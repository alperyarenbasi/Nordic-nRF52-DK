#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>          /* ← for bool, true, false */

#define BUTTON_1_PIN 13    
#define BUTTON_2_PIN 14
#define BUTTON_3_PIN 15

#define LED_MATRIX ((1<<17)|(1<<18)|(1<<19)|(1<<20))

//  picocom -b 9600 /dev/ttyACM0

void gpio_init(void){
    GPIO->PIN_CNF[BUTTON_1_PIN] = (3 << 2);
    GPIO->PIN_CNF[BUTTON_2_PIN] = (3 << 2);
    GPIO->PIN_CNF[BUTTON_3_PIN] = (3 << 2);


    GPIO->DIRSET = LED_MATRIX;
    GPIO->OUTSET = LED_MATRIX;
}


ssize_t _write(int fd, const void *buf, size_t count) {
    char *letter = (char *)(buf);
    for (int i = 0; i < count; i++) {
        uart_send(*letter);
        letter++;
    }
    return count;
}

static inline bool pressed(int pin)      /* aktiv-lav: 0 = trykket */
{
    return !(GPIO->IN & (1U << pin));
}

int main() {

    uart_init();
    gpio_init();
   
    bool sent1 = false, sent2 = false, sent3 = false;
    int sleep = 0;
    while (1) {

       /* --------- BTN1 → 'A' --------- */
        if (pressed(BUTTON_1_PIN)) {
            if (!sent1) { uart_send('A'); sent1 = true; }
        } else {
            sent1 = false;               // klar for neste trykk
        }

        /* --------- BTN2 → 'B' --------- */
        if (pressed(BUTTON_2_PIN)) {
            if (!sent2) { uart_send('B'); sent2 = true; }
        } else {
            sent2 = false;
        }

        /* --------- BTN3 → iprintf ----- */
        if (pressed(BUTTON_3_PIN)) {
            if (!sent3) {
                iprintf("The average grade in TTK%d was in %d was: %c\n\r",
                        4235, 2022, 'B');
                sent3 = true;
            }
        } else {
            sent3 = false;
        }

        
        // Toggle LEDs on received character
        char received = uart_read();
        if (received != '\0') {
            uart_send(received); //Bare for å teste, funket!!
            if (GPIO->OUT & LED_MATRIX) {  // If LEDs are off
                GPIO->OUTCLR = LED_MATRIX;  // Turn on
            } else {
                GPIO->OUTSET = LED_MATRIX;  // Turn off
            }
        }
    
        sleep = 10000;
	    while(--sleep); // Delay

    }
    
	return 0;
}
