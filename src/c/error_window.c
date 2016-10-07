#include <pebble.h>
#include "error_window.h"

/* Pop-up window to show when something goes wrong in pebble app */

Window *errorWindow;
Layer *errorGraphicsLayer;
char currentErrorText[1][20];

// convenience function
void error_window_show(char *errorText) {
  // copy to 2d array the string we pass in
  strncpy(currentErrorText[0], errorText, sizeof(currentErrorText[0]));

  if (errorGraphicsLayer) { // protect against null ptr
    // mark it dirty so it will get refreshed otherwise it won't
    layer_mark_dirty(errorGraphicsLayer);
  }

  window_stack_push(errorWindow, true);
  
}

/* Called when screen refreshed either automatically/manually or we have marked layer dirty */
void error_graphics_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_text_color(ctx, GColorRed);
  graphics_draw_text(ctx, currentErrorText[0], fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD),
		     GRect(0, 0, 144, 50), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
    
  graphics_context_set_stroke_color(ctx, GColorBlue);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_draw_line(ctx, GPoint(10, 30), GPoint(124, 138));
    
}

void error_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  errorGraphicsLayer = layer_create(GRect(0, 0, 144, 168));

  // dynamic layer, pebble calls this every manual or auto refresh, or we mark layer dirty
  layer_set_update_proc(errorGraphicsLayer, error_graphics_proc);
  layer_add_child(window_layer, errorGraphicsLayer);
}

void error_window_unload(Window *window) {
  layer_destroy(errorGraphicsLayer);
  errorGraphicsLayer = NULL; // FIX: crashed cloudpebble, but SDK worked fine, just be safe here
}

void error_window_create() {
  errorWindow = window_create();

  // casting an inline anon struct to WindowHandlers struct
  window_set_window_handlers(errorWindow, (WindowHandlers) {
      .load = error_window_load,
      .unload = error_window_unload
  });
}

void error_window_destroy() {
  window_destroy(errorWindow);
  
}

Window *error_window_get_window() {
  return errorWindow;
}
