#include <p18f4580.h>

#define Led1 PORTDbits.RD0
#define Led2 PORTDbits.RD1

char read;

void main(void)
{
    TRISCbits.RC6 = 0;  // TX
    TRISCbits.RC7 = 1;  // RX

    TRISDbits.RD0 = 0;  // LED1 output
    TRISDbits.RD1 = 0;  // LED2 output

    // UART INIT
    TXSTA = 0x24;       // TX enable, async, high speed
    RCSTA = 0x90;       // Serial port enable, RX enable
    SPBRG = 0x19;       // Baud-rate setting

    // INTERRUPT INIT
    PIE1bits.RCIE = 1;  // UART receive interrupt enable
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while(1)
    {
    }
}

#pragma code ISR = 0x08
#pragma interrupt ISR

void ISR(void)
{
    if(PIR1bits.RCIF)
    {
        read = RCREG;

        if(read == '1')
        {
            Led1 = 1;
        }
        else if(read == '0')
        {
            Led1 = 0;
        }
        else if(read == 'A' || read == 'a')
        {
            Led2 = 1;
        }
        else if(read == 'B' || read == 'b')
        {
            Led2 = 0;
        }
    }
}
