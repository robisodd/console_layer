#pragma once
#include <pebble.h>
#include "console.h"
#include <pebble.h>

// char screentext[18*21]="initializing...";
// uint8_t textcolor[18*21];  // foreground text color
// uint8_t backcolor[18*21];  // background text color
//4x6 pixel Font
//#define MAX_ROWS 28
//#define MAX_COLS 35 // Technically 36, but skipping bottom row due to corner mask.

/*
void draw_sprite4(uint8_t *fb, uint8_t *font, int16_t start_x, int16_t start_y, uint8_t color, uint8_t background_color, uint8_t spr) {  // in B&W, color=0 is black, else white
  uint16_t left   = (start_x <     0) ? (start_x >  -4) ?   0 - start_x : 4 : 0;
  uint16_t right  = (start_x > 144-4) ? (start_x < 144) ? 144 - start_x : 0 : 4;
  uint16_t top    = (start_y <     0) ? (start_y >  -6) ?   0 - start_y : 6 : 0;
  uint16_t bottom = (start_y > 168-6) ? (start_y < 168) ? 168 - start_y : 0 : 6;
  uint8_t    *row = font + (spr>>1);//(spr>>3);// + (top*64);
  uint16_t y_addr = (start_y + top) * PBL_IF_COLOR_ELSE(144, 20);
  uint8_t mask = (spr & 1) ? 8 : 128;
    
  for(uint16_t y=top; y<bottom; ++y) {
   for(uint16_t x=left; x<right; ++x) {
//   for(uint16_t y=0; y<6; ++y) {
//     for(uint16_t x=0; x<4; ++x) {
      #ifdef PBL_BW
        //fb[y_addr + ((start_x+x) >> 3)] &= ~(1 << ((start_x+x)&7)); // Black Background (comment both out for clear background)
        //fb[y_addr + ((start_x+x) >> 3)] |=  (1 << ((start_x+x)&7)); // White Background (comment both out for clear background)
        //if(color)
        //  fb[y_addr + ((start_x+x) >> 3)] |=  ((((*row>>x)&1)) << ((start_x+x)&7)); // White Pixel
        //else
        //  fb[y_addr + ((start_x+x) >> 3)] &= ~((((*row>>x)&1)) << ((start_x+x)&7)); // Black Pixel
      #else
        //if((*row>>x)&1)   // horizontally flipped
        if((*row&(mask>>x))) // normal
          fb[y_addr + start_x + x] = color;
        else
          fb[y_addr + start_x + x] = background_color;
      #endif
    }
    y_addr += PBL_IF_COLOR_ELSE(144, 20);
    row += 64;
  }
}
*/
// void draw_font4_text(uint8_t *fb, int16_t x, int16_t y, uint8_t color, char *str) { // str points to zero-terminated string
//   uint8_t strpos=0;
//   while(str[strpos]>0) {
//     if(x>(144-4)) {x=0; y+=6;}  // wrap horizontally
//     if(y>(168-6)) y=0;          // wrap vertically
//     draw_sprite4(fb, font4, x, y, color, str[strpos]);
//     x+=4; strpos++;
//   }
// }

// void draw_screen_text(uint8_t *fb) {
//   uint16_t strpos=0;
//   for(uint16_t y=0; y<MAX_ROWS; ++y) {
//     for(uint16_t x=0; x<MAX_COLS; ++x) {
//       draw_sprite4(fb, font4, x*4, y*6, textcolor[strpos], backcolor[strpos], screentext[strpos]);
//       ++strpos;
//     }
//   }
// }
//GBitmap *font4_bmp; uint8_t *font4;
//  font4_bmp = gbitmap_create_with_resource(RESOURCE_ID_FONT4); font4 = gbitmap_get_data(font4_bmp);
//  gbitmap_destroy(font4_bmp);





