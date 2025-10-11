#ifndef TIMER_H
#define TIMER_H

#include "types.h"

extern volatile uint64_t ticks;

void timer_init(void);
void timer_tick(void);
void set_next_timer(uint64_t next_t);


#endif
