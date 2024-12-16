#ifndef VBO_H
#define VBO_H

#include "gfx.h"

typedef struct {
	GLuint handle;
	GLuint type;
} VBO;

VBO create_vbo(GLuint type);
void destroy_vbo(VBO *self);
void vbo_bind(VBO *self);
void vbo_buffer(VBO *self, void *data, GLsizeiptr offset, GLsizeiptr count);

#endif
