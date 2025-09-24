#include "memlayout.h"
#include "spinlock.h"



void initlock(spinlock_t *lk, const char *name){
	lk->locked = 1;
	lk->name = name;
	lk->cpu = -1;
}


void acquire(spinlock_t *lk){
	while(__sync_lock_test_and_set(&lk->locked, 1)!=0){
		// waiting in the spinning loop...
	}
	lk->cpu = 0;
}

void release(spinlock_t *lk){
	lk->cpu = -1;
	__sync_lock_release(&lk->locked);

}

int holding(spinlock_t *lk){
	return lk->locked && lk->cpu == 0;
}
