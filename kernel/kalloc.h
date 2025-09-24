#ifndef KALLOC_H
#define KALLOC_H

void kinit(void *start_ptr, void *end_ptr);
void *kalloc(void);
void kfree(void *ptr_addr);


#endif
