#ifndef GFX_H
#define GFX_H

#include "../../include/glad/include/glad/glad.h"
#include "../util/util.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>

static inline void _gl_clear_all_errors() {
	while(glGetError() != GL_NO_ERROR) {} //:)
}

static inline bool _gl_check_error_status(const char *function, u32 line) {
	GLenum err = glGetError();
	while(err) {
		printf("GL ERROR %u\tline: %u\tfunction: %s\n", err, line, function);
		return true;
	}
	return false;
}

#define m_gl_check(x) _gl_clear_all_errors(); x; _gl_check_error_status(#x, __LINE__);

#endif
