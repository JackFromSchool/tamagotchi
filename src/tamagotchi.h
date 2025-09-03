#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H

#include "sprite.h"

struct Tamagotchi {
   struct Sprite sprite;
};

void tamagotchi_init(void);

#endif // !TAMAGOTCHI_H
