#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool is_running = false;
uint32_t window_width = 800;
uint32_t window_height = 600;

SDL_Texture* screen_texture = NULL;
uint32_t* screen_buffer = NULL;


bool initalize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "ERROR: sdl could not be initialized\n");
		return false;
	}

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
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

void setup(void) {
	screen_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
	screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
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

void render(void) {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	
	blit_screen();
	blank_screen(0xFFFF0000);

	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
	is_running = initalize_window();

	setup();

	while (is_running) {
		while(process_input());
		render();
	}
	return 0;
}