#ifndef CANVAS_H
#define CANVAS_H

#include "gfx.h"
#include "renderer.h"

typedef struct {
	SDL_Window *window;
	Renderer renderer;
} Canvas;

Canvas create_canvas(i32 w, i32 h);
void destroy_canvas(Canvas *self);
void canvas_render(Canvas *self);

#endif
