# ifndef MEMLAYOUT_H
# define MEMLAYOUT_H

#include "types.h"

#define KERNEL_BASE 	0x80200000UL

#define UART0 		0x10000000L

#define PHYSTOP 	0x88000000UL

// page size
# define PGSIZE 	4096
# define PGSHIFT	12
# define PGGROUNDUP(sz)	(((sz)+PGSIZE-1) & ~(PGSIZE-1))
# define PGGROUNDDOWN(a) ((a) & ~(PGSIZE-1))

#define PGROUNDUP_PTR(p) ((void*)PGGROUNDUP((uintptr_t)(p)))
#define PGROUNDDOWN_PTR(p) ((void*)PGGROUNDDOWN((uintptr_t)(p)))

extern char _kernel_start[];
extern char _kernel_end[];


# endif
