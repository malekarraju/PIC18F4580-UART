#include <p18f4580.h>

void Delay(int);

void main(void)
{
    char arr[] = "Raju Malekar ";
    char *str;

    TRISCbits.RC6 = 0;  // Transmitter
    TRISCbits.RC7 = 1;  // Receiver

    // UART Init
    TXSTA = 0x24;       // TX enable, asynchronous, high speed
    RCSTA = 0x90;       // Serial port enable, receiver enable
    SPBRG = 0x19;       // Baud-rate setting

    while(1)
    {
        str = arr;

        while(*str != '\0')
        {
            while(PIR1bits.TXIF == 0); // Wait until TXREG is ready

            TXREG = *str;
            Delay(100);

            str++;
        }
    }
}

void Delay(int x)
{
    int i, j;

    for(i = 0; i < x; i++)
        for(j = 0; j < x; j++);
}
