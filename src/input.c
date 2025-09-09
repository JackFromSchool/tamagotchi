#include "input.h"
#include "stm32l010x8.h"
#include "ui.h"

void input_init(void) {
   // Ensure peripheral is on
   RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

   GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD2);
   GPIOA->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2);

   // Enable External Interrupts
   SYSCFG->EXTICR[0] =
       (SYSCFG->EXTICR[0] &
        ~(SYSCFG_EXTICR1_EXTI0 | SYSCFG_EXTICR1_EXTI1 | SYSCFG_EXTICR1_EXTI2)) |
       SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI2_PA |
       SYSCFG_EXTICR1_EXTI2_PA;

   EXTI->IMR |= 0b111;
   EXTI->FTSR |= 0b111;

   NVIC_EnableIRQ(EXTI0_1_IRQn);
   NVIC_EnableIRQ(EXTI2_3_IRQn);

   NVIC_SetPriority(EXTI0_1_IRQn, 0);
   NVIC_SetPriority(EXTI2_3_IRQn, 0);
}

void EXTI0_1_IRQHandler(void) {
   // Clear Interrupt
   EXTI->PR |= 0b01;
   ui_next_icon();
}

void EXTI2_3_IRQHandler(void) {
   // Clear Interrupt
   EXTI->PR |= 0b10;
   ui_next_icon();
}

uint8_t input_read(void) {
   return (GPIOA->IDR & (GPIO_IDR_ID0 | GPIO_IDR_ID1 | GPIO_IDR_ID2));
}
