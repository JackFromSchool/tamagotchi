#ifndef SSD1306_H
#define SSD1306_H

#include "../delay.h"
#include "../hardware/i2c1.h"
#include "../sprite.h"
#include "stm32l0xx.h"

#define SSD1306_START_PAGE 0
#define SSD1306_END_PAGE 7
#define SSD1306_START_COL 0
#define SSD1306_END_COL 127

#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_HEIGHT 64
#define SSD1306_WIDTH 128

/**
 *  An SSD1306 Command.
 *  X is always the command and all other data needed after is ordered
 * alphabetically.
 */
enum SSD_CMD {
   /**
    *   Sets Contrast from 1 to 256.
    *   Params:
    *   - A[7:0] Contrast Value
    */
   SET_CONTRAST_CONTROL = (uint8_t)0x81,

   /**
    *   Selects between using RAM to display or ignoring and outputting all on.
    *   Params:
    *   - X[0] 0b use ram, 1b entire display on
    */
   ENTIRE_DISPLAY_ON = (uint8_t)0xA4,

   /**
    *   Selects between normal or inverse mode.
    *   Params:
    *   - X[0] 0b normal (0 = off, 1 = on), 1b inverse (0 = on, 1 = off)
    */
   SET_NORMAL_INVERSE_DISPLAY = (uint8_t)0xA6,

   /**
    *   Turn display on or off.
    *   Params:
    *   - X[0] 0b display off, 1b display on
    */
   SET_DISPLAY_ON_OFF = (uint8_t)0xAE,

   // TODO: probabaly should document these
   HORIZONTAL_SCROLL_SETUP = (uint8_t)0x26,
   VERTICAL_HORRIZONTAL_SCROLL_SETUP = (uint8_t)0x28,
   DEACTIVATE_SCROLL = (uint8_t)0x2E,
   ACTIVATE_SCROLL = (uint8_t)0x2F,
   SET_VERTICAL_SCROLL_AREA = (uint8_t)0xA3,

   /**
    *   Sets the lower nibble of the column start address register for page
    * addressing mode.
    *   Params:
    *   - X[3:0] Lower Nibble
    */
   SET_LOW_COL_START_ADDR_PAGE = (uint8_t)0x00,

   /**
    *   Sets the higher nibble of the column start address register for page
    * addressing mode.
    *   Params:
    *   - X[3:0] Higher Nibble
    */
   SET_HIG_COL_START_ADDR_PAGE = (uint8_t)0x10,

   /**
    *   Sets the memory addressing mode.
    *   Params:
    *   - A[1:0] 00b horizontal, 01b vertical, 10b page, 11b invalid
    */
   SET_MEM_ADDR_MODE = (uint8_t)0x20,

   /**
    *   Sets the column start and end address for horizontal and vertical
    * addressing mode
    *   Params:
    *   - A[6:0] column start address
    *   - B[6:0] column end address
    */
   SET_COL_ADDR = (uint8_t)0x21,

   /**
    *   Sets the page start and end address for horizontal and vertical
    * addressing mode.
    *   Params:
    *   - A[2:0] page start address
    *   - B[2:0] page end address
    */
   SET_PAGE_ADDR = (uint8_t)0x22,

   /**
    *   Sets the GDDRAM page start address for page addressing mode.
    *   Params:
    *   - X[2:0] page start address
    */
   SET_PAGE_START_ADDR_PAGE = (uint8_t)0xB0,

   /**
    *   Sets the display RAM start line register.
    *   Params:
    *   - X[5:0] display ram start register
    */
   SET_DISPLAY_START_LINE = (uint8_t)0x40,

   /**
    *   Remaps segments.
    *   Params:
    *   - X[0] 0b column address 0 maps to SEG0, 1b column address 127 maps to
    * SEG0
    */
   SET_SEGMENT_REMAP = (uint8_t)0xA0,

   /**
    *    Sets MUX ratio to N + 1 MUX
    *    Params:
    *    - A[5:0] set mux from 16 to 64, 0 to 14 are invalid
    */
   SET_MULTIPLEX_RATIO = (uint8_t)0xA8,

   /**
    *    Sets COM output scan direction.
    *    Params:
    *    - X[3] 0b normal mode (scan COM0 to COM[n-1]), 1b remapped mode
    * (reverse)
    */
   SET_COM_OUTPUT_SCAN_DIRECTION = (uint8_t)0xC0,

   /**
    *    Set the vertical shift my COM.
    *    Params:
    *    - A[5:0] vertical shift
    */
   SET_DISPLAY_OFFSET = (uint8_t)0xD3,

   /**
    *    Set the COM pins hardware config.
    *    Params:
    *    - A[4] 0b sequential config, 1b alternative config,
    *    - A[5] 0b disable com l/r remap, 1b enable com l/r remap
    */
   SET_COM_PINS_HARDWARE_CONFIG = (uint8_t)0xDA,

   /**
    *   Sets the display clock divide ratio/oscillator frequency.
    *   Params:
    *   - A[3:0] divide ratio a[3:0] + 1
    *   - A[7:4] oscillator frequency
    */
   SET_DISPLAY_CLOCK_DIVIDE = (uint8_t)0xD5,

   /**
    *    Sets pre-charge period.
    *    Params:
    *    - A[3:0] phase 1 period (0 invalid)
    *    - A[7:4] phase 2 period (0 invalid)
    */
   SET_PRE_CHARGE_PERIOD = (uint8_t)0xD9,

   SET_VCOMH_DESLECT_LEVEL = (uint8_t)0xDB,

   NOP = (uint8_t)0xE3,

};

void ssd1306_send_cmd(uint8_t cmd);
void ssd1306_send_cmd_list(uint8_t *buf, uint32_t len);

void ssd1306_init(void);
void ssd1306_test(void);
void ssd1306_clear_screen(void);
void ssd1306_draw_sprite(struct Sprite *sprite);
void ssd1306_draw_2sprite_or(struct Sprite *base, struct Sprite *second);

#endif