/*



//8x8 pixel font
#define MAX_ROWS 21
#define MAX_COLS 18

char buffer[256];
GBitmap *font8_bmp = NULL; uint8_t *font8 = NULL;
// First byte is options
// 0bA-------:
//  A: word_wrap
//  B:
//  C:
//  D:
//  E:
//  F:
//  G:
//  H:
// 2nd & 3rd bytes are default colors
// Default colors = White text on Black

// The bulk of the bytes are as follows:
//   0b0xxxxxxx: ASCII 0-127
//   0b10rrggbb: Change Background Color
//   0b11rrggbb: Change Foreground Color

// 8x8: 18w x 21h = 378 bytes
// 6x8: 24w x 21h = 504 bytes
typedef struct console_data_struct {
  char *text;
  bool word_wrap;
  
} console_data_struct;

static uint8_t console[1024] = "\xFF\x80initializing...\n\nnow...";

//char screentext[MAX_ROWS*MAX_COLS] = "initializing...";
//uint8_t textcolor[MAX_ROWS*MAX_COLS];  // foreground text color
//uint8_t backcolor[MAX_ROWS*MAX_COLS];  // background text color

void draw_sprite8(uint8_t *fb, uint8_t *font, int16_t start_x, int16_t start_y, uint8_t color, uint8_t background_color, uint8_t spr) {  // in B&W, color=0 is black, else white
  uint16_t left   = (start_x <     0) ? (start_x >  -8) ?   0 - start_x : 8 : 0;
  uint16_t right  = (start_x > 144-8) ? (start_x < 144) ? 144 - start_x : 0 : 8;
  uint16_t top    = (start_y <     0) ? (start_y >  -8) ?   0 - start_y : 8 : 0;
  uint16_t bottom = (start_y > 168-8) ? (start_y < 168) ? 168 - start_y : 0 : 8;
  uint8_t    *row = font + (spr&3) + ((spr&252)*8) + (top*4);
  uint16_t y_addr = (start_y + top) * PBL_IF_COLOR_ELSE(144, 20);

  for(uint16_t y=top; y<bottom; ++y) {
    for(uint16_t x=left; x<right; ++x) {
      #ifdef PBL_BW
        if(color&0b00111111) {
          fb[y_addr + ((start_x+x) >> 3)] &= ~(1 << ((start_x+x)&7)); // Black Background (comment out for clear background)
          fb[y_addr + ((start_x+x) >> 3)] |=  ((((*row>>x)&1)) << ((start_x+x)&7)); // White Pixel
        } else {
          fb[y_addr + ((start_x+x) >> 3)] |=  (1 << ((start_x+x)&7)); // White Background (comment out for clear background)
          fb[y_addr + ((start_x+x) >> 3)] &= ~((((*row>>x)&1)) << ((start_x+x)&7)); // Black Pixel
        }
      #else
        //if((*row>>x)&1)   // horizontally flipped
        if((*row&(128>>x))) // normal
          fb[y_addr + start_x + x] = color;
        else
          fb[y_addr + start_x + x] = background_color;
      #endif
    }
    y_addr += PBL_IF_COLOR_ELSE(144, 20);
    row += 4;
  }
}

void draw_screen_text(uint8_t *fb) {
  uint16_t strpos=0;
  for(uint16_t y=0; y<21; ++y) {
    for(uint16_t x=0; x<18; ++x) {
      draw_sprite8(fb, font8, x*8, y*8, textcolor[strpos], backcolor[strpos], screentext[strpos]);
      ++strpos;
    }
  }
}
void draw_screen_text(uint8_t *fb) {
  uint16_t strpos=0;
  uint8_t text_color = 0b11111111;
  uint8_t back_color = 0b11111111;
  uint16_t y=0, x=0;
  while (true) {
    
    if(y>=21)
      return;
  }
  for(uint16_t y=0; y<21; ++y) {
    for(uint16_t x=0; x<18; ++strpos) {
      if(console[strpos]&0b10000000) {
        
      } else {
        draw_sprite8(fb, font8, x*8, y*8, text_color, back_color, console[strpos]);
        ++x;
      }
      
    }
  }
}

void move_screen_text_up_one_line(Layer *console_layer) {
  for(uint16_t y=0; y<MAX_ROWS-1; ++y) {
    for(uint16_t x=0; x<MAX_COLS; ++x) {
      screentext[y*MAX_COLS+x] = screentext[(y+1)*MAX_COLS+x];
       textcolor[y*MAX_COLS+x] =  textcolor[(y+1)*MAX_COLS+x];
       backcolor[y*MAX_COLS+x] =  backcolor[(y+1)*MAX_COLS+x];
    }
  }
  for(uint16_t x=0; x<MAX_COLS; ++x) {
    screentext[(MAX_ROWS-1)*MAX_COLS + x] = ' ';
     textcolor[(MAX_ROWS-1)*MAX_COLS + x] = 0b11000000;
     backcolor[(MAX_ROWS-1)*MAX_COLS + x] = 0b11000000;
  }
//   layer_mark_dirty(console_layer);
}

void add_text(Layer *console_layer, char *str, uint8_t color, uint8_t bgcolor) { // TOFIX: Buffer Overrun possibility
  uint16_t strpos=0, x=MAX_COLS;
  while(str[strpos]>0 && strpos<255) {
    if(x==MAX_COLS) {
      x=0;
      move_screen_text_up_one_line(console_layer);
    }
    if(str[strpos]==10 || str[strpos]==13) {  // if CR or LF
      if(x>0)
        for(; x<MAX_COLS; ++x) {
          screentext[(MAX_ROWS-1)*MAX_COLS+x] = ' ';
           textcolor[(MAX_ROWS-1)*MAX_COLS+x] = color;
           backcolor[(MAX_ROWS-1)*MAX_COLS+x] = bgcolor;
        }
    } else {
      screentext[(MAX_ROWS-1)*MAX_COLS+x] = str[strpos];
       textcolor[(MAX_ROWS-1)*MAX_COLS+x] = color;
       backcolor[(MAX_ROWS-1)*MAX_COLS+x] = bgcolor;
      x++;
    }
    strpos++;
  }
  for(; x<MAX_COLS; ++x) {
    screentext[(MAX_ROWS-1)*MAX_COLS+x] = ' ';
     textcolor[(MAX_ROWS-1)*MAX_COLS+x] = color;
     backcolor[(MAX_ROWS-1)*MAX_COLS+x] = bgcolor;
  }
}

static void console_layer_update(Layer *console_layer, GContext *ctx) {
  uint8_t *framebuffer = (uint8_t*)*(size_t*)ctx;
  draw_screen_text(framebuffer);
}

Layer* console_layer_create(GRect frame) {
  static Layer *console_layer;
  size_t buffer_size = 100;
  console_layer = layer_create_with_data(frame, buffer_size);
  //void* layer_get_data(const Layer *layer)
  layer_set_update_proc(console_layer, console_layer_update);
  if(!font8) {
    font8_bmp = gbitmap_create_with_resource(RESOURCE_ID_FONT8);
    font8 = gbitmap_get_data(font8_bmp);
  }
  return console_layer;
}

void console_layer_destroy(Layer *console_layer) {
  layer_destroy(console_layer);
  //if(font8) {gbitmap_destroy(font8_bmp); font8 = NULL;}
}

void console_layer_set_colors(Layer *console_layer, GColor text_color, GColor background_color) {
  
}

void console_layer_set_default_colors(Layer *console_layer, GColor text_color, GColor background_color) {
  
}

void console_layer_write_text_color(Layer *console_layer, char *text, bool dirty_layer_after_writing, GColor text_color, GColor back_color) {
  add_text(console_layer, text, 0b11111111, 0b11000001);
  if(dirty_layer_after_writing)
    layer_mark_dirty(console_layer);
}

void console_layer_write_text(Layer *console_layer, char *text, bool dirty_layer_after_writing) {
  add_text(console_layer, text, 0b11111111, 0b11000001);
  if(dirty_layer_after_writing)
    layer_mark_dirty(console_layer);
}

void console_layer_set_color(Layer *console_layer, GColor color) {
  
}

*/




















