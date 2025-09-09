#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H

#include "hardware/i2c1.h"
#include "hardware/input.h"
#include "sprite.h"
#include "ui.h"

struct Tamagotchi {
   struct Sprite sprite;
};

void tamagotchi_init(void);

#endif // !TAMAGOTCHI_H
