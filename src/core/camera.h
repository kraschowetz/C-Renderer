#ifndef CAMERA_H
#define CAMERA_H

#include "../util/util.h"
#include <cglm/struct.h>

#define VEC3_UP (vec3){0.0f, 1.0f, 0.0f}

/*
	TODO:
		-orthografic camera
*/

typedef struct {
	mat4s view, projection;
} ViewProjection;

typedef struct {
	ViewProjection view_proj;
	vec3s position, direction, up, right;
	f32 pitch, yaw, fov, aspect, near, far;
} Camera;

Camera *create_camera(f32 fov);
void camera_update(Camera *self);

#endif
