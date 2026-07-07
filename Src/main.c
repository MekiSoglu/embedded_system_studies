#include <stdint.h>
#include "stm32.h"

#define LED_PIN_GREEN  12
#define LED_PIN_ORANGE 13
#define LED_PIN_RED    14
#define LED_PIN_BLUE   15
#define PUSH_BUTTON    0

void sleep(volatile uint32_t key) {
    while (key > 0) key--;
}

uint8_t buton_yeni_basildi_mi(uint8_t *last_toggle)
{
    uint8_t toggle = (GPIOA->IDR & (1UL << PUSH_BUTTON)) ? 1 : 0;
    uint8_t yeni_basildi = (toggle == 1 && *last_toggle == 0);
    *last_toggle = toggle;
    return yeni_basildi;
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~(0b11UL << (PUSH_BUTTON * 2));
    GPIOA->PUPDR &= ~(0b11UL << (PUSH_BUTTON * 2));
    GPIOA->PUPDR |=  (0b10UL << (PUSH_BUTTON * 2));

    GPIOD->MODER &= ~(0b11UL << (LED_PIN_GREEN  * 2));
    GPIOD->MODER |=  (0b01UL << (LED_PIN_GREEN  * 2));
    GPIOD->MODER &= ~(0b11UL << (LED_PIN_ORANGE * 2));
    GPIOD->MODER |=  (0b01UL << (LED_PIN_ORANGE * 2));
    GPIOD->MODER &= ~(0b11UL << (LED_PIN_RED    * 2));
    GPIOD->MODER |=  (0b01UL << (LED_PIN_RED    * 2));
    GPIOD->MODER &= ~(0b11UL << (LED_PIN_BLUE   * 2));
    GPIOD->MODER |=  (0b01UL << (LED_PIN_BLUE   * 2));

    uint8_t last_toggle = 0;
    uint8_t key = 1;
    uint8_t leds [4] ={LED_PIN_GREEN , LED_PIN_ORANGE , LED_PIN_RED , LED_PIN_BLUE };
    uint8_t current_led =0;

    for (;;)
    {

        if (buton_yeni_basildi_mi(&last_toggle)) {
            key = !key;
        }

        if(key){

        	for(int i =0;i<4;i++){
        		if(current_led == i){
        			GPIOD->ODR |= (1UL << leds[i]);
        			sleep(10000);
        		}else{
        			GPIOD->ODR &= ~(1UL << leds[i]);
        			sleep(10000);
        		}
        	}
        }
        sleep(30000);


        current_led = (current_led +1) %4;


    }
}
