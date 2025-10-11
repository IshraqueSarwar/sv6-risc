#ifndef TRAP_H
#define TRAP_H

#include "types.h"

typedef struct trapframe{
	// we save all the registers before we switch to kernel mode
	uint64_t ra; // return addr register
	uint64_t sp; // stack pointer
	uint64_t gp; // global pointer
	uint64_t tp; // thread pointer
	uint64_t s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11; // preserved for fucntion calls
	uint64_t a0, a1, a2, a3, a4, a5, a6, a7; // function argumnets and  // return values
	uint64_t t0, t1, t2, t3, t4, t5, t6; // temporary value storage registers
}trapframe_t;


#endif
