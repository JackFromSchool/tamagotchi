#include "ui.h"
#include "sprite.h"
#include "ssd1306.h"

#define NO_SELECTION 255U

static struct Sprite *const selection_list[] = {
    &icon_food,   &icon_lights, &icon_game,      &icon_medicine,
    &icon_toilet, &icon_scale,  &icon_discipline};

static uint8_t selected_sprite = NO_SELECTION;

void ui_redraw(void) {
   ssd1306_draw_sprite(&icon_food);
   ssd1306_draw_sprite(&icon_lights);
   ssd1306_draw_sprite(&icon_game);
   ssd1306_draw_sprite(&icon_medicine);
   ssd1306_draw_sprite(&icon_toilet);
   ssd1306_draw_sprite(&icon_scale);
   ssd1306_draw_sprite(&icon_discipline);
   ssd1306_draw_sprite(&icon_attention);
}

void ui_init(void) { ui_redraw(); }

void ui_next_icon(void) {
   if (selected_sprite == NO_SELECTION) {
      selected_sprite = 0;
      ssd1306_draw_2sprite_or(selection_list[selected_sprite], &icon_selected);
      // TODO: Begin Countdown to NO_SELECTION
   } else {
      ssd1306_draw_sprite(selection_list[selected_sprite]);

      if (++selected_sprite == 7)
         selected_sprite = 0;

      ssd1306_draw_2sprite_or(selection_list[selected_sprite], &icon_selected);
   }
}

void ui_select_icon(void);

void ui_cancel_selection(void) {
   if (selected_sprite != NO_SELECTION) {
      ssd1306_draw_sprite(selection_list[selected_sprite]);
      selected_sprite = NO_SELECTION;
   }
}
