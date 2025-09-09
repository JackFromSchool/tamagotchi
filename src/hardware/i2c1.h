#ifndef I2C1_H
#define I2C1_H

#include "stm32l0xx.h"

void i2c1_init(void);
void i2c1_blocking_send_bytes(uint8_t addr, uint8_t *buffer, uint32_t size);

#endif
