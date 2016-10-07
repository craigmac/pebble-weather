#include <pebble.h>
#include "main_window.h"
#include "error_window.h"

Window *mainWindow;
MenuLayer *mainMenuLayer;

/* void *data -- dynamic ptr so we can pass any ptr struct in, used to pass data structs around.
 * just use NULL if you don't need to pass anything in */
uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 2; // one for cities section, one for adding cities section
}

uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
  case 0:
    return 1;
  case 1:
    return 1;
  default:
    return 0;
  }
  return 0;
    
}

int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  // usualy just return this constant
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}


/* Draw headers of sections */
void menu_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context) {
  switch (cell_layer->section) {
  case 0:
    menu_cell_basic_header_draw(ctx, cell_layer, "Cities");
    break;
  case 1:
    menu_cell_basic_header_draw(ctx, cell_layer, "Other");
    break;
  }
    
}

/* Draw rows in sections */
void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    switch (cell_index->section) {
      // Section 1 -- list of cities section
      case 0:
        switch (cell_index->row) {
          case 0:
	    menu_cell_basic_draw(ctx, cell_layer, "Example", "40 degrees", NULL);
            break;
        }
	break;

      // Section 2 -- add a city section
      case 1:
	menu_cell_basic_draw(ctx, cell_layer, "Add City", NULL, NULL);
	break;
    }
}

/* void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data)
 *
 * Called when user clicks select button on a row
 *
 *
 */
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  error_window_show("Hello there!");
	
}

void setup_menu_layer(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  mainMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));

  // set callbacks for menus
  menu_layer_set_callbacks(mainMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback, // num of sections in menu layer
        .get_num_rows = menu_get_num_rows_callback, // amount of rows section has
	.get_header_height = menu_get_header_height_callback, // usually leave this
	.draw_header = menu_draw_header_callback, // draw header gfx
	.draw_row = menu_draw_row_callback, // draw row gfx
	.select_click = menu_select_callback, // on user click
  });

  menu_layer_set_click_config_onto_window(mainMenuLayer, window);
  layer_add_child(window_layer, menu_layer_get_layer(mainMenuLayer));
}

void main_window_load(Window *window) {
  setup_menu_layer(window);
  
}

void main_window_unload(Window *window) {
  menu_layer_destroy(mainMenuLayer);
  
}

void main_window_create() {
  mainWindow = window_create();

  // casting an inline anon struct to WindowHandlers struct
  window_set_window_handlers(mainWindow, (WindowHandlers) {
      .load = main_window_load,
      .unload = main_window_unload
  });
}

void main_window_destroy() {
  window_destroy(mainWindow);
  
}

Window *main_window_get_window() {
  return mainWindow;
}
