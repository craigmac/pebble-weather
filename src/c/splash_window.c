/*
 * Splash window that shows before the launch of main window.
 */

#include <pebble.h>
#include "splash_window.h"

Window *splash_window = NULL;
GBitmap *splash_img = NULL;
BitmapLayer *splash_img_layer = NULL;
TextLayer *splash_img_title = NULL;

/*
 * Function to load splash window and set gfx.
 */
void splash_window_load(Window *window)
{
	Layer *window_layer = window_get_root_layer(window);

	splash_img = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH);
	splash_img_layer = bitmap_layer_create(GRect(0, 0, 144, 120));
	bitmap_layer_set_bitmap(splash_img_layer, splash_img);
	bitmap_layer_set_compositing_mode(splash_img_layer, GCompOpSet);
	layer_add_child(window_layer, bitmap_layer_get_layer(splash_img_layer));

	splash_img_title = text_layer_create(GRect(0, 120, 144, 50));
	text_layer_set_text(splash_img_title, "Weather App");
	text_layer_set_text_alignment(splash_img_title, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(splash_img_title));
}

/*
 * Function called on window unload event. Releases resources.
 */
void splash_window_unload(Window *window)
{
	gbitmap_destroy(splash_img);
	bitmap_layer_destroy(splash_img_layer);
	text_layer_destroy(splash_img_title);
}

/*
 * Function to create and set event callbacks for window.
 */
void splash_window_create(void)
{
	splash_window = window_create();

	window_set_window_handlers(splash_window, (WindowHandlers) {
			.load = splash_window_load,
				.unload = splash_window_unload
	});
}

/*
 * Function to destroy the splash window.
 */
void splash_window_destroy(void)
{
	window_destroy(splash_window);
}

/*
 * Function to return a pointer to the splash window.
 */
Window *splash_window_get_window(void)
{
	return splash_window;
}
