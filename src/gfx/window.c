#include "window.h"

Window g_window;

Window create_window(const char *title, i32 w, i32 h) {

	Window self;

	self.width = w;
	self.height = h;
	self.aspect = (f32)(w) / (f32)(h);

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Failed to init SDL!\n");
		exit(1);
	}
	self.sdl_window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		SDL_WINDOW_OPENGL
	);

	if(!self.sdl_window) {
		fprintf(stderr, "Failed to init sdl_window!\n");
		exit(1);
	}

	return self;
}

void destroy_window(Window *self) {
	destroy_renderer(&self->renderer);

	SDL_DestroyWindow(self->sdl_window);
	SDL_Quit();
}

void window_render(Window *self) {
	render(&self->renderer, self->sdl_window);
}
