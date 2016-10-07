#pragma once

void main_window_load(Window *window);
void main_window_create();
void main_window_destroy();
Window *main_window_get_window();

uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data);
uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data);
int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data);
void menu_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *data);
void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data);
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data);
void setup_menu_layer(Window *window);




