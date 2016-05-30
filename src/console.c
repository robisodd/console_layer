#include "console.h"
#include <pebble.h>

// ------------------------------------------------------------------------------------------------------------ //
//  Data Structure
// ------------------------------------------------------------------------------------------------------------ //

typedef struct console_row_struct {
  char   row_text[CONSOLE_LAYER_BUFFER_SIZE_PER_ROW + 1];
  GColor text_background_color;       // Set to GColorInherit to inherit default background
  GColor text_color;                  // Set to GColorInherit to inherit default text color
  GFont  font;                        // Set to GFontInherit to inherit default layer font
  int    text_alignment;              // Set to GTextAlignmentInherit to inherit default text alignment
  int    word_wrap;                   // true or false. Or WordWrapInherit to inherit default layer word wrap
} console_row_struct;

typedef struct console_data_struct {
  //GColor           console_layer_border_color;
  //int              console_layer_border_thickness;
  //bool             console_layer_border;
  //GColor           console_layer_header_background_color;
  //GColor           console_layer_header_text_color;
  //GFont            console_layer_header_font;
  //GTextAlignment   console_layer_header_text_alignment;
  //bool             console_layer_header;
  GColor             console_layer_background_color;
  GColor             default_text_background_color;
  GColor             default_text_color;
  GFont              default_font;
  GTextAlignment     default_text_alignment;
  bool               default_word_wrap;
  console_row_struct console_row[CONSOLE_LAYER_MAX_ROWS];
  int                current_row;
} console_data_struct;

// static console_data_struct *get_console_data(Layer *console_layer) {
//   return (console_data_struct*)layer_get_data(console_layer);
// }
  
// ------------------------------------------------------------------------------------------------------------ //
// Draw Layer
// ------------------------------------------------------------------------------------------------------------ //
static void console_layer_update(Layer *console_layer, GContext *ctx) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  GRect frame = layer_get_frame(console_layer);
  
  // Layer Background
  if(console_data->console_layer_background_color.argb!=GColorClear.argb) {
    graphics_context_set_fill_color(ctx, console_data->console_layer_background_color);
    graphics_fill_rect(ctx, (GRect){.origin = GPoint(0, 0), .size = frame.size}, 0, GCornerNone);
  }
  
  // Display Rows
  int16_t y = frame.size.h, row = (console_data->current_row - 1 + CONSOLE_LAYER_MAX_ROWS) % CONSOLE_LAYER_MAX_ROWS, row_height;
  while(y>0 && console_data->console_row[row].row_text[0]!=0) {
    char *text = console_data->console_row[row].row_text;
    GFont font = console_data->console_row[row].font ? console_data->console_row[row].font : console_data->default_font;
    GTextAlignment alignment = console_data->console_row[row].text_alignment == GTextAlignmentInherit ? console_data->default_text_alignment : console_data->console_row[row].text_alignment;
    bool word_wrap = console_data->console_row[row].word_wrap == WordWrapInherit ? console_data->default_word_wrap : console_data->console_row[row].word_wrap;
    
    if(word_wrap)
      row_height = graphics_text_layout_get_content_size(text, font, frame, GTextOverflowModeTrailingEllipsis, alignment).h;
    else
      row_height = graphics_text_layout_get_content_size("0", font, frame, GTextOverflowModeTrailingEllipsis, alignment).h;
    
    y -= row_height;

    if(console_data->console_row[row].text_background_color.argb!=GColorClear.argb) {
      graphics_context_set_fill_color(ctx, console_data->console_row[row].text_background_color);
      graphics_fill_rect(ctx, GRect(0, y, frame.size.w, row_height), 0, GCornerNone);
    }

    graphics_context_set_text_color(ctx, console_data->console_row[row].text_color.argb ? console_data->console_row[row].text_color : console_data->default_text_color);
    graphics_draw_text(ctx, text, font, GRect(0, y - 3, frame.size.w, row_height), GTextOverflowModeTrailingEllipsis, alignment, NULL);  // y-3 because Pebble's text rendering goes outside rect

    row = (row - 1 + CONSOLE_LAYER_MAX_ROWS) % CONSOLE_LAYER_MAX_ROWS;
  }
  
  // Draw Border
