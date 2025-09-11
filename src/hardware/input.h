#ifndef INPUT_H
#define INPUT_H

#include "stm32l0xx.h"

void input_init(void);
uint8_t input_read(void);

void input_register_callback(void (*callback)(uint8_t));

#endif // !INPUT_H
