/*
 * The main window of the application. Comes after the initial splash window which shows
 * the application logo and/or intro animation. 
 * 
 * Written in Linux kernel C-style <https://www.kernel.org/doc/Documentation/CodingStyle>
 * 
 */

#include <pebble.h>
#include "main_window.h"
#include "error_window.h"

Window *main_window = NULL;
MenuLayer *main_menu_layer = NULL;

/*
 * Function that returns the number of sections a menu layer contains. Optional
 * to include MenuLayer referring to, and pointer to a context to work with (by
 * default it will be the window)
 */
uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *context)
{
	return 2; /* one for cities section, one for adding cities section */
}

/*
 * Function that returns the number of rows a given section contains. 
 */
uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer,
				    uint16_t section_index, void *context)
{
	switch (section_index) {
	case 0:
		return 1;
	case 1:
		return 1;
	default:
		return 0;
  }
  /*  return 0; */
}

/*
 * Function that returns the height of a header. Usually left as is and 
 * a constant is returned, but it is here if you really tweak things.
 */
int16_t menu_get_header_height_callback(MenuLayer *menu_layer,
					uint16_t section_index, void *context)
{
	return MENU_CELL_BASIC_HEADER_HEIGHT;
}

/* 
 * Function to draw a section header/s.
 */
void menu_draw_header_callback(GContext *ctx, const Layer *cell_layer,
			       uint16_t section_index, void *context)
{
	switch (cell_layer->section) {
	case 0:
		menu_cell_basic_header_draw(ctx, cell_layer, "Cities");
		break;
	case 1:
		menu_cell_basic_header_draw(ctx, cell_layer, "Other");
		break;
	}
}

/* 
 * Function to draw invidual rows inside a section.
 */
void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer,
			    MenuIndex *cell_index, void *context)
{
	switch (cell_index->section) {
		/* Section 1 -- list of cities section */
		case 0:
			switch (cell_index->row) {
			case 0:
				menu_cell_basic_draw(ctx, cell_layer,
				 "Example", "40 degrees", NULL);
			break;
			}
		        /* break; */
		 /* Section 2 -- add a city section */
		 case 1:
			 menu_cell_basic_draw(ctx, cell_layer,
					      "Add City", NULL, NULL);
			 break;
	}
}

/* 
 * Function to run when user presses 'select' button.
 */
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *context)
{
	error_window_show("Hello there!");
}

/*
 * Function to create the main window and setup event callbacks
 */
void setup_menu_layer(Window *window)
{
	Layer *window_layer = window_get_root_layer(window);
  
	main_menu_layer = menu_layer_create(GRect(0, 0, 144, 168));

	menu_layer_set_callbacks(main_menu_layer, NULL, (MenuLayerCallbacks){
			.get_num_sections = menu_get_num_sections_callback,
				.get_num_rows = menu_get_num_rows_callback,
				.get_header_height = menu_get_header_height_callback,
				.draw_header = menu_draw_header_callback,
				.draw_row = menu_draw_row_callback,
				.select_click = menu_select_callback,
  });

	menu_layer_set_click_config_onto_window(main_menu_layer, window);
	layer_add_child(window_layer, menu_layer_get_layer(main_menu_layer));
}

/*
 * Function to call other loading functions when window first loads.
 */
void main_window_load(Window *window)
{
	setup_menu_layer(window);
}

/*
 * Function to free resources used on window unload event.
 */
void main_window_unload(Window *window)
{
	menu_layer_destroy(main_menu_layer);
}

/*
 * Function to create main window and set window load/unload callbacks.
 */
void main_window_create(void)
{
	main_window = window_create();

	window_set_window_handlers(main_window, (WindowHandlers) {
			.load = main_window_load,
			.unload = main_window_unload
  });
}

/*
 * Function to free main window and associated memory.
 */
void main_window_destroy(void)
{
	window_destroy(main_window);
}

/*
 * Getter function to return main window to outside calls.
 */
Window *main_window_get_window(void)
{
	return main_window;
}
