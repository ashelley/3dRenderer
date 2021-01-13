#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <stdio.h>
#include "types.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool is_running = false;
uint32_t window_width = 800;
uint32_t window_height = 600;
vec3 camera_pos = { .x = 0, .y = 0, .z = -5 };
float fov_factor = 640;

SDL_Texture* screen_texture = NULL;
uint32_t* screen_buffer = NULL;

float frame_target_time = 1000 / 60;
float previous_frame_time = 0;

bool initalize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "ERROR: sdl could not be initialized\n");
		return false;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	window_width = display_mode.w;
	window_height = display_mode.h;

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
	//window = SDL_CreateWindow(NULL, 100, 100, 800, 600, SDL_WINDOW_BORDERLESS);

	if (!window) {
		fprintf(stderr, "ERROR: sdl window could not be created\n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "ERROR: sdl renderer could not be created\n");
		return false;
	}

	return true;
}

void initialize_screen() {
	screen_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
	screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
}

void wait_for_next_frame() {
	int time_to_wait = frame_target_time - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0 && time_to_wait <= frame_target_time) {
		SDL_Delay(time_to_wait);
	}

	previous_frame_time = SDL_GetTicks();
}

bool process_input(void) {
	SDL_Event event;
	if (!SDL_PollEvent(&event)) {
		return false;
	}

	if (event.type == SDL_QUIT) {
		is_running = false;
	}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			is_running = false;
		}
	}

	return true;
}

void blit_screen(void) {
	SDL_UpdateTexture(screen_texture, NULL, screen_buffer, (int)(window_width) * sizeof(uint32_t));
	SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
}

void blank_screen(uint32_t color) {
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			screen_buffer[(window_width * y) + x] = color;
		}
	}
}

void set_pixel(int x, int y, uint32_t color) {
	if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
		screen_buffer[(window_width * y) + x] = color;
	}
}

vec2 project(vec3 point) {
	vec2 projected = {
		.x = (fov_factor * point.x) / point.z,
		.y = (fov_factor * point.y) / point.z
	};
	return projected;
}


#endif
