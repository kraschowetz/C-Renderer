#include "engine.h"
#include "timer.h"

Engine *create_engine() {
	Engine *self = (Engine*) malloc(sizeof(Engine));

	self->canvas = create_canvas(400, 300);
	self->running = false;

	return self;
}

void engine_stop(Engine *self) {
	destroy_canvas(self->canvas);
	free(self);

	self = NULL;
}

void poll_events(Engine *self) {
	SDL_Event e;
	SDL_PollEvent(&e);

	switch(e.type) {
		case SDL_QUIT:
			self->running = false;
			break;
	}
}

void engine_start(Engine *self) {
	self->running = true;
	Timer delta_timer = timer_start();
	Timer timer = timer_start();
	f32 last_time = 0.0f;

	while(self->running) {
		poll_events(self);

		self->canvas->renderer->time = (f32)(timer_get_ticks(&timer) / 1000.0);
		canvas_render(self->canvas);

		self->delta = (f32)(timer_get_ticks(&delta_timer) / 1000.0);
		self->frames++;
		delta_timer = timer_start();

		if((f32)(timer_get_ticks(&timer) / 1000.0) > last_time) {
			printf("%i\n", self->frames);
			self->frames = 0;
			last_time += 1.0f;
		}
	}

	engine_stop(self);
}
