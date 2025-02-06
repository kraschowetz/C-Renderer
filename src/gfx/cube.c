#include "cube.h"
#include "gfx.h"
#include "vao.h"
#include "vbo.h"

Cube *create_cube(GLfloat position[36], GLfloat color[36]) {
	Cube *self = (Cube*)malloc(sizeof(Cube));
	
	self->vao = create_vao();
	vao_bind(&self->vao);
	self->vbo = create_vbo(GL_ARRAY_BUFFER);
	vbo_bind(&self->vbo);

	vbo_buffer(&self->vbo, (void*)position, 0, sizeof(GLfloat) * 36);
	vao_attr(&self->vao, &self->vbo, 0, 3, GL_FLOAT, 0, 0);

	self->vbo = create_vbo(GL_ARRAY_BUFFER);
	vbo_bind(&self->vbo);

	vbo_buffer(&self->vbo, (void*)color, 0, sizeof(GLfloat) * 36);
	vao_attr(&self->vao, &self->vbo, 1, 3, GL_FLOAT, 0, 0);

	return self;
}

void destroy_cube(Cube *self) {
	destroy_vao(&self->vao);
	destroy_vbo(&self->vbo);

	free(self);
	self = NULL;
}

void cube_render(const Cube *self) {
	vao_bind(&self->vao);

	GLuint ids[GFX_CUBE_IBO_SIZE] = GFX_CUBE_RENDERING_ORDER;

	glDrawElements(GL_TRIANGLES, GFX_CUBE_IBO_SIZE, GL_UNSIGNED_INT, ids);
}
