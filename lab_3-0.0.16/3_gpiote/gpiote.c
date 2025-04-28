#include "gpiote.h"
#include "gpio.h"

#define BUTTON_1_PIN 13
#define LED_PINS {17, 18, 19, 20}

void gpiote_init(void) {
    // Konfigurer GPIOTE kanal 0 for BUTTON_1 som hendelse
    GPIOTE->CONFIG[0] = (1 << 0) |                  // MODE: Hendelse (Event)
                        (BUTTON_1_PIN << 8) |       // PSEL: Pin 13
                        (2 << 16);                  // POLARITY: HiToLo (aktiv-lav)

    // Konfigurer GPIOTE kanaler 1-4 for LED-ene som oppgaver
    int led_pins[] = LED_PINS;
    for (int i = 0; i < 4; i++) {
        GPIOTE->CONFIG[i+1] = (3 << 0) |            // MODE: Oppgave (Task)
                              (led_pins[i] << 8) |  // PSEL: Pin 16 til 20
                              (3 << 16) |           // POLARITY: Toggle
                              (1 << 20);            // OUTINIT: Høy (LED av, aktiv-lav)
    }
}