#include "mcc_generated_files/mcc.h"
#include <xc.h>
#define Dgt1 LATCbits.LATC3
#define Dgt2 LATCbits.LATC4
#define DS  LATC6      //PORTCbits.RC6
#define STCP LATC5     //PORTCbits.RC5
#define SHCP LATC7     //PORTCbits.RC7
 unsigned int number;
 unsigned char d1, d2, d3, d4;
unsigned char Digit[10] = { 0x03, 0x9F, 0X25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09 };// SIRASIYLA 0,1,2,3,4,5,6,7,8,9
/*
                         Main application
 */

void writeDigit(unsigned char digit) {
    unsigned char i;
    SHCP = 0;
    STCP = 0;
    SHCP = 0;
    STCP = 0;
    for (i = 0; i < 8; i++) {
        DS = (digit >> i) & 0x01;
        SHCP = 1;
        SHCP = 1;
        SHCP = 0;
        SHCP = 0;
    }
    STCP = 1;
    STCP = 1;
}

void displayNumber(unsigned int number1) {

    d1 = number1 / 1000;
    number1 %= 1000;
    d2 = number1 / 100;
    number1 %= 100;
    d3 = number1 / 10;
    d4 = number1 % 10;

    /*d1=1;
    d2=2;
    d3=3;
    d4=4;*/

    // Display each digit
    //digit_select(4);
    Dgt1 = 1;//a1=digit1
            Dgt2 = 1;
    writeDigit(Digit[d1]);
   __delay_ms(50);

    //digit_select(3);
    Dgt1 = 0;//a2=digit2
            Dgt2 = 1;
    writeDigit(Digit[d2]);
   __delay_ms(50);

    //digit_select(2);
    Dgt1 = 1;//a3=digit3
            Dgt2 = 0;
    writeDigit(Digit[d3]);
    __delay_ms(50);

    //digit_select(1);
    Dgt1 = 0;//a4=digit4
            Dgt2 = 0;
    writeDigit(Digit[d4]);
   __delay_ms(50);
}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        for (number = 0; number < 10000; number++)
        {
            displayNumber(number);
            __delay_ms(10);
        }
    }
}
/**
 End of File
*/