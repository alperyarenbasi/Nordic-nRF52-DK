#include "uart.h"
#include "gpio.h"

void uart_init(){
    // Config GPIO pins
    GPIO->PIN_CNF[UART_INT_TX_PIN] = (1<<0); // TXD: Output, no pull
    GPIO->PIN_CNF[UART_INT_RX_PIN] = (3<<2); // RXD: Input,

    //Assigning pins to UART
    UART->PSELTXD = UART_INT_TX_PIN;    //6
    UART->PSELRXD = UART_INT_RX_PIN;    //8
    
    // Disable hardware flow control (no CTS/RTS)
    UART->PSELCTS = 0xFFFFFFFF;         // Disconnected
    UART->PSELRTS = 0xFFFFFFFF;         // Disconnected

    UART->CONFIG = 0;                   // HWFC = 0 (disabled), Parity = 0 (none), Stop = 0 (1 stop bit)
    UART->BAUDRATE = 0x00275000;        // Value from datasheet for 9600 baud
    UART->ENABLE = 4;                   //enable uart
    UART->TASKS_STARTRX = 1;            // Start mottaker ?
}


void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;            // Start sender
    UART->TXD = letter;                 // Skriv tegn til TXD
    while (!UART->EVENTS_TXDRDY);       // Vent til sending er ferdig
    UART->EVENTS_TXDRDY = 0;            // Nullstill event
    UART->TASKS_STOPTX = 1;             // Stop transmitter (kan droppes hvis du skal sende flere tegn etter hverandre)
}


char uart_read() {
    if (UART->EVENTS_RXDRDY) {  // Sjekk om data er klar
        char letter = UART->RXD; // Les tegn
        UART->EVENTS_RXDRDY = 0; // Nullstill event
        return letter;
    }
    return '\0';                // Ingen data, returner null
}