#include "triangle.h"

 Triangle *create_triangle(GLfloat position[9], GLfloat vert_color[9]) {
	 Triangle *self = (Triangle*)malloc(sizeof(Triangle));

	self->vao = create_vao();
	vao_bind(&self->vao);
	self->vbo = create_vbo(GL_ARRAY_BUFFER);
	vbo_bind(&self->vbo);
	
	GLuint vbo_data_ids[2] = {0, 1};

	vbo_buffer(&self->vbo, (void*)position, 0, sizeof(GLfloat) * 9);
	vao_attr(&self->vao, &self->vbo, 0, 3, GL_FLOAT, 0, 0);

	self->vbo = create_vbo(GL_ARRAY_BUFFER);
	vbo_bind(&self->vbo);

	vbo_buffer(&self->vbo, (void*)vert_color, 0, sizeof(GLfloat) * 9);
	vao_attr(&self->vao, &self->vbo, 1, 3, GL_FLOAT, 0, 0);
	
	vao_flush_attr(vbo_data_ids, 2);

	return self;
}

void destroy_triangle( Triangle *self) {
	destroy_vao(&self->vao);
	destroy_vbo(&self->vbo);

	free(self);
	self = NULL;
}

void triangle_render( Triangle *self) {
	vao_bind(&self->vao);
	glDrawArrays(
		GL_TRIANGLES,
		0,
		3
	);
}