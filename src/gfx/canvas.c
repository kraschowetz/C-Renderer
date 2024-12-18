#include "canvas.h"

Canvas create_canvas(i32 w, i32 h) {

	Canvas self;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Failed to init SDL!\n");
		exit(1);
	}
	self.window = SDL_CreateWindow(
		"Teste Shaders",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		SDL_WINDOW_OPENGL
	);

	if(!self.window) {
		fprintf(stderr, "Failed to init window!\n");
		exit(1);
	}

	self.renderer = create_renderer(self.window);

	return self;
}

void destroy_canvas(Canvas *self) {
	destroy_renderer(&self->renderer);

	SDL_DestroyWindow(self->window);
	SDL_Quit();
}

void canvas_render(Canvas *self) {
	render(&self->renderer, self->window);
}
