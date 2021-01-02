#include "renderer.h"
#include "scenes.h"

void setup(void) {
	initialize_screen();
	initialize_point_cube();
}

void update(void) {
	update_point_cube();
}

void render(void) {
	blank_screen(0xFF000000);
	//line_grid();
	pixel_grid();
	draw_projected_points();
	blit_screen();
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
	is_running = initalize_window();

	setup();

	while (is_running) {
		while(process_input());
		update();
		render();
	}
	return 0;
}