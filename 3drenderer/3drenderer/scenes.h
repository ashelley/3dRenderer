#ifndef SCENES_H
#define SCENES_H

#include "renderer.h"

void line_grid(void) {
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

void pixel_grid(void) {
	uint32_t color = 0xFF444444;
	for (int y = 0; y < window_height; y += 10) {
		for (int x = 0; x < window_width; x += 10) {
			set_pixel(x, y, color);
		}
	}
}


#define N_POINTS (9 * 9 * 9)
vec3 cube_rotation = { .x = 0, .y = 0, .z = 0 };
vec3 cube_points[N_POINTS]; // 9x9x9 cube
vec2 projected_points[N_POINTS];

void initialize_point_cube() {
	int point_count = 0;
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3 new_point = { .x = x, .y = y, .z = z };
				cube_points[point_count++] = new_point;
			}
		}
	}
}

void update_point_cube() {

	cube_rotation.x += 0.01;
	cube_rotation.y += 0.01;
	cube_rotation.z += 0.01;

	for (int i = 0; i < N_POINTS; i++) {
		vec3 point = cube_points[i];

		vec3 transformed = rotate_x(point, cube_rotation.x);
		transformed = rotate_y(transformed, cube_rotation.y);
		transformed = rotate_z(transformed, cube_rotation.z);

		transformed.z -= camera_pos.z;

		vec2 projected_point = project(transformed);

		projected_points[i] = projected_point;
	}
}

void draw_projected_points() {
	for (int i = 0; i < N_POINTS; i++) {
		vec2 projected_point = projected_points[i];
		draw_rect(projected_point.x + (window_width / 2), projected_point.y + (window_height / 2), 4,4,0xFFFFFF00);
	}
}

#endif
