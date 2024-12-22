#include "timer.h"
#include <SDL2/SDL_timer.h>

f32 delta_time = 0.0f;

Timer timer_start() {
	Timer self;
	self.start_time = SDL_GetTicks();

	return self;
}

u32 timer_get_ticks(Timer *self) {
	return SDL_GetTicks() - self->start_time;
}

