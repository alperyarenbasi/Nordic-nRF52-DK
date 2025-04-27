#include <stdint.h>

#define BUTTON_1_PIN 13    
#define BUTTON_2_PIN 14
#define LED_Matrix (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20); 
#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init(void){
    /* PULL = 11 (pull-up)  =>  (3 << 2)  */
    GPIO->PIN_CNF[BUTTON_1_PIN] = (3 << 2);
    GPIO->PIN_CNF[BUTTON_2_PIN] = (3 << 2);
}



int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    button_init();

	int sleep = 0;
    while (1) {

        /* aktiv-lav: 0 = knapp trykket */
        if (!(GPIO->IN & (1 << BUTTON_1_PIN))) {           /* BUTTON 1 */
            GPIO->OUTCLR = LED_Matrix;
        }
        if (!(GPIO->IN & (1 << BUTTON_2_PIN))) {           /* BUTTON 2 */
            GPIO->OUTSET = LED_Matrix;
        }
        sleep = 10000;
	    while(--sleep); // Delay
    }
    
	return 0;
}