//   if(console_data->console_layer_border_color.argb!=GColorClear.argb) {
//     graphics_context_set_stroke_color(ctx, console_data->console_layer_border_color);
//     graphics_draw_rect(ctx, (GRect){.origin = GPoint(0, 0), .size = frame.size});
//   }
}

// ------------------------------------------------------------------------------------------------------------ //
// Create and Destroy Layer
// ------------------------------------------------------------------------------------------------------------ //
Layer* console_layer_create(GRect frame) {
  Layer *console_layer;
  size_t buffer_size = sizeof (console_data_struct);
  
  if((console_layer = layer_create_with_data(frame, buffer_size))) {
    layer_set_clips(console_layer, true);
    console_layer_set_defaults(console_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14), GColorBlack, GColorClear, GColorClear, GTextAlignmentLeft, false);
    console_layer_clear(console_layer);
    layer_set_update_proc(console_layer, console_layer_update);
  }
  return console_layer;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_destroy(Layer *console_layer) {
  layer_destroy(console_layer);
}



// ------------------------------------------------------------------------------------------------------------ //
// Gets
// ------------------------------------------------------------------------------------------------------------ //
// GColor         console_layer_get_border_color                (Layer *console_layer) {
//   return ((console_data_struct*)layer_get_data(console_layer))->console_layer_border_color;
// }
// ------------------------------------------------------------------------------------------------------------ //
GColor         console_layer_get_background_color             (Layer *console_layer) {
  return ((console_data_struct*)layer_get_data(console_layer))->console_layer_background_color;
}
// ------------------------------------------------------------------------------------------------------------ //
GColor         console_layer_get_default_text_color           (Layer *console_layer) {
  return ((console_data_struct*)layer_get_data(console_layer))->default_text_color;
}
// ------------------------------------------------------------------------------------------------------------ //
GColor         console_layer_get_default_text_background_color(Layer *console_layer) {
  return ((console_data_struct*)layer_get_data(console_layer))->default_text_background_color;}
// ------------------------------------------------------------------------------------------------------------ //
bool           console_layer_get_default_word_wrap            (Layer *console_layer) {
  return ((console_data_struct*)layer_get_data(console_layer))->default_word_wrap;
}
// ------------------------------------------------------------------------------------------------------------ //
GTextAlignment console_layer_get_default_text_alignment       (Layer *console_layer) {
  return ((console_data_struct*)layer_get_data(console_layer))->default_text_alignment;
}
// ------------------------------------------------------------------------------------------------------------ //
GFont          console_layer_get_default_font                 (Layer *console_layer) {
  return ((console_data_struct*)layer_get_data(console_layer))->default_font;
}
// ------------------------------------------------------------------------------------------------------------ //
GColor         console_layer_get_text_color                   (Layer *console_layer) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  return console_data->console_row[console_data->current_row].text_color;
}
// ------------------------------------------------------------------------------------------------------------ //
GColor         console_layer_get_text_background_color        (Layer *console_layer) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  return console_data->console_row[console_data->current_row].text_background_color;
}
// ------------------------------------------------------------------------------------------------------------ //
int            console_layer_get_word_wrap                    (Layer *console_layer) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  return console_data->console_row[console_data->current_row].word_wrap;
}
// ------------------------------------------------------------------------------------------------------------ //
GTextAlignment console_layer_get_text_alignment               (Layer *console_layer) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  return console_data->console_row[console_data->current_row].text_alignment;
}
// ------------------------------------------------------------------------------------------------------------ //
GFont          console_layer_get_font                         (Layer *console_layer) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  return console_data->console_row[console_data->current_row].font;
}


