#ifndef WINDOW_H
#define WINDOW_H

#include "gfx.h"
#include "renderer.h"

typedef struct {
	SDL_Window *sdl_window;
	Renderer renderer;
	i32 width, height;
	f32 aspect;
} Window;

Window create_window(const char *title, i32 w, i32 h);
void destroy_window(Window *self);
void window_render(Window *self);

extern Window g_window;

#endif
