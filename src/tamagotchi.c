#include "tamagotchi.h"

void tamagotchi_init(void) {
   // Initialize Peripherals
   i2c1_init();
   input_init();

   // Initialize Drivers
   ssd1306_init();

   // Initialize Software
   ui_init();
}
