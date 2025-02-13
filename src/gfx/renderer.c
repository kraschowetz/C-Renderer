#include "renderer.h"
#include "../core/input.h"
#include "../core/timer.h"
#include "camera.h"
#include "cube.h"
#include "window.h"
#include <SDL2/SDL_keycode.h>
#include <cglm/struct/vec3.h>
#include <math.h>

PerspectiveCamera *camera;
OrthoCamera *o_camera;

Renderer create_renderer(SDL_Window *window) {

	Renderer self;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	self.context = SDL_GL_CreateContext(window);
	if(!self.context) {
		THROW_ERR("failed to init OpenGL\n");
	}

	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		THROW_ERR("failed to load OpenGl\n");
	}

	if(SDL_GL_SetSwapInterval(VSYNC_STATE) < 0) {
		THROW_ERR("failed to enable vsync\n");
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

	GLfloat cube_vec_pos[36] = {
		-1.0f, -1.0f, 1.0f, //frontface
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, //backface
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f
	};

	GLfloat cube_vec_color[36] = {
		1.0, 0.0, 0.0, //frontface
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, //backface
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
	};

	self.tri = create_triangle(
		tri_vec_pos,
		tri_vec_color
	);

	self.quad = create_quad(
		quad_vec_pos,
		quad_vec_color
	);

	self.cube = create_cube(
		cube_vec_pos,
		cube_vec_color
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

	camera = create_perspective_camera(45.0f);
	o_camera = create_ortho_camera((vec2s){{-1.0f, -1.0f}}, (vec2s){{10.0f, 10.0f}});

	return self;
}

void destroy_renderer(Renderer *self) {
	destroy_triangle(self->tri);
	destroy_quad(self->quad);
	destroy_cube(self->cube);
	destroy_shader(&self->shader);
	destroy_perspective_camera(camera);
	destroy_ortho_camera(o_camera);
}

void renderer_prepare() {
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glViewport(0,0, g_window.width, g_window.height);
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
	glm_rotate_y(model, DEG2RAD(self->time * 0.0f), rotation_matrix); // should use glm_rotate_at();
	
	mat4 translation_matrix;
	glm_translate_to(model, (vec3){0.0f, 0.0f, 0.0f}, translation_matrix);
	
	mat4 scale_matrix;
	glm_scale_to(model, scale, scale_matrix);
	
	// translate -> rotate -> scale
	glm_mat4_mulN((mat4 *[]){&model, &translation_matrix, &rotation_matrix, &scale_matrix}, 4, model);
	
	mat4 perspective_matrix;
	glm_perspective(RAD2DEG(45), g_window.aspect, NEAR_PLANE, FAR_PLANE, perspective_matrix);
	

	shader_bind(&self->shader);
	shader_uniform_float(&self->shader, "time", self->time);
	shader_uniform_mat4(&self->shader, "u_model", model);
	shader_uniform_mat4s(&self->shader, "u_perspective", camera->view_proj.projection);
	shader_uniform_mat4s(&self->shader, "u_view", camera->view_proj.view);

	/* triangle_render(self->tri); */
	/* quad_render(self->quad); */
	cube_render(self->cube);

	/* UI pass */

	shader_uniform_mat4s(&self->shader, "u_perspective", o_camera->view_proj.projection);
	shader_uniform_mat4s(&self->shader, "u_view", o_camera->view_proj.view);

	triangle_render(self->tri);
	quad_render(self->quad);

	SDL_GL_SwapWindow(window);

	// m_gl_check(glBindBuffer(GL_ARRAY_BUFFER, 100)); // <- teste do macro gl_check
	
	//cam movement

	if(get_key_pressed(SDL_SCANCODE_LEFT))
		camera->yaw += delta_time;
	if(get_key_pressed(SDL_SCANCODE_RIGHT))
		camera->yaw -= delta_time;
	if(get_key_pressed(SDL_SCANCODE_UP))
		camera->pitch += delta_time;
	if(get_key_pressed(SDL_SCANCODE_DOWN))
		camera->pitch -= delta_time;
	
	vec3s movement, dir, forward, right;
	movement = GLMS_VEC3_ZERO;
	dir = GLMS_VEC3_ZERO;
	forward = (vec3s){{SINF(camera->yaw), 0, COSF(camera->yaw)}};
	right = glms_vec3_cross((vec3s){{0.0f, 1.0f, 0.0f}}, forward);

	if(get_key_pressed(SDLK_d)) {
		dir = glms_vec3_sub(dir, right);
	}
	if(get_key_pressed(SDLK_a)) {
		dir = glms_vec3_add(dir, right);
	}
	if(get_key_pressed(SDLK_w)) {
		dir = glms_vec3_add(dir, forward);
	}
	if(get_key_pressed(SDLK_s)) {
		dir = glms_vec3_sub(dir, forward);
	}
	
	if(!isnan(glms_vec3_norm(dir))) {
		const f32 speed = 5.0f;
		movement = glms_normalize(dir);
		movement = glms_vec3_scale(movement, speed * delta_time);
	}

	camera->position = glms_vec3_add(camera->position, movement);

	perspective_camera_update(camera);
	ortho_camera_update(o_camera);
}
