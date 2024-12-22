#include "camera.h"

Camera *create_camera(f32 fov) {
	Camera *self = calloc(1, sizeof(Camera));
	self->fov = fov;
	self->aspect = 400.0f / 300.0f; // <- use variables
	self->near = 0.01f;
	self->far = 1000.0f;

	camera_update(self);

	return self;
}

void camera_update(Camera *self) {
	self->pitch = clamp(self->pitch, -PI_2, PI_2);
	self->yaw = (self->yaw < 0 ? TAU : 0.0f) + fmodf(self->yaw, TAU);
	
	self->direction = (vec3s){{
		cosf(self->pitch) * sinf(self->yaw),
		sinf(self->pitch),
		cosf(self->pitch) * cosf(self->yaw)
	}};
	glms_vec3_normalize(self->direction);

	self->right = glms_vec3_cross((vec3s){{0.0f, 1.0f, 0.0f}}, self->direction);
	self->up = glms_vec3_cross(self->direction, self->right);

	self->view_proj.view = glms_lookat(
		self->position,
		glms_vec3_add(self->position, self->direction),
		self->up
	);
	self->view_proj.projection = glms_perspective(
		self->fov,
		self->aspect,
		self->near,
		self->far
	);
}