// ------------------------------------------------------------------------------------------------------------ //
// Sets
// ------------------------------------------------------------------------------------------------------------ //
// void console_layer_set_border_color                 (Layer *console_layer, GColor border_color) {
//   ((console_data_struct*)layer_get_data(console_layer))->console_layer_border_color = border_color;
// }
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_background_color             (Layer *console_layer, GColor background_color) {
  ((console_data_struct*)layer_get_data(console_layer))->console_layer_background_color = background_color;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_default_text_color           (Layer *console_layer, GColor default_text_color) {
  ((console_data_struct*)layer_get_data(console_layer))->default_text_color = default_text_color;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_default_text_background_color(Layer *console_layer, GColor default_text_background_color) {
  ((console_data_struct*)layer_get_data(console_layer))->default_text_background_color = default_text_background_color;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_word_wrap                    (Layer *console_layer, int word_wrap) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->console_row[console_data->current_row].word_wrap = word_wrap;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_default_word_wrap            (Layer *console_layer, bool default_word_wrap) {
  ((console_data_struct*)layer_get_data(console_layer))->default_word_wrap = default_word_wrap;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_font                         (Layer *console_layer, GFont font) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->console_row[console_data->current_row].font = font;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_default_font                 (Layer *console_layer, GFont default_font) {
  ((console_data_struct*)layer_get_data(console_layer))->default_font = default_font;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_text_alignment               (Layer *console_layer, GTextAlignment text_alignment) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->console_row[console_data->current_row].text_alignment = text_alignment;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_default_text_alignment       (Layer *console_layer, GTextAlignment default_text_alignment) {
  ((console_data_struct*)layer_get_data(console_layer))->default_text_alignment = default_text_alignment;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_text_color                   (Layer *console_layer, GColor text_color) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->console_row[console_data->current_row].text_color = text_color;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_text_background_color        (Layer *console_layer, GColor text_background_color) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->console_row[console_data->current_row].text_background_color = text_background_color;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_text_colors                  (Layer *console_layer, GColor text_color, GColor text_background_color) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->console_row[console_data->current_row].text_color = text_color;
  console_data->console_row[console_data->current_row].text_background_color = text_background_color;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_set_defaults(Layer *console_layer, GFont font, GColor default_text_color, GColor default_text_background_color,
                                GColor layer_background_color, GTextAlignment text_alignment, bool word_wrap) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->default_text_color             = default_text_color;
  console_data->default_text_background_color  = default_text_background_color;
  console_data->console_layer_background_color = layer_background_color;
  //console_data->console_layer_border_color     = layer_border_color;
  console_data->default_font                   = font;
  console_data->default_word_wrap              = word_wrap;
  console_data->default_text_alignment         = text_alignment;
}


// ------------------------------------------------------------------------------------------------------------ //
// Write Layer
// ------------------------------------------------------------------------------------------------------------ //
// do the 10 thing cause else wordwrap=false hides multi-lines
void console_layer_write_text(Layer *console_layer, char *text, bool dirty_layer_after_writing) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  while (*text!=0) {
    int i = 0;
    while(*text!=0 && *text!=10) {
      if((*text)>=32 && (*text)<=127 && i<CONSOLE_LAYER_BUFFER_SIZE_PER_ROW)        // if printable character and not at end of row_text
        console_data->console_row[console_data->current_row].row_text[i++] = *text; // then add it
      text++;
    }
    if((*text)==10) {
      text++;            // if *text=10 (i.e "\n"), move to next character.  else it'll get stuck in a loop
      if(i==0) console_data->console_row[console_data->current_row].row_text[i++] = 32;  // To display \n blank lines
    }
    console_data->console_row[console_data->current_row].row_text[i] = 0;           // terminate row's text
    
    int new_row = (console_data->current_row + 1) % CONSOLE_LAYER_MAX_ROWS;
    console_data->console_row[new_row].font                  = console_data->console_row[console_data->current_row].font;
    console_data->console_row[new_row].text_color            = console_data->console_row[console_data->current_row].text_color;
    console_data->console_row[new_row].text_background_color = console_data->console_row[console_data->current_row].text_background_color;
    console_data->console_row[new_row].word_wrap             = console_data->console_row[console_data->current_row].word_wrap;
    console_data->console_row[new_row].text_alignment        = console_data->console_row[console_data->current_row].text_alignment;
    console_data->console_row[new_row].row_text[0] = 0;
    console_data->current_row = new_row;
  }

  if(dirty_layer_after_writing)
    layer_mark_dirty(console_layer);
}
/*
void console_layer_write_text(Layer *console_layer, char *text, bool dirty_layer_after_writing) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  int i = 0;
  while (*text!=0) {
    if ((((*text)>=32 && (*text)<=127) || (*text==10)) && i<CONSOLE_LAYER_BUFFER_SIZE_PER_ROW)        // if printable character and not at end of row_text
      console_data->console_row[console_data->current_row].row_text[i++] = *text; // then add it
    text++;
  }
  console_data->console_row[console_data->current_row].row_text[i] = 0;           // terminate row's text

  int new_row = (console_data->current_row + 1) % CONSOLE_LAYER_MAX_ROWS;
  console_data->console_row[new_row].font                  = console_data->console_row[console_data->current_row].font;
  console_data->console_row[new_row].text_color            = console_data->console_row[console_data->current_row].text_color;
  console_data->console_row[new_row].text_background_color = console_data->console_row[console_data->current_row].text_background_color;
  console_data->console_row[new_row].word_wrap             = console_data->console_row[console_data->current_row].word_wrap;
  console_data->console_row[new_row].text_alignment        = console_data->console_row[console_data->current_row].text_alignment;
  console_data->console_row[new_row].row_text[0] = 0;
  console_data->current_row = new_row;

  if(dirty_layer_after_writing)
    layer_mark_dirty(console_layer);
}
*/
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_write_text_attributes(Layer *console_layer, char *text, GFont font, GColor text_color, GColor background_color, GTextAlignment text_alignment, int word_wrap, bool dirty_layer_after_writing) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  
  GColor old_text_background_color = console_data->console_row[console_data->current_row].text_background_color;
  GColor old_text_color            = console_data->console_row[console_data->current_row].text_color;
  GFont  old_font                  = console_data->console_row[console_data->current_row].font;
  int    old_word_wrap             = console_data->console_row[console_data->current_row].word_wrap;
  int    old_text_alignment        = console_data->console_row[console_data->current_row].text_alignment;

  console_layer_set_word_wrap(console_layer, word_wrap);
  console_layer_set_font(console_layer, font);
  console_layer_set_text_colors(console_layer, text_color, background_color);
  console_layer_set_text_alignment(console_layer, text_alignment);
  console_layer_write_text(console_layer, text, dirty_layer_after_writing);

  console_data->console_row[console_data->current_row].font                  = old_font;
  console_data->console_row[console_data->current_row].text_color            = old_text_color;
  console_data->console_row[console_data->current_row].text_background_color = old_text_background_color;
  console_data->console_row[console_data->current_row].word_wrap             = old_word_wrap;
  console_data->console_row[console_data->current_row].text_alignment        = old_text_alignment;
}
// ------------------------------------------------------------------------------------------------------------ //
void console_layer_clear(Layer *console_layer) {
  console_data_struct *console_data = (console_data_struct*)layer_get_data(console_layer);
  console_data->current_row = 0;
  for(int i=0; i<CONSOLE_LAYER_MAX_ROWS; ++i) {
    console_data->console_row[i].row_text[0] = 0;
    console_data->console_row[i].text_background_color = GColorInherit;
    console_data->console_row[i].text_color            = GColorInherit;
    console_data->console_row[i].font                  = GFontInherit;
    console_data->console_row[i].text_alignment        = GTextAlignmentInherit;
    console_data->console_row[i].word_wrap             = WordWrapInherit;
  }
}
// ------------------------------------------------------------------------------------------------------------ //