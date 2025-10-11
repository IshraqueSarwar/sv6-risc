#include "kalloc.h"
#include "spinlock.h"
#include "memlayout.h"
#include "printf.h"
#include "types.h"


struct run{
	struct run *next;
};

static struct run *freelist = 0;
static spinlock_t kmem_lock;



// we need to move this memset later to string.h
void* memset(void* dest, int ch, size_t count) {
    unsigned char* p = dest;
    while(count--) {
        *p++ = (unsigned char)ch;
    }
    return dest;
}


void kinit(void *start_ptr, void *end_ptr){
	//sanity check
	if(start_ptr>=end_ptr){
		kprintf("kinit: invalid memory range %x-%x\n", start_ptr, end_ptr);
	}


	initlock(&kmem_lock, "kmem");

	void* kmem_start = PGROUNDUP_PTR((uintptr_t)start_ptr);
	void* kmem_end = PGROUNDDOWN_PTR((uintptr_t)end_ptr);

	kprintf("kinit: start=%x, end=%x\n", kmem_start, kmem_end);

	// this part is very cool
	// so initially p1 = r1->0(as freelist)
	// then freelist->r1 therefore freelist->r1->0
	// over time as p1..p2..p3(pages are looped)
	// freelist = (rN) (which points to ->rN-1...->r3->r2->r1->0);
	// such a cool way to implement!
	//int i = 0;
	for(void* p = kmem_start; p<kmem_end;p+=PGSIZE){
		struct run *r = (struct run*)p;
		r->next = freelist;
		freelist = r;
		//kprintf("freepage: %d\n", i);
		//i++;
	}
	kprintf("kinit: Done creating freepages!\n");

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
