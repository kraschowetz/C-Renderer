#include "renderer.h"
#include "../core/input.h"
#include "../core/timer.h"
#include "../core/camera.h"
#include <cglm/cam.h>
#include <cglm/struct/vec3.h>
#include <stdio.h>

vec3 cam;
Camera *camera;

Renderer create_renderer(SDL_Window *window) {

	Renderer self;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	self.context = SDL_GL_CreateContext(window);
	if(!self.context) {
		fprintf(stderr, "failed to init OpenGL!\n");
		exit(1);
	}

	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		fprintf(stderr, "failed to load OpenGL!\n");
		exit(1);
	}

	if(SDL_GL_SetSwapInterval(VSYNC_STATE) < 0) {
		fprintf(stderr, "failed to enable vsync!\n");
		exit(1);
	}

	GLfloat tri_vec_pos[9] = {
		0.0, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.0, 0.5, 0.0
	};

	GLfloat tri_vec_color[9] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};

	GLfloat quad_vec_pos[12] = {
		-0.5, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.5, 0.0,
		-0.5, 0.5, 0.0
	};

	GLfloat quad_vec_color[12] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0
	};

	self.tri = create_triangle(
		tri_vec_pos,
		tri_vec_color
	);

	self.quad = create_quad(
		quad_vec_pos,
		quad_vec_color
	);

	self.shader = create_shader(
		"./res/2d.vert",
		"./res/2d.frag"
	);

	self.time = 0.0;

	printf(
		"vendor:\t\t%s\nrenderer:\t%s\nversion:\t%s\nlang_version:\t%s\n",
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION),
		glGetString(GL_SHADING_LANGUAGE_VERSION)
	);

	camera = create_camera(45.0f);

	return self;
}

void destroy_renderer(Renderer *self) {
	destroy_triangle(self->tri);
	destroy_shader(&self->shader);
	free(camera);
}

void renderer_prepare() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glViewport(0,0, 400, 300);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void render(Renderer *self, SDL_Window *window) {
	renderer_prepare();

	mat4 model = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	vec3 scale = {1.5, 1.5, 1.5};
	
	mat4 rotation_matrix;
	glm_rotate_y(model, radians(self->time * 60.0f), rotation_matrix); // should use glm_rotate_at();
	
	mat4 translation_matrix;
	glm_translate_to(model, cam, translation_matrix);
	
	mat4 scale_matrix;
	glm_scale_to(model, scale, scale_matrix);
	
	// translate -> rotate -> scale
	glm_mat4_mulN((mat4 *[]){&model, &translation_matrix, &rotation_matrix, &scale_matrix}, 4, model);
	
	mat4 perspective_matrix;
	glm_perspective(degrees(45), 400.0f/300.0f, NEAR_PLANE, FAR_PLANE, perspective_matrix);
	

	shader_bind(&self->shader);
	shader_uniform_float(&self->shader, "time", 0);
	shader_uniform_mat4(&self->shader, "u_model", model);
	shader_uniform_mat4s(&self->shader, "u_perspective", camera->view_proj.projection);
	shader_uniform_mat4s(&self->shader, "u_view", camera->view_proj.view);

	triangle_render(self->tri);
	quad_render(self->quad);

	SDL_GL_SwapWindow(window);

	// m_gl_check(glBindBuffer(GL_ARRAY_BUFFER, 100)); // <- teste do macro gl_check
	
	if(get_key_pressed(SDL_SCANCODE_LEFT))
		camera->yaw += delta_time;
	if(get_key_pressed(SDL_SCANCODE_RIGHT))
		camera->yaw -= delta_time;
	if(get_key_pressed(SDL_SCANCODE_UP))
		camera->pitch += delta_time;
	if(get_key_pressed(SDL_SCANCODE_DOWN))
		camera->pitch -= delta_time;

	if(get_key_pressed(SDLK_d))
		camera->position.x -= delta_time;
	if(get_key_pressed(SDLK_a))
		camera->position.x += delta_time;
	if(get_key_pressed(SDLK_w))
		camera->position.z += delta_time;
	if(get_key_pressed(SDLK_s))
		camera->position.z -= delta_time;

	camera_update(camera);

}
