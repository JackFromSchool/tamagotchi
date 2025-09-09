#include "ssd1306.h"
#include <stdint.h>

void ssd1306_send_cmd(uint8_t cmd) {
   uint8_t buf[2] = {0x80, cmd};
   i2c1_blocking_send_bytes(SSD1306_I2C_ADDR, buf, 2);
}

void ssd1306_send_cmd_list(uint8_t *buf, uint32_t len) {
   for (uint32_t i = 0; i < len; i++) {
      ssd1306_send_cmd(buf[i]);
   }
}

void ssd1306_write_data(uint8_t data) {
   uint8_t buf[2] = {0x40, data};
   i2c1_blocking_send_bytes(SSD1306_I2C_ADDR, buf, 2);
}

void ssd1306_init(void) {
   /* clang-format off */
   uint8_t cmds[27] = {
      SET_DISPLAY_ON_OFF,
      SET_MEM_ADDR_MODE,
      0x00,
      SET_DISPLAY_START_LINE,
      SET_SEGMENT_REMAP | 0x01,
      SET_MULTIPLEX_RATIO,
      SSD1306_HEIGHT - 1,
      SET_COM_OUTPUT_SCAN_DIRECTION | 0x08,
      SET_DISPLAY_OFFSET,
      0x00,
      SET_COM_PINS_HARDWARE_CONFIG,
      0x12,
      SET_DISPLAY_CLOCK_DIVIDE,
      0x80,
      SET_PRE_CHARGE_PERIOD,
      0xF1,
      SET_VCOMH_DESLECT_LEVEL,
      0x30,
      SET_CONTRAST_CONTROL,
      0xFF,
      ENTIRE_DISPLAY_ON,
      SET_NORMAL_INVERSE_DISPLAY,
      // NOTE: Don't know what this does but it's in the code I'm basing this
      // off of so I included it.
      0x8D,
      0x14,
      DEACTIVATE_SCROLL,
      SET_DISPLAY_ON_OFF | 0x01,
   };
   /* clang-format on */

   ssd1306_send_cmd_list(cmds, 27);
}

void ssd1306_clear_screen(void) {
   // clang-format off
   uint8_t set_address_mode[] = {
      SET_MEM_ADDR_MODE,
      0b01,
      SET_PAGE_ADDR,
      SSD1306_START_PAGE,
      SSD1306_END_PAGE,
      SET_COL_ADDR,
      SSD1306_START_COL,
      SSD1306_END_COL,
   };
   // clang-format on

   ssd1306_send_cmd_list(set_address_mode, sizeof(set_address_mode));

   for (uint32_t i = 0; i <= SSD1306_END_COL; i++) {
      for (uint32_t j = 0; j <= SSD1306_END_PAGE; j++) {
         ssd1306_write_data(0x00);
      }
   }
}

void ssd1306_test(void) {
   ssd1306_clear_screen();
   while (1) {
      ssd1306_send_cmd(ENTIRE_DISPLAY_ON | 0x1);
      delay_ms(1000);
      ssd1306_send_cmd(ENTIRE_DISPLAY_ON);
      delay_ms(1000);
   }
}

void ssd1306_draw_sprite(struct Sprite *sprite) {
   // Get Local Coordinates
   uint8_t column_start = sprite->x_pos;
   uint8_t column_end = sprite->x_pos + sprite->width - 1;
   uint8_t page_start = (sprite->y_pos) >> 3;
   uint8_t page_end = (sprite->y_pos + sprite->height - 1) >> 3;

   // Set Up Write
   uint8_t set_address_mode[] = {
       SET_MEM_ADDR_MODE, 0b00,         SET_PAGE_ADDR, page_start,
       page_end,          SET_COL_ADDR, column_start,  column_end,
   };

   ssd1306_send_cmd_list(set_address_mode, sizeof(set_address_mode));

   // Begin Writing
   uint32_t index = 0;
   for (uint32_t page = page_start; page <= page_end; page++) {
      for (uint32_t column = column_start; column <= column_end; column++) {
         ssd1306_write_data(sprite->data[index++]);
      }
   }
}

void ssd1306_draw_2sprite_or(struct Sprite *base, struct Sprite *second) {
   // Get Local Coordinates
   uint8_t column_start = base->x_pos;
   uint8_t column_end = base->x_pos + base->width - 1;
   uint8_t page_start = (base->y_pos) >> 3;
   uint8_t page_end = (base->y_pos + base->height - 1) >> 3;

   // Set Up Write
   uint8_t set_address_mode[] = {
       SET_MEM_ADDR_MODE, 0b00,         SET_PAGE_ADDR, page_start,
       page_end,          SET_COL_ADDR, column_start,  column_end,
   };

   ssd1306_send_cmd_list(set_address_mode, sizeof(set_address_mode));

   // Begin Writing
   uint32_t index = 0;
   for (uint32_t page = page_start; page <= page_end; page++) {
      for (uint32_t column = column_start; column <= column_end; column++) {
         ssd1306_write_data(base->data[index] | second->data[index]);
         index++;
      }
   }
}
