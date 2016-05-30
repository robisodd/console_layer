#pragma once
#include <pebble.h>
#define CONSOLE_LAYER_MAX_ROWS 21             // PTR is 180px high / (FONT_KEY_GOTHIC_09     = 9px high) = 20 max
#define CONSOLE_LAYER_BUFFER_SIZE_PER_ROW 60  // PTR is 180px wide / (FONT_KEY_GOTHIC_09 'i' = 3px wide) = 60 max

#define WordWrapFalse 0
#define WordWrapTrue 1
#define WordWrapInherit 2

enum {GTextAlignmentInherit = 60};
#define GColorInherit ((GColor8){.argb=GColorClearARGB8})
#define GFontInherit NULL

Layer* console_layer_create               (GRect frame);
void   console_layer_destroy              (Layer *console_layer);
void   console_layer_clear                (Layer *console_layer);
void   console_layer_write_text           (Layer *console_layer, char *text, bool dirty_layer_after_writing);
void   console_layer_write_text_attributes(Layer *console_layer, char *text, GFont font,
                                           GColor text_color, GColor background_color,
                                           GTextAlignment text_alignment,
                                           int word_wrap, bool dirty_layer_after_writing);
// ------------------------------------------------------------------------------------------------------------ //
// Gets
// ------------------------------------------------------------------------------------------------------------ //
//GColor         console_layer_get_border_color                 (Layer *console_layer);
GColor         console_layer_get_background_color             (Layer *console_layer);
GColor         console_layer_get_text_color                   (Layer *console_layer);
GColor         console_layer_get_text_background_color        (Layer *console_layer);
int            console_layer_get_word_wrap                    (Layer *console_layer);
GFont          console_layer_get_font                         (Layer *console_layer);
GTextAlignment console_layer_get_text_alignment               (Layer *console_layer);
GColor         console_layer_get_default_text_color           (Layer *console_layer);
GColor         console_layer_get_default_text_background_color(Layer *console_layer);
bool           console_layer_get_default_word_wrap            (Layer *console_layer);
GFont          console_layer_get_default_font                 (Layer *console_layer);
GTextAlignment console_layer_get_default_text_alignment       (Layer *console_layer);

// ------------------------------------------------------------------------------------------------------------ //
// Sets
// ------------------------------------------------------------------------------------------------------------ //
//void console_layer_set_border_color                 (Layer *console_layer, GColor border_color);
void console_layer_set_background_color             (Layer *console_layer, GColor         background_color);
void console_layer_set_text_color                   (Layer *console_layer, GColor         text_color);
void console_layer_set_text_background_color        (Layer *console_layer, GColor         text_background_color);
void console_layer_set_word_wrap                    (Layer *console_layer, int            word_wrap);
void console_layer_set_font                         (Layer *console_layer, GFont          font);
void console_layer_set_text_alignment               (Layer *console_layer, GTextAlignment text_alignment);
void console_layer_set_default_text_color           (Layer *console_layer, GColor         default_text_color);
void console_layer_set_default_text_background_color(Layer *console_layer, GColor         default_text_background_color);
void console_layer_set_default_word_wrap            (Layer *console_layer, bool           default_word_wrap);
void console_layer_set_default_font                 (Layer *console_layer, GFont          default_font);
void console_layer_set_default_text_alignment       (Layer *console_layer, GTextAlignment default_text_alignment);

void console_layer_set_text_colors                  (Layer *console_layer, GColor text_color, GColor text_background_color);
void console_layer_set_defaults                     (Layer *console_layer, GFont font,
                                                     GColor text_color, GColor text_background_color,
                                                     GColor layer_background_color,// GColor layer_border_color,
                                                     GTextAlignment text_alignment, bool word_wrap);