// char screentext[18*21]="initializing...";
// uint8_t textcolor[18*21];  // foreground text color
// uint8_t backcolor[18*21];  // background text color
//4x6 pixel Font
//#define MAX_ROWS 28
//#define MAX_COLS 35 // Technically 36, but skipping bottom row due to corner mask.

/*
void draw_sprite4(uint8_t *fb, uint8_t *font, int16_t start_x, int16_t start_y, uint8_t color, uint8_t background_color, uint8_t spr) {  // in B&W, color=0 is black, else white
  uint16_t left   = (start_x <     0) ? (start_x >  -4) ?   0 - start_x : 4 : 0;
  uint16_t right  = (start_x > 144-4) ? (start_x < 144) ? 144 - start_x : 0 : 4;
  uint16_t top    = (start_y <     0) ? (start_y >  -6) ?   0 - start_y : 6 : 0;
  uint16_t bottom = (start_y > 168-6) ? (start_y < 168) ? 168 - start_y : 0 : 6;
  uint8_t    *row = font + (spr>>1);//(spr>>3);// + (top*64);
  uint16_t y_addr = (start_y + top) * PBL_IF_COLOR_ELSE(144, 20);
  uint8_t mask = (spr & 1) ? 8 : 128;
    
  for(uint16_t y=top; y<bottom; ++y) {
   for(uint16_t x=left; x<right; ++x) {
//   for(uint16_t y=0; y<6; ++y) {
//     for(uint16_t x=0; x<4; ++x) {
      #ifdef PBL_BW
        //fb[y_addr + ((start_x+x) >> 3)] &= ~(1 << ((start_x+x)&7)); // Black Background (comment both out for clear background)
        //fb[y_addr + ((start_x+x) >> 3)] |=  (1 << ((start_x+x)&7)); // White Background (comment both out for clear background)
        //if(color)
        //  fb[y_addr + ((start_x+x) >> 3)] |=  ((((*row>>x)&1)) << ((start_x+x)&7)); // White Pixel
        //else
        //  fb[y_addr + ((start_x+x) >> 3)] &= ~((((*row>>x)&1)) << ((start_x+x)&7)); // Black Pixel
      #else
        //if((*row>>x)&1)   // horizontally flipped
        if((*row&(mask>>x))) // normal
          fb[y_addr + start_x + x] = color;
        else
          fb[y_addr + start_x + x] = background_color;
      #endif
    }
    y_addr += PBL_IF_COLOR_ELSE(144, 20);
    row += 64;
  }
}
*/
// void draw_font4_text(uint8_t *fb, int16_t x, int16_t y, uint8_t color, char *str) { // str points to zero-terminated string
//   uint8_t strpos=0;
//   while(str[strpos]>0) {
//     if(x>(144-4)) {x=0; y+=6;}  // wrap horizontally
//     if(y>(168-6)) y=0;          // wrap vertically
//     draw_sprite4(fb, font4, x, y, color, str[strpos]);
//     x+=4; strpos++;
//   }
// }

