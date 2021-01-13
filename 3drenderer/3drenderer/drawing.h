#ifndef DRAWING_H
#define DRAWING_H

#include "renderer.h"

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)longest_side_length;
	float y_inc = delta_y / (float)longest_side_length;

	float current_x = x0;
	float current_y = y0;
	for (int i = 0; i <= longest_side_length; i++) {
		set_pixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
}


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
