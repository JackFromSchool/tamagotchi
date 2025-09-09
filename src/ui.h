#ifndef UI_H
#define UI_H

#include <stdbool.h>
#include <stddef.h>

#include "drivers/ssd1306.h"
#include "sprite.h"
#include "stm32l0xx.h"

void ui_init(void);
void ui_next_icon(void);
void ui_select_icon(void);
void ui_cancel_selection(void);

#endif // !UI_H
