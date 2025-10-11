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

//plic base and macros
#define PLIC_BASE	0x0c000000UL
#define PLIC_PRIORITY	(PLIC_BASE + 0x0000)
#define PLIC_PENDING	(PLIC_BASE + 0x1000)
#define PLIC_ENABLE	(PLIC_BASE + 0x2000)
#define PLIC_CONTEXT	(PLIC_BASE + 0x200000)

#define PLIC_ENABLE_TARGET(ctx) (PLIC_ENABLE + (ctx)*0x80)
#define PLIC_CONTEXT_PRIORITY(ctx) (PLIC_CONTEXT + (ctx)*0x1000)
#define PLIC_CONTEXT_CLAIM(ctx) (PLIC_CONTEXT + (ctx)*0x1000 + 4)


# endif
