#include "ppi.h"
#include "gpiote.h"

void ppi_init(void) {
    // Konfigurer PPI-kanaler 0-3
    for (int i = 0; i < 4; i++) {
        PPI->CH[i].EEP = (uint32_t)&GPIOTE->EVENTS_IN[0];     // Hendelse fra BUTTON_1
        PPI->CH[i].TEP = (uint32_t)&GPIOTE->TASKS_OUT[i+1];   // Oppgave til LED (kanal 1-4)
    }

    // Aktiver PPI-kanaler 0-3
    PPI->CHENSET = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
}