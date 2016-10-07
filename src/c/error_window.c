/*
 * Pop-up window to show when something goes wrong in app 
 */

#include <pebble.h>
#include "error_window.h"

Window *error_window;
Layer *error_gfx_layer;
char curr_err_text[1][20];

/*
 * Function that shows error window with error message.
 */
void error_window_show(char *errorText)
{
	strncpy(curr_err_text[0], errorText, sizeof(curr_err_text[0]));

	/* NULL ptr protection */
	if (error_gfx_layer) {
		/* mark it dirty so it will get refreshed */
		layer_mark_dirty(error_gfx_layer);
	}

	window_stack_push(error_window, true);
}

/*
 * Function called when screen refreshed either automatically/manually
 * or we have marked layer dirty
 */
void error_graphics_proc(Layer *layer, GContext *ctx)
{
	graphics_context_set_text_color(ctx, GColorRed);
	graphics_draw_text(ctx, curr_err_text[0],
			   fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD),
			   GRect(0, 0, 144, 50), GTextOverflowModeWordWrap,
			   GTextAlignmentCenter, NULL);

	graphics_context_set_stroke_color(ctx, GColorBlue);
	graphics_context_set_stroke_width(ctx, 3);
	graphics_draw_line(ctx, GPoint(10, 30), GPoint(124, 138));
}

/*
 * Function to create the error window and graphics layer for it.
 */
void error_window_load(Window *window)
{
	Layer *window_layer = window_get_root_layer(window);

	error_gfx_layer = layer_create(GRect(0, 0, 144, 168));

	layer_set_update_proc(error_gfx_layer, error_graphics_proc);
	layer_add_child(window_layer, error_gfx_layer);
}

/*
 * Function that frees window and related resources on window unload.
 */
void error_window_unload(Window *window)
{
	layer_destroy(error_gfx_layer);
	error_gfx_layer = NULL;
}

/*
 * Function that creates the error window and sets the load/unload callbacks.
 */
void error_window_create()
{
	error_window = window_create();

	window_set_window_handlers(error_window, (WindowHandlers) {
			.load = error_window_load,
				.unload = error_window_unload
	});
}

/*
 * Function to free the error window and related resources.
 */
void error_window_destroy()
{
	window_destroy(error_window);
}

/*
 * Function to return the errow window.
 */
Window *error_window_get_window()
{
	return error_window;
}
