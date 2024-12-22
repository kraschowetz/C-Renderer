#include "engine.h"
#include "timer.h"
#include "input.h"
#include <SDL2/SDL_events.h>
#include <stdio.h>

Engine *create_engine() {
	Engine *self = (Engine*) malloc(sizeof(Engine));

	g_window = create_window("renderer", 800, 600);
	g_window.renderer = create_renderer(g_window.sdl_window);
	self->running = false;

	return self;
}

void engine_stop(Engine *self) {
	destroy_window(&g_window);

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

	update_input_state(e);
}

void engine_start(Engine *self) {
	self->running = true;
	Timer delta_timer = timer_start();
	Timer timer = timer_start();
	f32 last_time = 0.0f;

	while(self->running) {
		poll_events(self);

		g_window.renderer.time = (f32)(timer_get_ticks(&timer) / 1000.0);
		window_render(&g_window);

		self->delta = (f32)(timer_get_ticks(&delta_timer) / 1000.0);
		delta_time = (f32)(timer_get_ticks(&delta_timer) / 1000.0);
		self->frames++;
		delta_timer = timer_start();

		if((f32)(timer_get_ticks(&timer) / 1000.0) > last_time) {
			printf("%i\n", self->frames);
			self->frames = 0;
			last_time += 1.0f;
		}

		if(get_key_just_released(SDLK_SPACE)) {
			printf("apertou!\n");
		}

		if(get_mouse_button_just_pressed(1)) {
			printf("%i\n", get_mouse_click_ammount());
		}
	}

	engine_stop(self);
}
