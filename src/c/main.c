/*
 * Main entry point of weather-app. Coordinates pushing Windows
 * onto the window manager.
 */

#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"
#include "error_window.h"

/*
 * Function to push the main window onto the stack and show it.
 */
static void launch_main_window (void *data)
{
	const bool animated = true;
	window_stack_push(main_window_get_window(), animated);
}

int main () {
	splash_window_create();
	main_window_create();
	error_window_create();

	window_stack_push(splash_window_get_window(), true);

	/* Launch main window after 1.25 secs */
	AppTimer *apptmr = app_timer_register(1250,
					      launch_main_window, NULL);
	free(apptmr); /* fix gcc complaint about unused var */
	app_event_loop();

	/* TODO: turn below responsibly over to _unload() functions */
	splash_window_destroy();
	main_window_destroy();
	error_window_destroy();
}
