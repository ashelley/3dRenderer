#ifndef SCENES_H
#define SCENES_H

#include "renderer.h"

void draw_grid(void) {
	uint32_t color = 0xFF00FFFF;

	int cell_width = window_width / 10;
	int cell_height = window_height / 10;

	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			if (x % cell_width == 0 || x == window_width - 1) {
				screen_buffer[(window_width * y) + x] = color;
			}
			if (y % cell_height == 0 || y == window_height - 1) {
				screen_buffer[(window_width * y) + x] = color;
			}
		}
	}
}

#endif
