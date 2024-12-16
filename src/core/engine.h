#ifndef ENGINE_H
#define ENGINE_H

#include "../util/util.h"
#include "../gfx/canvas.h"

typedef struct {
	Canvas *canvas;
	bool running;
	f32 delta;
	u32 frames;
} Engine;

Engine *create_engine();
void engine_start(Engine *self);
void engine_stop(Engine *self);
void poll_events(Engine *self);

#endif
