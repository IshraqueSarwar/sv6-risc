#ifndef PROC_H
#define PROC_H

#include "types.h"
#include "trap.h"

// we define the states that the process can be in
enum proc_state{
	UNUSED,
	EMBRYO,
	SLEEPING,
	RUNNABLE,
	RUNNING,
	ZOMBIE
};


typedef struct proc{
	int pid;
	enum proc_state state;
	trapframe_t *tf;	//pointer to process trapframe in kernel memory
	int killed;
	
}proc_t;


// functions
proc_t *myproc(void);	// current proc
void kill_current_process(void); // to mark process killed
void schedule(void);	// basic scheduler -> where the scheduling magic happens
void proc_init(void);

#endif
