// Control switches configuration (PORT E)
#define MAN_AUTO_SW   RE0_bit   // 0 = Manual Mode (Pressed), 1 = Automatic Mode (Released)
#define STREET_SW     RE1_bit   // In Manual: 0 = South Green (Pressed), 1 = West Green (Released)

// West Street Traffic Lights (PORT D)
#define WEST_RED      RD0_bit
#define WEST_YELLOW   RD1_bit
#define WEST_GREEN    RD2_bit

// South Street Traffic Lights (PORT D)
#define SOUTH_RED     RD3_bit
#define SOUTH_YELLOW  RD4_bit
#define SOUTH_GREEN   RD5_bit

// 7-Segment Display Enable Pins (PORT C)
#define EN_WEST_UNT   RC0_bit   // West street - Units digit
#define EN_WEST_TEN   RC1_bit   // West street - Tens digit
#define EN_SOUTH_UNT  RC2_bit   // South street - Units digit
#define EN_SOUTH_TEN  RC3_bit   // South street - Tens digit

// Global Variables
unsigned char west_timer = 20;  // Initial West green (20s)
unsigned char south_timer = 23; // Initial South red (23s)
unsigned char state = 0;        // Automatic sequence state (0 to 3)
unsigned int isr_counter = 0;   // Counter for 1 second interval
unsigned char digit_select = 0; // Multiplexing tracker

// Manual Mode Variables
unsigned char manual_state = 0; // 0: West Green, 1: West Yellow, 2: South Green, 3: South Yellow
unsigned char prev_man_auto = 1;
unsigned char exiting_manual = 0; // Flag to handle 3s yellow transition when leaving manual

// Function to update Traffic Light LEDs instantly
void update_traffic_lights() {
    if (MAN_AUTO_SW == 1 && exiting_manual == 0) {
        // --- AUTOMATIC MODE LIGHTS ---
        switch(state) {
            case 0: // West Green (20s) | South Red (23s)
                WEST_GREEN = 1; WEST_YELLOW = 0; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 1: // West Yellow (3s) | South Red (last 3s)
                WEST_GREEN = 0; WEST_YELLOW = 1; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 2: // West Red (15s) | South Green (12s)
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 1; SOUTH_YELLOW = 0; SOUTH_RED = 0;
                break;
            case 3: // West Red (last 3s) | South Yellow (3s)
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 1; SOUTH_RED = 0;
                break;
        }
    }
    else {
        // --- MANUAL MODE OR TRANSITION LIGHTS ---
        switch(manual_state) {
            case 0: // West Green | South Red
                west_timer = 0; south_timer = 0;
                WEST_GREEN = 1; WEST_YELLOW = 0; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 1: // West Yellow (3s) | South Red
                south_timer = 0;
                WEST_GREEN = 0; WEST_YELLOW = 1; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 2: // West Red | South Green
                west_timer = 0; south_timer = 0;
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 1; SOUTH_YELLOW = 0; SOUTH_RED = 0;
                break;
            case 3: // West Red | South Yellow (3s)
                west_timer = 0;
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 1; SOUTH_RED = 0;
                break;
        }
    }
}

