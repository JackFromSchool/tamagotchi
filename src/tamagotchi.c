#include "tamagotchi.h"
#include "i2c1.h"
#include "input.h"

void tamagotchi_init(void) {
   // Initialize Hardware

   i2c1_init();
   init_inputs();
}
