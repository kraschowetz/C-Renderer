#ifndef RENDERER_H
#define RENDERER_H

#include "cube.h"
#include "shader.h"
#include "triangle.h"
#include "quad.h"

#define VSYNC_STATE 0

#define NEAR_PLANE 0.1f
#define FAR_PLANE 10.0f

typedef struct{
	SDL_GLContext context;
	Shader shader;
	Triangle *tri;
	Quad *quad;
	Cube *cube;
	f32 time;
} Renderer;

Renderer create_renderer(SDL_Window *window);
void destroy_renderer(Renderer *self);
void render_prepare(void);
void render(Renderer *self, SDL_Window *window);


#endif
