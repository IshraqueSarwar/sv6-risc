#ifndef SPINLOCK_H
#define SPINLOCK_H

typedef struct{
	volatile int locked;
	const char *name;
	int cpu;
}spinlock_t;

void initlock(spinlock_t *lk, const char *name);
void acquire(spinlock_t *lk);
void release(spinlock_t *lk);
int holding(spinlock_t *lk);


#endif
