#include "renderer.h"
#include "scenes.h"

void render(void) {
	blank_screen(0xFFFF0000);
	draw_grid();
	blit_screen();
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