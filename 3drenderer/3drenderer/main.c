#include "renderer.h"
#include "drawing.h"

//#include "scene_point_cube.h"
#include "scene_cube_mesh.h"

void setup(void) {
	initialize_screen();
	scene_initialize();
}

void update(void) {
	wait_for_next_frame();
	scene_update();
}

void render(void) {
	blank_screen(0xFF000000);
	//draw_line_grid();
	draw_pixel_grid();
	scene_render();
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