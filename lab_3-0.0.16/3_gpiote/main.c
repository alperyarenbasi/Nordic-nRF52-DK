#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

#define BUTTON_1_PIN 13
#define LED_MATRIX ((1<<17)|(1<<18)|(1<<19)|(1<<20))

int main() {
    GPIO->PIN_CNF[BUTTON_1_PIN] = (3 << 2);
    GPIO->DIRSET = LED_MATRIX;
    GPIO->OUTSET = LED_MATRIX;

    gpiote_init();
    ppi_init();

    while (1) {
        // Gjør ingenting ->CPU gjør ingenting
    }
    return 0;
}