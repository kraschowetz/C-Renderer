#include "quad.h"
#include "vao.h"

Quad *create_quad(GLfloat position[12], GLfloat color[12]) {
	Quad *self = (Quad*)malloc(sizeof(Quad));

	self->vao = create_vao();
	vao_bind(&self->vao);
	self->vbo = create_vbo(GL_ARRAY_BUFFER);
	vbo_bind(&self->vbo);

	GLuint vbo_data_ids[2] = {0, 1};

	vbo_buffer(&self->vbo, (void*)position, 0, sizeof(GLfloat) * 12);
	vao_attr(&self->vao, &self->vbo, 0, 3, GL_FLOAT, 0, 0);
	
	//is this needed?
	self->vbo = create_vbo(GL_ARRAY_BUFFER);
	vbo_bind(&self->vbo);

	vbo_buffer(&self->vbo, (void*)color, 0, sizeof(GLfloat) * 12);
	vao_attr(&self->vao, &self->vbo, 1, 3, GL_FLOAT, 0, 0);

	vao_flush_attr(vbo_data_ids, 2);

	return self;
}

void destroy_quad(Quad *self) {
	destroy_vao(&self->vao);
	destroy_vbo(&self->vbo);

	free(self);
	self = NULL;
}

void quad_render(Quad *self) {
	vao_bind(&self->vao);

	GLuint ids[6] = GFX_QUAD_RENDERING_ORDER;

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ids);
}
