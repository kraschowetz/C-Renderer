#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "gfx.h"
#include "vao.h"

typedef struct {
	VAO vao;
	VBO vbo;
} Triangle;

Triangle *create_triangle(GLfloat position[9], GLfloat vert_color[9]);
void destroy_triangle(Triangle *self);
void triangle_render(const Triangle *self);

#endif
