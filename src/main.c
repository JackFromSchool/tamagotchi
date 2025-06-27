#include "stm32l0xx.h"

#include "i2c1.h"
#include "sprite.h"
#include "ssd1306.h"

void hsi_clock_on(void) {
   // Enable HSI
   RCC->CR |= RCC_CR_HSION;
   // Wait for stability
   while ((RCC->CR & RCC_CR_HSIRDY) == 0) {
   }

   // Switch SysClock to HSI
   uint32_t cfgr = RCC->CFGR;
   cfgr &= ~(RCC_CFGR_SW);
   cfgr |= RCC_CFGR_SW_HSI;
   RCC->CFGR = cfgr;
}

uint8_t on = 0;

int main(void) {
   // NOTE: Doesn't work in start up for some reason so it's here
   hsi_clock_on();
   SystemCoreClockUpdate();

   RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

   GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk);
   GPIOA->MODER |= GPIO_MODER_MODE0_0;

   SysTick->VAL = 0x00;
   SysTick->LOAD = SystemCoreClock - 1;
   SCB->SHP[1] = (SCB->SHP[1] & (~0xC0000000)) | (1 << 30);
   SysTick->CTRL = 0x7;
   SysTick->VAL = 0;

   i2c1_init();
   ssd1306_init();
   ssd1306_clear_screen();

   ssd1306_draw_sprite(&icon_food);
   ssd1306_draw_sprite(&icon_lights);
   ssd1306_draw_sprite(&icon_game);
   ssd1306_draw_sprite(&icon_medicine);
   ssd1306_draw_sprite(&icon_toilet);
   ssd1306_draw_sprite(&icon_scale);
   ssd1306_draw_sprite(&icon_discipline);
   ssd1306_draw_sprite(&icon_attention);

   while (1) {
      __ASM("nop");
   }

   return 0;
}

void SysTick_Handler(void) {
   if (on) {
      GPIOA->BSRR = GPIO_BSRR_BR_0;
   } else {
      GPIOA->BSRR = GPIO_BSRR_BS_0;
   }
   on = !on;
}
