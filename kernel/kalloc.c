#include "kalloc.h"
#include "spinlock.h"
#include "memlayout.h"
#include <string.h>

struct run{
	struct run *next;
};

static struct run *freelist = 0;
static spinlock_t kmem_lock;
static unsigned long kmem_start, kmem_end;


void kinit(void *start_ptr, void *end_ptr){
	initlock(&kmem_lock, "kmem");

	kmem_start = PGGROUNDUP(start_ptr);
	kmem_end = PGGROUNDDOWN(end_ptr);

	// this part is very cool
	// so initially p1 = r1->0(as freelist)
	// then freelist->r1 therefore freelist->r1->0
	// over time as p1..p2..p3(pages are looped)
	// freelist = (rN) (which points to ->rN-1...->r3->r2->r1->0);
	// such a cool way to implement!
	for(unsigned long p = kmem_start; p+PGSIZE<=kmem_end;p+=PGSIZE){
		struct run *r = (struct run*)p;
		p->next = freelist;
		freelist = r;
	}

}


void *kalloc(void){
	// acquire spinlock to avoid raceconditions
	acquire(&kmem_lock);
	
	// get the most recent node/page
	struct run *r = freelist;
	if(r!=0){
		// mode the freelist head to the next page
		freelist = r->next;
	}
	// release the spinlock
	release(&kmem_lock);

	if(r!=0){
		// we fill up the entire 4kb with 5s so that later procs can validate
		memset(r, 5, PGSIZE);
	}
	// returning the kalloced page
	return (void*)r;

}


void kfree(void* ptr_addr){
	if(ptr_addr == 0)return;
	
	// overwriting freed memory w junk
	memset(ptr_addr, 1, PGSIZE);
	
	acquire(&kmem_lock);
	struct run *r = (struct run *)ptr_addr;
	r->next = freelist;
	freelist = r;
	release(&kmem_lock);
}
