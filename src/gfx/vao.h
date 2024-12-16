#ifndef VAO_H
#define VAO_H

#include "vbo.h"

typedef struct {
	GLuint	handle;
} VAO;

VAO create_vao();
void destroy_vao(VAO *self);
void vao_bind(VAO *self);
void vao_attr(
	VAO *self,
	VBO *vbo,
	GLuint index,
	GLint size,
	GLenum type,
	GLsizei stride,
	size_t offset
);
void vao_disable_attr(VAO *self, GLuint *ids, size_t id_count);
void vao_flush_attr(GLuint *ids, size_t id_count);

#endif
