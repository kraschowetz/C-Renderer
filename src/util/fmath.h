#ifndef FMATH_H
#define FMATH_H

#include "types.h"
#include <math.h>
#include <cglm/cglm.h>

#define PI ((f32)(GLM_PI))
#define PI_2 ((f32)(GLM_PI_2))
#define TAU (2 * PI)

#define cosf(x) ((f32)(cos(x)))
#define sinf(x) ((f32)(sin(x)))

#define radians(x) ((x) * (typeof(x))(PI / 180.0f))
#define degrees(x) ((x) * (typeof(x))(180.0f / PI))

#define min(a, b) ({ \
	typeof(a) _a = (a); \
	typeof(b) _b = (b); \
	_a < _b ? _a : _b; \
})

#define max(a, b) ({ \
	typeof(a) _a = (a); \
	typeof(b) _b = (b); \
	_a > _b ? _a : _b; \
})

#define clamp(x, mn, mx) ({\
	typeof(x) _x = (x); \
	typeof(mn) _min = (mn); \
	typeof(mx) _max = (mx); \
	max(_min, min(_max, _x)); \
})

#endif
