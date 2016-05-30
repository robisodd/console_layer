#include <pebble.h>
#include "main.h"
#include "console.h"

Window *main_window;
Layer *root_layer;
Layer *console_layer;
bool emulator = false;

static void error_msg(char *msg) {
  printf("Displaying Error: %s", msg);
  console_layer_write_text_attributes(console_layer, msg, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), GColorRed, GColorClear, GTextAlignmentCenter, true, true);
}


// ------------------------------------------------------------------------ //
//  Dictation API Functions
// ------------------------------------------------------------------------ //
static DictationSession *dictation_session = NULL;
static char dictation_text[512];
const char* DictationSessionStatusError[] = {
  "Transcription successful, with a valid result.",
  "User rejected transcription and exited UI.",
  "User exited UI after transcription error.",
  "Too many errors occurred during transcription and the UI exited.",
  "No speech was detected and UI exited.",
  "No BT or internet connection.",
  "Voice transcription disabled for this user.",
  "Voice transcription failed due to internal error.",
  "Cloud recognizer failed to transcribe speech."
};

static void dictation_session_callback(DictationSession *session, DictationSessionStatus status, char *transcription, void *context) {
  if(status == DictationSessionStatusSuccess) {
    snprintf(dictation_text, sizeof(dictation_text), "%s", transcription);
    printf("Dictation Text: %s", dictation_text);
    console_layer_write_text(console_layer, dictation_text, true);
  } else {
    snprintf(dictation_text, sizeof(dictation_text), "Error: %s", DictationSessionStatusError[status]);
    error_msg(dictation_text);
  }
}

static void init_dictation() {
  dictation_session = dictation_session_create(sizeof(dictation_text), dictation_session_callback, NULL);
}

static void deinit_dictation() {
  if(dictation_session)
    dictation_session_destroy(dictation_session);
}



// ------------------------------------------------------------------------ //
//  Button Functions
// ------------------------------------------------------------------------ //
void up_click_handler  (ClickRecognizerRef recognizer, void *context) { //   UP   button
  switch(rand()%3) {
    case 0: console_layer_write_text(console_layer, "Hello\nThere", true); break;
    case 1: console_layer_write_text(console_layer, "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", true); break;
    case 2: console_layer_write_text(console_layer, "abcdefghijklmnopqrstuvwxyz", true); break;
  }
}

void sl_click_handler  (ClickRecognizerRef recognizer, void *context) { // SELECT button
  if(emulator)
    error_msg("No Microphone");
  else
    PBL_IF_MICROPHONE_ELSE(dictation_session_start(dictation_session), error_msg("No Microphone"));
}

void dn_click_handler  (ClickRecognizerRef recognizer, void *context) { //  DOWN  button
  //console_layer_set_text_colors(console_layer, GColorWhite, GColorRed);
  
  console_layer_set_background_color(console_layer, (GColor){.argb=0b11000000+(rand()%64)});
  
  switch(rand()%2) {
    case 0: console_layer_set_text_colors(console_layer, (GColor){.argb=0b11000000+(rand()%64)}, (GColor){.argb=0b11000000+(rand()%64)}); break;
    case 1: console_layer_set_text_background_color(console_layer, GColorInherit); break;
  }
  
  switch(rand()%4) {
    case 0: console_layer_set_default_font(console_layer, fonts_get_system_font(FONT_KEY_GOTHIC_09)); break;
    case 1: console_layer_set_default_font(console_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18)); break;
    case 2: console_layer_set_default_font(console_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18)); break;
    case 3: console_layer_set_default_font(console_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18)); break;
  }

  console_layer_set_word_wrap(console_layer, rand()%2 ? (rand()%2?true:false) : WordWrapInherit);  // 50% Inherit, 25% True, 25% False
  console_layer_set_default_word_wrap(console_layer, rand()%2 ?true : false);
  
  switch(rand()%4) {
    case 0: console_layer_set_text_alignment(console_layer, GTextAlignmentLeft);    break;
    case 1: console_layer_set_text_alignment(console_layer, GTextAlignmentCenter);  break;
    case 2: console_layer_set_text_alignment(console_layer, GTextAlignmentRight);   break;
    case 3: console_layer_set_text_alignment(console_layer, GTextAlignmentInherit); break;
  }
  
  switch(rand()%3) {
    case 0: console_layer_set_default_text_alignment(console_layer, GTextAlignmentLeft);   break;
    case 1: console_layer_set_default_text_alignment(console_layer, GTextAlignmentCenter); break;
    case 2: console_layer_set_default_text_alignment(console_layer, GTextAlignmentRight);  break;
  }

  layer_mark_dirty(console_layer);
  //console_layer_write_text(console_layer, "Hello", true);
}

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, dn_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, sl_click_handler);
  //window_single_click_subscribe(BUTTON_ID_BACK, bk_click_handler);
}


// ------------------------------------------------------------------------ //
//  Main Functions
// ------------------------------------------------------------------------ //
void main_window_load(Window *window) {
  root_layer = window_get_root_layer(window);
  GRect rect = layer_get_frame(window_get_root_layer(window));
  IF_ROUND(rect = grect_inset(rect, GEdgeInsets(26)));
  //GRect rect = GRect(20, 20, 100, 100);

  console_layer = console_layer_create(rect);
  layer_add_child(root_layer, console_layer);
  
  console_layer_set_default_word_wrap(console_layer, true);
  console_layer_set_default_text_color(console_layer, GColorWhite);
  //console_layer_set_text_colors(console_layer, GColorWhite, GColorRed);
  
  window_set_click_config_provider(window, click_config_provider);
  console_layer_write_text_attributes(console_layer, "Welcome to\nConsole Layer", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GColorInherit, GColorInherit, GTextAlignmentCenter, true, true);
  console_layer_write_text(console_layer, "Hello World.", true);
  console_layer_write_text(console_layer, "Example Text", true);
}

void main_window_unload(Window *window) {
  layer_destroy(console_layer);
}

void init() {
  // Create main Window
  main_window = window_create();
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_background_color(main_window, IF_BW_COLOR(GColorBlack, GColorDarkGray));
  window_stack_push(main_window, true);
  // Create new dictation session
  init_dictation();
}

void deinit() {
  deinit_dictation();
  window_destroy(main_window);  // Destroy main Window
}



void battery_handler(BatteryChargeState charge_state) {
  static int previous_state = 0;  // To stop the friggin CONSTANT messages with no state change!
  if (charge_state.is_charging || charge_state.is_plugged) {
    if(previous_state != 1) {
      LOG("External Power Detected: Backlight On");
      previous_state = 1;
      light_enable(true);
    }
  } else {
    if(previous_state != 2) {
      LOG("Battery Power Detected: Backlight Auto");
      previous_state = 2;
      light_enable(false);
    }
  }
}


int main(void) {
  init();
  
  emulator = watch_info_get_model()==WATCH_INFO_MODEL_UNKNOWN;
  if(emulator) {
    light_enable(true);  // Good colors on emulator
    LOG("Emulator Detected: Turning Backlight On");
  }
  
  battery_state_service_subscribe(battery_handler);
  battery_handler(battery_state_service_peek());
  
  app_event_loop();
  deinit();
  
  battery_state_service_unsubscribe();
}