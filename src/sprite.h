#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>

struct Sprite {
   const uint8_t *data;
   const uint8_t width;
   const uint8_t height;
   uint8_t x_pos;
   uint8_t y_pos;
};

// Sprites
extern struct Sprite icon_attention;
extern struct Sprite icon_food;
extern struct Sprite icon_game;
extern struct Sprite icon_scale;
extern struct Sprite icon_toilet;
extern struct Sprite icon_lights;
extern struct Sprite icon_medicine;
extern struct Sprite icon_discipline;
extern struct Sprite icon_selected;

#endif // !SPRITE_H
