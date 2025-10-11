#include "timer.h"
#include "printf.h"

volatile uint64_t ticks = 0;

#define CLINT_MTIMECMP(base, hart) ((volatile uint64_t *)((base) + 0x4000 + 8*(hart)))
#define CLINT_MTIME(base)          ((volatile uint64_t *)((base) + 0xBFF8))
#define CLINT_BASE 0x02000000UL


void set_next_timer(uint64_t next_t){
	*CLINT_MTIMECMP(CLINT_BASE, 0) = next_t;
}


void init_timer(void){
	set_next_timer(1000000ULL);
}

void timer_tick(void){
	ticks++;

	if((ticks)%100==0){
		kprintf("[TIMER] ticks=%d\n", ticks);
	}

	set_next_timer(ticks +1000);
}