// void draw_screen_text(uint8_t *fb) {
//   uint16_t strpos=0;
//   for(uint16_t y=0; y<MAX_ROWS; ++y) {
//     for(uint16_t x=0; x<MAX_COLS; ++x) {
//       draw_sprite4(fb, font4, x*4, y*6, textcolor[strpos], backcolor[strpos], screentext[strpos]);
//       ++strpos;
//     }
//   }
// }
//GBitmap *font4_bmp; uint8_t *font4;
//  font4_bmp = gbitmap_create_with_resource(RESOURCE_ID_FONT4); font4 = gbitmap_get_data(font4_bmp);
//  gbitmap_destroy(font4_bmp);








/*
//8x8 pixel font
#define MAX_ROWS 21
#define MAX_COLS 18

char buffer[256];
GBitmap *font8_bmp = NULL; uint8_t *font8 = NULL;
// First byte is options
// 0bA-------:
//  A: word_wrap
//  B:
//  C:
//  D:
//  E:
//  F:
//  G:
//  H:
// 2nd & 3rd bytes are default colors
// Default colors = White text on Black

// The bulk of the bytes are as follows:
//   0b0xxxxxxx: ASCII 0-127
//   0b10rrggbb: Change Background Color
//   0b11rrggbb: Change Foreground Color

// 8x8: 18w x 21h = 378 bytes
// 6x8: 24w x 21h = 504 bytes
typedef struct console_data_struct {
  char *text;
  bool word_wrap;
  uint8_t default_back_color;
  uint8_t default_text_color;
} console_data_struct;

#define CONSOLE_BUFFER_SIZE 1024
static uint8_t console[CONSOLE_BUFFER_SIZE] = "\xFF\x80initializing...\n\nnow...";
static uint8_t default_back_color = GColorClearARGB8;
static uint8_t default_text_color = GColorWhiteARGB8;
bool word_wrap = true;

void draw_sprite8(uint8_t *fb, uint8_t *font, int16_t start_x, int16_t start_y, uint8_t color, uint8_t background_color, uint8_t spr) {  // in B&W, color=0 is black, else white
  //printf("fg/bg: %x:%x %x", color, background_color, spr);
  uint16_t left   = (start_x <     0) ? (start_x >  -8) ?   0 - start_x : 8 : 0;
  uint16_t right  = (start_x > 144-8) ? (start_x < 144) ? 144 - start_x : 0 : 8;
  uint16_t top    = (start_y <     0) ? (start_y >  -8) ?   0 - start_y : 8 : 0;
  uint16_t bottom = (start_y > 168-8) ? (start_y < 168) ? 168 - start_y : 0 : 8;
  uint8_t    *row = font + (spr&3) + ((spr&252)*8) + (top*4);
  uint16_t y_addr = (start_y + top) * PBL_IF_COLOR_ELSE(144, 20);

  for(uint16_t y=top; y<bottom; ++y) {
    for(uint16_t x=left; x<right; ++x) {
      #ifdef PBL_BW
        if(color&0b00111111) {
          fb[y_addr + ((start_x+x) >> 3)] &= ~(1 << ((start_x+x)&7)); // Black Background (comment out for clear background)
          fb[y_addr + ((start_x+x) >> 3)] |=  ((((*row>>x)&1)) << ((start_x+x)&7)); // White Pixel
        } else {
          fb[y_addr + ((start_x+x) >> 3)] |=  (1 << ((start_x+x)&7)); // White Background (comment out for clear background)
          fb[y_addr + ((start_x+x) >> 3)] &= ~((((*row>>x)&1)) << ((start_x+x)&7)); // Black Pixel
        }
      #else
        //if((*row>>x)&1)   // horizontally flipped
        if((*row&(128>>x))) // normal
          fb[y_addr + start_x + x] = color;
        else
          fb[y_addr + start_x + x] = background_color;
      #endif
    }
    y_addr += PBL_IF_COLOR_ELSE(144, 20);
    row += 4;
  }
}


void draw_screen_text(uint8_t *fb) {
  uint16_t strpos = 0;
  uint8_t text_color = default_text_color;
  uint8_t back_color = default_back_color;
  
  uint16_t y=0, x=0;
  do {
    if(console[strpos]&0b10000000) {
      if(console[strpos]&0b01000000) {
        text_color = 0b11000000 + (console[strpos]&0b00111111);
      } else {
        back_color = 0b11000000 + (console[strpos]&0b00111111);
      }
    } else if(console[strpos]>31) {
      draw_sprite8(fb, font8, (x++)*8, y*8, text_color, back_color, console[strpos]);
    } else if(console[strpos]==10 || console[strpos]==13) {  // if CR or LF
      //if(x>0)
      for(; x<MAX_COLS; ++x)
        draw_sprite8(fb, font8, x*8, y*8, text_color, back_color, 32);
    } else {
      // 0 - 31, not 10 or 13
    }
    
    if(x>=MAX_COLS) {x=0; ++y;} // if wordwrap
    if(y>=MAX_ROWS) {return;}
  } while (strpos<CONSOLE_BUFFER_SIZE && console[++strpos]>0);
}


static void repair_text_buffer() {
  // remove CRLF -> CR
  // Remove redundant colors
  // Remove unused colors
  uint16_t readpos = 0;
  uint16_t writepos = 0;
  uint8_t last_char = 0;
  bool back_color_changed = false;
  bool fore_color_changed = false;
  
  uint8_t current_text_color = default_text_color;
  uint8_t current_back_color = default_back_color;
  uint16_t y=0, x=0;
  
  do {
    if(console[readpos]&0b10000000) {
      if(console[readpos]&0b01000000) {
        uint8_t text_color = 0b11000000 + (console[readpos]&0b00111111);
        if(text_color != current_text_color) {
          if no characters were printed since last color was updated, then replace that color
          console[writepos++] = console[readpos];
          current_text_color = text_color;
          
        }
      } else {
        uint8_t back_color = 0b11000000 + (console[readpos]&0b00111111);
        if(back_color != current_back_color) {
          console[writepos++] = console[readpos];
          current_back_color = back_color;
        }
      }
    } else { // Else is a character
      if(console[readpos]>31) {  // Is a printable character
        console[writepos++] = console[readpos];
        last_char = console[readpos];
        ++x;
      } else if(console[readpos]==10 || (console[readpos]==13 && last_char != 10)) {  // else if nonprintable is CR or LF
        last_char = console[readpos];
        console[writepos++] = console[readpos];
        x=MAX_COLS;
      }  // else delete character
      last_char = console[readpos];
    }
    if(x>=MAX_COLS) {x=0; ++y;} // if wordwrap
  } while (readpos<CONSOLE_BUFFER_SIZE && console[++readpos]>0 && y<MAX_ROWS);
  console[writepos] = 0;
}
  
static void console_layer_update(Layer *console_layer, GContext *ctx) {
  uint8_t *framebuffer = (uint8_t*)*(size_t*)ctx;
  draw_screen_text(framebuffer);
}

Layer* console_layer_create(GRect frame) {
  static Layer *console_layer;
  size_t buffer_size = 100;
  console_layer = layer_create_with_data(frame, buffer_size);
  //void* layer_get_data(const Layer *layer)
  layer_set_update_proc(console_layer, console_layer_update);
  if(!font8) {
    font8_bmp = gbitmap_create_with_resource(RESOURCE_ID_FONT8);
    font8 = gbitmap_get_data(font8_bmp);
  }
  return console_layer;
}

void console_layer_destroy(Layer *console_layer) {
  layer_destroy(console_layer);
  //if(font8) {gbitmap_destroy(font8_bmp); font8 = NULL;}
}

void console_layer_set_color(Layer *console_layer, GColor text_color, GColor background_color) {
  uint16_t strpos=0;
  while (console[strpos]>0 && strpos<CONSOLE_BUFFER_SIZE) strpos++;
  if(strpos<CONSOLE_BUFFER_SIZE) console[strpos++] = 0b11000000 || (text_color.argb & 0b00111111);
  if(strpos<CONSOLE_BUFFER_SIZE) console[strpos++] = 0b10000000 || (background_color.argb & 0b00111111);
}

void console_layer_set_default_color(Layer *console_layer, GColor text_color, GColor background_color) {
  
}

void console_layer_write_text(Layer *console_layer, char *text, bool dirty_layer_after_writing) {
  uint16_t strpos=0, textpos=0;
  while (console[strpos]>0 && strpos<CONSOLE_BUFFER_SIZE)
    strpos++;
  while (strpos<CONSOLE_BUFFER_SIZE && text[textpos]>0)
    console[strpos++] = (0b01111111 & text[textpos++]);  // Mask to 0-127 ASCII

  //add_text(console_layer, text, 0b11111111, 0b11000001);
  if(dirty_layer_after_writing)
    layer_mark_dirty(console_layer);
}
*/
