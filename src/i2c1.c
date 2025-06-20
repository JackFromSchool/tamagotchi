#include "i2c1.h"
#include "stm32l010x8.h"

void i2c1_init(void) {
   // Ensure Clocks Enabled
   RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
   RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

   // Ensure Peripherasl Off
   I2C1->CR1 &= ~(I2C_CR1_PE);

   // Configure Pins
   GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD6 | GPIO_PUPDR_PUPD7);
   GPIOB->OSPEEDR =
       (GPIOB->OSPEEDR & ~(GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7)) |
       (GPIO_OSPEEDR_OSPEED6_1 | GPIO_OSPEEDR_OSPEED7_1);
   GPIOB->OTYPER |= (GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7);
   GPIOB->AFR[0] = (GPIOB->AFR[0] & ~(GPIO_AFRL_AFSEL6 | GPIO_AFRL_AFSEL7)) |
                   (0b0001 << GPIO_AFRL_AFSEL6_Pos) |
                   (0b0001 << GPIO_AFRL_AFSEL7_Pos);
   GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE6 | GPIO_MODER_MODE7)) |
                  (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);

   // Configure Peripheral
   I2C1->TIMINGR = (uint32_t)0x00300619;
   I2C1->CR1 = I2C_CR1_PE;
}

void i2c1_blocking_send_bytes(uint8_t addr, uint8_t *buffer, uint32_t size) {
   // Ensure Transmit reg is empty
   while ((I2C1->ISR & I2C_ISR_TXE) != I2C_ISR_TXE)
      ;

   // Preload Transmit register
   I2C1->TXDR = buffer[0];
   // Begin Transmition
   I2C1->CR2 = (I2C1->CR2 & ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RD_WRN)) |
               (I2C_CR2_AUTOEND | I2C_CR2_START | (addr << 1) |
                (size << I2C_CR2_NBYTES_Pos));

   for (uint32_t i = 1; i < size; i++) {
      while ((I2C1->ISR & I2C_ISR_TXE) != I2C_ISR_TXE)
         ;

      I2C1->TXDR = buffer[i];
   }
}
