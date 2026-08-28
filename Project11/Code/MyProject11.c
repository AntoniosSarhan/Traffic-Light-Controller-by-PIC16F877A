// Control switches configuration (PORT E)
#define MAN_AUTO_SW   RE0_bit   // 0 = Manual, 1 = Automatic
#define STREET_SW     RE1_bit   // In Manual: 0 = South Green, 1 = West Green

// West Street Traffic Lights (PORT D)
#define WEST_RED      RD0_bit
#define WEST_YELLOW   RD1_bit
#define WEST_GREEN    RD2_bit

// South Street Traffic Lights (PORT D)
#define SOUTH_RED     RD3_bit
#define SOUTH_YELLOW  RD4_bit
#define SOUTH_GREEN   RD5_bit

// 7-Segment Enables (PORT C)
#define EN_WEST_UNT   RC0_bit
#define EN_WEST_TEN   RC1_bit
#define EN_SOUTH_UNT  RC2_bit
#define EN_SOUTH_TEN  RC3_bit

// Global Variables
unsigned char west_timer = 20;
unsigned char south_timer = 23;
unsigned char state = 0;
unsigned int isr_counter = 0;
unsigned char digit_select = 0;

unsigned char manual_state = 0;
unsigned char prev_man_auto = 1;
unsigned char exiting_manual = 0;

void update_traffic_lights() {
    if (MAN_AUTO_SW == 1 && exiting_manual == 0) {
        switch(state) {
            case 0: // West Green | South Red
                WEST_GREEN = 1; WEST_YELLOW = 0; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 1: // West Yellow | South Red
                WEST_GREEN = 0; WEST_YELLOW = 1; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 2: // West Red | South Green
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 1; SOUTH_YELLOW = 0; SOUTH_RED = 0;
                break;
            case 3: // West Red | South Yellow
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 1; SOUTH_RED = 0;
                break;
        }
    }
    else {
        switch(manual_state) {
            case 0: // West Green
                west_timer = 0; south_timer = 0;
                WEST_GREEN = 1; WEST_YELLOW = 0; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 1: // West Yellow (Transition)
                south_timer = 0;
                WEST_GREEN = 0; WEST_YELLOW = 1; WEST_RED = 0;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 0; SOUTH_RED = 1;
                break;
            case 2: // South Green
                west_timer = 0; south_timer = 0;
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 1; SOUTH_YELLOW = 0; SOUTH_RED = 0;
                break;
            case 3: // South Yellow (Transition)
                west_timer = 0;
                WEST_GREEN = 0; WEST_YELLOW = 0; WEST_RED = 1;
                SOUTH_GREEN = 0; SOUTH_YELLOW = 1; SOUTH_RED = 0;
                break;
        }
    }
}

void interrupt() {
    if (TMR0IF_bit) {
        TMR0 = 6;
        TMR0IF_bit = 0;

        // 1. Refresh Display (Anti-Ghosting)
        EN_WEST_UNT = 0; EN_WEST_TEN = 0; EN_SOUTH_UNT = 0; EN_SOUTH_TEN = 0;

        // 2. Multiplexing
        if (digit_select == 0) {
            PORTB = (west_timer % 10) | ((south_timer % 10) << 4);
            EN_WEST_UNT = 1; EN_SOUTH_UNT = 1;
            digit_select = 1;
        } else {
            PORTB = (west_timer / 10) | ((south_timer / 10) << 4);
            EN_WEST_TEN = 1; EN_SOUTH_TEN = 1;
            digit_select = 0;
        }

        // 3. Switch Mode Handling
        if (MAN_AUTO_SW != prev_man_auto) {
            prev_man_auto = MAN_AUTO_SW;
            if (MAN_AUTO_SW == 1) {
                exiting_manual = 1;
                if (manual_state == 0)      { manual_state = 1; west_timer = 3; }
                else if (manual_state == 2) { manual_state = 3; south_timer = 3; }
            } else {
                exiting_manual = 0;
                manual_state = (STREET_SW == 0) ? 2 : 0;
            }
        }

        if (MAN_AUTO_SW == 0) {
            if (manual_state == 0 && STREET_SW == 0)      { manual_state = 1; west_timer = 3; }
            else if (manual_state == 2 && STREET_SW == 1) { manual_state = 3; south_timer = 3; }
        }

        // 4. Timer Logic (1 Second)
        isr_counter++;
        if (isr_counter >= 250) {
            isr_counter = 0;

            if (MAN_AUTO_SW == 1 && exiting_manual == 0) {
                if (west_timer > 0)  west_timer--;
                if (south_timer > 0) south_timer--;

                switch(state) {
                    case 0: if (west_timer == 0)  { state = 1; west_timer = 3; } break;
                    case 1: if (west_timer == 0)  { state = 2; west_timer = 15; south_timer = 12; } break;
                    case 2: if (south_timer == 0) { state = 3; south_timer = 3; } break;
                    case 3: if (south_timer == 0) { state = 0; west_timer = 20; south_timer = 23; } break;
                }
            } else {
                if (manual_state == 1) {
                    if (west_timer > 0) west_timer--;
                    if (west_timer == 0) {
                        if (exiting_manual) { exiting_manual = 0; state = 2; west_timer = 15; south_timer = 12; }
                        else { manual_state = 2; }
                    }
                } else if (manual_state == 3) {
                    if (south_timer > 0) south_timer--;
                    if (south_timer == 0) {
                        if (exiting_manual) { exiting_manual = 0; state = 0; west_timer = 20; south_timer = 23; }
                        else { manual_state = 0; }
                    }
                }
            }
        }
    }
}

void main() {
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x03;
    ADCON1 = 0x06;

    PORTB = 0; PORTC = 0; PORTD = 0;

    manual_state = (STREET_SW == 0) ? 2 : 0;
    update_traffic_lights();

    OPTION_REG = 0x83; // Prescaler 1:16
    TMR0 = 6;
    TMR0IE_bit = 1;
    GIE_bit = 1;

    while(1) {
        update_traffic_lights();
    }
}