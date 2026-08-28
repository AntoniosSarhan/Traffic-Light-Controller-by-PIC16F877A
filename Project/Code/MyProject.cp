#line 1 "C:/Users/Antonios/Desktop/Summer Training/Embedded Systems/Embedded/Project/Code/MyProject.c"
#line 22 "C:/Users/Antonios/Desktop/Summer Training/Embedded Systems/Embedded/Project/Code/MyProject.c"
unsigned char west_timer = 20;
unsigned char south_timer = 23;
unsigned char state = 0;
unsigned int isr_counter = 0;
unsigned char digit_select = 0;


unsigned char manual_state = 0;
unsigned char prev_man_auto = 1;
unsigned char exiting_manual = 0;


void update_traffic_lights() {
 if ( RE0_bit  == 1 && exiting_manual == 0) {

 switch(state) {
 case 0:
  RD2_bit  = 1;  RD1_bit  = 0;  RD0_bit  = 0;
  RD5_bit  = 0;  RD4_bit  = 0;  RD3_bit  = 1;
 break;
 case 1:
  RD2_bit  = 0;  RD1_bit  = 1;  RD0_bit  = 0;
  RD5_bit  = 0;  RD4_bit  = 0;  RD3_bit  = 1;
 break;
 case 2:
  RD2_bit  = 0;  RD1_bit  = 0;  RD0_bit  = 1;
  RD5_bit  = 1;  RD4_bit  = 0;  RD3_bit  = 0;
 break;
 case 3:
  RD2_bit  = 0;  RD1_bit  = 0;  RD0_bit  = 1;
  RD5_bit  = 0;  RD4_bit  = 1;  RD3_bit  = 0;
 break;
 }
 }
 else {

 switch(manual_state) {
 case 0:
 west_timer = 0; south_timer = 0;
  RD2_bit  = 1;  RD1_bit  = 0;  RD0_bit  = 0;
  RD5_bit  = 0;  RD4_bit  = 0;  RD3_bit  = 1;
 break;
 case 1:
 south_timer = 0;
  RD2_bit  = 0;  RD1_bit  = 1;  RD0_bit  = 0;
  RD5_bit  = 0;  RD4_bit  = 0;  RD3_bit  = 1;
 break;
 case 2:
 west_timer = 0; south_timer = 0;
  RD2_bit  = 0;  RD1_bit  = 0;  RD0_bit  = 1;
  RD5_bit  = 1;  RD4_bit  = 0;  RD3_bit  = 0;
 break;
 case 3:
 west_timer = 0;
  RD2_bit  = 0;  RD1_bit  = 0;  RD0_bit  = 1;
  RD5_bit  = 0;  RD4_bit  = 1;  RD3_bit  = 0;
 break;
 }
 }
}


void interrupt() {
 if (TMR0IF_bit) {
 TMR0 = 6;
 TMR0IF_bit = 0;


  RC0_bit  = 0;  RC1_bit  = 0;  RC2_bit  = 0;  RC3_bit  = 0;
 PORTB = 0x00;


 switch(digit_select) {
 case 0: PORTB = (west_timer % 10);  RC0_bit  = 1; digit_select = 1; break;
 case 1: PORTB = (west_timer / 10);  RC1_bit  = 1; digit_select = 2; break;
 case 2: PORTB = (south_timer % 10);  RC2_bit  = 1; digit_select = 3; break;
 case 3: PORTB = (south_timer / 10);  RC3_bit  = 1; digit_select = 0; break;
 }


 if ( RE0_bit  != prev_man_auto) {
 prev_man_auto =  RE0_bit ;


 if ( RE0_bit  == 1) {
 exiting_manual = 1;
 if (manual_state == 0) {
 manual_state = 1;
 west_timer = 3;
 }
 else if (manual_state == 2) {
 manual_state = 3;
 south_timer = 3;
 }
 }

 else {
 exiting_manual = 0;
 if ( RE1_bit  == 0) manual_state = 2;
 else manual_state = 0;
 }
 }


 if ( RE0_bit  == 0) {
 if (manual_state == 0 &&  RE1_bit  == 0) {
 manual_state = 1;
 west_timer = 3;
 }
 else if (manual_state == 2 &&  RE1_bit  == 1) {
 manual_state = 3;
 south_timer = 3;
 }
 }


 isr_counter++;
 if (isr_counter >= 250) {
 isr_counter = 0;


 if ( RE0_bit  == 1 && exiting_manual == 0) {
 if (west_timer > 0) west_timer--;
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

 else {
 if (manual_state == 1) {
 if (west_timer > 0) west_timer--;
 if (west_timer == 0) {
 if (exiting_manual) {
 exiting_manual = 0;
 state = 2;
 west_timer = 15;
 south_timer = 12;
 } else {
 manual_state = 2;
 }
 }
 }
 else if (manual_state == 3) {
 if (south_timer > 0) south_timer--;
 if (south_timer == 0) {
 if (exiting_manual) {
 exiting_manual = 0;
 state = 0;
 west_timer = 20;
 south_timer = 23;
 } else {
 manual_state = 0;
 }
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


 if ( RE1_bit  == 0) manual_state = 2;
 else manual_state = 0;

 update_traffic_lights();


 OPTION_REG = 0x83;
 TMR0 = 6;
 TMR0IE_bit = 1;
 GIE_bit = 1;

 while(1) {
 update_traffic_lights();
 }
}
