# ifndef MEMLAYOUT_H
# define MEMLAYOUT_H


#define KERNEL_BASE 	0x80200000UL

#define UART0 		0x10000000L

#define PHYSTOP 	(KERNEL_BASE+128*1024*1024)

// page size
# define PGSIZE 	4096
# define PGSHIFT	12
# define PGGROUNDUP(sz)	(((sz)+PGSIZE-1) & ~(PGSIZE-1))
# define PGGROUNDDOWN(a) ((a) & ~(PGSIZE-1))


extern char _kernel_start[];
extern char _kernel_end[];


# endif
