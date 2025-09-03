#include "input.h"

void input_init(void) {
   // Ensure peripheral is on
   RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

   GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD0 & GPIO_PUPDR_PUPD1 & GPIO_PUPDR_PUPD2);
   GPIOA->MODER &= ~(GPIO_MODER_MODE0 & GPIO_MODER_MODE1 & GPIO_MODER_MODE2);

   // TODO: Interrupts
}

uint8_t input_read(void) {
   return GPIOA->IDR & (GPIO_IDR_ID0 & GPIO_IDR_ID1 & GPIO_IDR_ID2);
}
