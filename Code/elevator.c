sbit LCD_RS at PORTA1_bit;
sbit LCD_EN at PORTA2_bit;
sbit LCD_D4 at PORTA4_bit;
sbit LCD_D5 at PORTA5_bit;
sbit LCD_D6 at PORTA6_bit;
sbit LCD_D7 at PORTA7_bit;

sbit LCD_RS_Direction at DDA1_bit;
sbit LCD_EN_Direction at DDA2_bit;
sbit LCD_D4_Direction at DDA4_bit;
sbit LCD_D5_Direction at DDA5_bit;
sbit LCD_D6_Direction at DDA6_bit;
sbit LCD_D7_Direction at DDA7_bit;

char key;
int currentFloor = 1;
int target = 0;

void main() {

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1,1,"Floor:");
    Lcd_Chr(1,8,currentFloor + '0');

    // KEY PAD
    DDRD = 0x0F;     // ROWS OUTPUT (PD0-3) – COLUMNS INPUT (PD4-7)
    PORTD = 0xFF;    // pull-up for columns

    // BUTTONS
    DDRC = 0x00;     // FLOOR BUTTONS INPUT
    PORTC = 0xFF;    // pull-up

    // MOTOR
    DDRB = 0x0f;

    while(1) {

        key = 0;
        target = 0;


                PORTD = 0xFE;
        if(PIND.B4 == 0) key = '7';
        if(PIND.B5 == 0) key = '8';
        if(PIND.B6 == 0) key = '9';
        if(PIND.B7 == 0) key = 'A';

        PORTD = 0xFD;
        if(PIND.B4 == 0) key = '4';
        if(PIND.B5 == 0) key = '5';
        if(PIND.B6 == 0) key = '6';
        if(PIND.B7 == 0) key = 'B';

        PORTD = 0xFB;
        if(PIND.B4 == 0) key = '1';
        if(PIND.B5 == 0) key = '2';
        if(PIND.B6 == 0) key = '3';
        if(PIND.B7 == 0) key = 'C';

        PORTD = 0xF7;
        if(PIND.B4 == 0) key = 'O';
        if(PIND.B5 == 0) key = 'C';
        if(PIND.B6 == 0) key = '0';
        if(PIND.B7 == 0) key = '=';


        // DEBOUNCE + RELEASE
        if(key != 0){
            Delay_ms(50);
            while(PIND.B4 == 0 || PIND.B5 == 0 || PIND.B6 == 0 || PIND.B7 == 0);
        }


        if(key >= '1' && key <= '5'){
            target = key - '0';
        }


        if(PINC.B0 == 0) target = 1;
        if(PINC.B1 == 0) target = 2;
        if(PINC.B2 == 0) target = 3;
        if(PINC.B3 == 0) target = 4;
        if(PINC.B4 == 0) target = 5;


        //   MOVE ELEVATOR
   =
        if(target >= 1 && target <=5 && target != currentFloor){

            // UP
            if(target > currentFloor){
                PORTB.B0 = 1;
                PORTB.B1 = 0;

                while(currentFloor < target){
                    Delay_ms(2000);
                    currentFloor++;

                    Lcd_Cmd(_LCD_CLEAR);
                    Lcd_Out(1,1,"Floor:");

                    Lcd_Chr(1,8,currentFloor + '0');
                }
            }

            // DOWN
            if(target < currentFloor){
                PORTB.B0 = 0;
                PORTB.B1 = 1;

                while(currentFloor > target){
                    Delay_ms(2000);
                    currentFloor--;

                    Lcd_Cmd(_LCD_CLEAR);
                    Lcd_Out(1,1,"Floor:");
                    Lcd_Chr(1,8,currentFloor + '0');
                }
            }

            PORTB.B0 = 0;
            PORTB.B1 = 0;
        }

        Delay_ms(20);
    }
}