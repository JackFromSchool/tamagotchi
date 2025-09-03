#ifndef INPUT_H
#define INPUT_H

#include "sprite.h"
#include "ssd1306.h"
#include "stm32l0xx.h"

void input_init(void);
uint8_t input_read(void);

#endif // !INPUT_H
