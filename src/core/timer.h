#ifndef TIMER_H
#define TIMER_H

#include "../util/util.h"

typedef struct {
	u32 start_time;
} Timer;

Timer timer_start();
u32 timer_get_ticks(Timer *self);

extern f32 delta_time;

#endif
