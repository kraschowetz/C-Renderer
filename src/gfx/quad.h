#ifndef QUAD_H
#define QUAD_H

#include "gfx.h"
#include "vao.h"

#define GFX_QUAD_RENDERING_ORDER {0, 1, 2, 2, 3, 0}

typedef struct {
	VAO vao;
	VBO vbo;
} Quad;

Quad *create_quad(GLfloat position[12], GLfloat color[12]);
void destroy_quad(Quad *self);
void quad_render(Quad *self);

#endif
