#include <xc.h>
#include <stdint.h>

// Konfigürasyon bitleri
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config BOREN = ON
#pragma config CLKOUTEN = OFF
#pragma config WRT = OFF

#define _XTAL_FREQ 4000000

// Pin tan?mlar?
#define Dgt1 LATCbits.LATC3
#define Dgt2 LATCbits.LATC4
#define DS LATC6
#define STCP LATC5
#define SHCP LATC7

unsigned char d1, d2, d3, d4;
unsigned char Digit[10] = {0x03, 0x9F, 0X25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09}; // 0-9 aras?ndaki rakamlar?n kar??l?k gelen de?erleri

volatile unsigned int number = 9999; // 9999 ile ba?la

void writeDigit(unsigned char digit)
{
    unsigned char i;
    SHCP = 0;
    STCP = 0;
    SHCP = 0;
    STCP = 0;
    for (i = 0; i < 8; i++)
    {
        DS = (digit >> i) & 0x01;
        SHCP = 1;
        SHCP = 1;
        SHCP = 0;
        SHCP = 0;
    }
    STCP = 1;
    STCP = 1;
}

void displayNumber(unsigned int number1)
{
    d1 = number1 / 1000;
    number1 %= 1000;
    d2 = number1 / 100;
    number1 %= 100;
    d3 = number1 / 10;
    d4 = number1 % 10;

    // Her basama?? göster
    Dgt1 = 1; // Basamak 1'i seç
    Dgt2 = 1;
    writeDigit(Digit[d1]);
     __delay_ms(10);

    Dgt1 = 0; // Basamak 2'yi seç
    Dgt2 = 1;
    writeDigit(Digit[d2]);
     __delay_ms(10);

    Dgt1 = 1; // Basamak 3'ü seç
    Dgt2 = 0;
    writeDigit(Digit[d3]);
     __delay_ms(10);

    Dgt1 = 0; // Basamak 4'ü seç
    Dgt2 = 0;
    writeDigit(Digit[d4]);
     __delay_ms(10);
}

void initTimer1()
{
    T1CONbits.TMR1CS = 0b00; // Timer1, FOSC/4 h?z?nda çal??acak ?ekilde ayarland?
    T1CONbits.T1CKPS = 0b11; // Timer1 ön bölücü 1:8
    TMR1 = 3036; // 1 saniyelik zaman dilimi için Timer1'i ba?lat
    T1CONbits.TMR1ON = 1; // Timer1'i etkinle?tir
    TMR1IE = 1; // Timer1 kesmelerini etkinle?tir
    PEIE = 1; // Periferik kesmeleri etkinle?tir
    GIE = 1; // Genel kesmeleri etkinle?tir
}

void interrupt Timer1_ISR(void)
{
    if (TMR1IF)
    {
        TMR1IF = 0; // Timer1 kesme bayra??n? s?f?rla

        number--; // Her 1 saniyede bir say?y? azalt
        if (number < 0)
            number = 9999; // S?f?ra ula??ld???nda geri dön
    }
}

void main(void)
{
    TRISC = 0x00; // PORTC'yi ç?k?? olarak ayarla
    PORTC = 0x00; // PORTC'yi ba?lat

    initTimer1(); // Timer1'i ba?lat

    while (1)
    {
        displayNumber(number);
    }
}


