#ifndef INPUT_H
#define INPUT_H

#include "../ui.h"
#include "stm32l0xx.h"

void input_init(void);
uint8_t input_read(void);

#endif // !INPUT_H
