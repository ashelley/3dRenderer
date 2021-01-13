#ifndef DRAWING_H
#define DRAWING_H

#include "renderer.h"

void draw_rect(int x, int y, int width, int height, uint32_t color) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int current_x = x + i;
			int current_y = y + j;
			set_pixel(current_x, current_y, color);
		}
	}
}

void draw_line_grid(void) {
	uint32_t color = 0xFF00FFFF;

	int cell_width = window_width / 10;
	int cell_height = window_height / 10;

	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			if (x % cell_width == 0 || x == window_width - 1) {
				set_pixel(x, y, color);
			}
			if (y % cell_height == 0 || y == window_height - 1) {
				set_pixel(x, y, color);
			}
		}
	}
}

void draw_pixel_grid(void) {
	uint32_t color = 0xFF444444;
	for (int y = 0; y < window_height; y += 10) {
		for (int x = 0; x < window_width; x += 10) {
			set_pixel(x, y, color);
		}
	}
}

#endif
