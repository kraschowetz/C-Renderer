#include "timer.h"
#include <SDL2/SDL_timer.h>

Timer timer_start() {
	Timer self;
	self.start_time = SDL_GetTicks();

	return self;
}

u32 timer_get_ticks(Timer *self) {
	return SDL_GetTicks() - self->start_time;
}

