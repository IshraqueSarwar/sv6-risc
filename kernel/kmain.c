#include "printf.h"
#include "memlayout.h"
#include "kalloc.h"


void kmain(void){
	//uart_init();
	//uart_puts("We wrote the smallest kernel w GPT");
	kprintf("RISC v6 tinyOSX - first build %d/%d/%d\n", 21,9,2025);
	
	kprintf("kernel start: %x\n", _kernel_start);
	kprintf("kernel end:   %x\n",_kernel_end);
	kprintf("PHYSTOP:      %x\n", (void *)PHYSTOP);
	
	kinit(_kernel_end, (void*)PHYSTOP);


	// Test 1: allocating single page
	void *p = kalloc();
	if(p){
		kprintf("Allocated a page at %x\n", p);
	}else{
		kprintf("allocation failed\n");
	}

	// Test 2: allocating multiple pages
	for(int i = 0;i<5;i++){
		void *q = kalloc();
		if(q){
			kprintf("Page %d: %x\n", i, q);
		}else{
			kprintf("No more memory at i=%d", i);
			break;
		}
	}


	// Test 3: freeing and reallocating
	kprintf("Freeing the first page...\n");
	kfree(p);

	void *r = kalloc();
	kprintf("Re-allocating page at %x\n", r);
	

	// dont touch this loop, this is the infinite loop after entry to kernel
	while(1){
	}
	


}