// Interrupt Service Routine
void interrupt() {
    if (TMR0IF_bit) {
        TMR0 = 6;         // Reload Timer0
        TMR0IF_bit = 0;   // Clear Flag

        // 1. Anti-Ghosting
        EN_WEST_UNT = 0; EN_WEST_TEN = 0; EN_SOUTH_UNT = 0; EN_SOUTH_TEN = 0;
        PORTB = 0x00;

        // 2. Display Multiplexing
        switch(digit_select) {
            case 0: PORTB = (west_timer % 10);  EN_WEST_UNT = 1; digit_select = 1; break;
            case 1: PORTB = (west_timer / 10);  EN_WEST_TEN = 1; digit_select = 2; break;
            case 2: PORTB = (south_timer % 10); EN_SOUTH_UNT = 1; digit_select = 3; break;
            case 3: PORTB = (south_timer / 10); EN_SOUTH_TEN = 1; digit_select = 0; break;
        }

        // 3. Switch Mode Transition Logic
        if (MAN_AUTO_SW != prev_man_auto) {
            prev_man_auto = MAN_AUTO_SW;

            // Returned to Auto Mode from Manual
            if (MAN_AUTO_SW == 1) {
                exiting_manual = 1; // Set transition flag
                if (manual_state == 0) {
                    manual_state = 1; // Switch West from Green to Yellow
                    west_timer = 3;
                }
                else if (manual_state == 2) {
                    manual_state = 3; // Switch South from Green to Yellow
                    south_timer = 3;
                }
            }
            // Entered Manual Mode from Auto
            else {
                exiting_manual = 0;
                if (STREET_SW == 0) manual_state = 2; // South Green (Pressed)
                else                manual_state = 0; // West Green (Released)
            }
        }

        // 4. Manual Switch Sampling (Only active during steady manual operation)
        if (MAN_AUTO_SW == 0) {
            if (manual_state == 0 && STREET_SW == 0) {
                manual_state = 1;
                west_timer = 3;
            }
            else if (manual_state == 2 && STREET_SW == 1) {
                manual_state = 3;
                south_timer = 3;
            }
        }

        // 5. Time Base (1-Second Logic)
        isr_counter++;
        if (isr_counter >= 250) {
            isr_counter = 0;

            // --- AUTOMATIC COUNTDOWN ---
            if (MAN_AUTO_SW == 1 && exiting_manual == 0) {
                if (west_timer > 0)  west_timer--;
                if (south_timer > 0) south_timer--;

                switch(state) {
                    case 0:
                        if (west_timer == 0) { state = 1; west_timer = 3; }
                        break;
                    case 1:
                        if (west_timer == 0) { state = 2; west_timer = 15; south_timer = 12; }
                        break;
                    case 2:
                        if (south_timer == 0) { state = 3; south_timer = 3; }
                        break;
                    case 3:
                        if (south_timer == 0) { state = 0; west_timer = 20; south_timer = 23; }
                        break;
                }
            }
            // --- MANUAL / EXIT TRANSITION COUNTDOWN ---
            else {
                if (manual_state == 1) {
                    if (west_timer > 0) west_timer--;
                    if (west_timer == 0) {
                        if (exiting_manual) {
                            exiting_manual = 0; // Finished 3s yellow, start auto from South Green
                            state = 2;
                            west_timer = 15;
                            south_timer = 12;
                        } else {
                            manual_state = 2; // Lock South Green in Manual
                        }
                    }
                }
                else if (manual_state == 3) {
                    if (south_timer > 0) south_timer--;
                    if (south_timer == 0) {
                        if (exiting_manual) {
                            exiting_manual = 0; // Finished 3s yellow, start auto from West Green
                            state = 0;
                            west_timer = 20;
                            south_timer = 23;
                        } else {
                            manual_state = 0; // Lock West Green in Manual
                        }
                    }
                }
            }
        }
    }
}

void main() {
    // I/O Configuration
    TRISB = 0x00; // Output for 7448 BCD Decoder
    TRISC = 0x00; // Output for 7-Segment Enables
    TRISD = 0x00; // Output for Traffic Light LEDs
    TRISE = 0x03; // Input for Switches (RE0, RE1)

    ADCON1 = 0x06; // Configure PORTE as Digital I/O
    PORTB = 0; PORTC = 0; PORTD = 0;

    // Bootup State Check
    if (STREET_SW == 0) manual_state = 2; // South Green
    else                manual_state = 0; // West Green

    update_traffic_lights();

    // Timer0 Setup
    OPTION_REG = 0x83; // Prescaler 1:16
    TMR0 = 6;
    TMR0IE_bit = 1;
    GIE_bit = 1;

    while(1) {
        update_traffic_lights();
    }
}