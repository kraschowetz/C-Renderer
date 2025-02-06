#ifndef CUBE_H
#define CUBE_H

#include "gfx.h"
#include "vao.h"

/*
*	front
*	?
*	?
*	?
*	?
*/

#define GFX_CUBE_RENDERING_ORDER { \
	0, 1, 2, 2, 3, 0, \
	1, 5, 6, 6, 2, 1, \
	7, 6, 5, 5, 4, 7, \
	4, 0, 3, 3, 7, 4, \
	4, 5, 1, 1, 0, 4, \
	3, 2, 6, 6, 7, 3 \
}
#define GFX_CUBE_IBO_SIZE 36

typedef struct {
	VAO vao;
	VBO vbo;
} Cube;

Cube *create_cube(GLfloat position[36], GLfloat color[36]);
void destroy_cube(Cube *self);
void cube_render(const Cube *self);

#endif
