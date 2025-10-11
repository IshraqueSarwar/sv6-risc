#include "proc.h"
#include "printf.h"
#include "uart.h"
#include "trap.h"
#include "timer.h"


static proc_t *current_proc = 0;

proc_t *myproc(void){
	return current_proc;
}


void proc_init(void){
	current_proc = 0;
}

void kill_current_process(void){
	proc_t *p = myproc();
	if(!p){
		kprintf("Kill current process: no current process, panic!!\n");
		return;
	}

	p->killed = 1;
	p->state = ZOMBIE;
	kprintf("proc %d killed\n", p->pid);
}


void schedule(void){
	// this needs to be implemented later
	kprintf("[SCHED] schedule() called -- not implemented");
}


#define SYS_write 	1
#define SYS_exit 	2


// this current implementation of the systemcall write isnt safe as the function
// directly accesses the mem and user can pass malicious code/addr and crash the
// kernel
// TODO: implement a safer version of the sys_write
static int sys_write(uint64_t fd, uint64_t buf_va, uint64_t len){
	(void)fd;
	const char *buf = (const char *)buf_va;

	for(uint64_t i = 0;i<len;i++){
		uart_putc(buf[i]);		
	}

	return (int)len;
}


static int sys_exit(int status){
	struct proc *p = myproc();
	kprintf("proc %d exit(%d)\n", p? p->pid:-1, status);
	if(p){
		p->killed = 1;
		p->state = ZOMBIE;
	}
	return 0;
}

int syscall_dispatch(){
	proc_t *p = myproc();

	if(!p || !p->tf){
		kprintf("syscall_dispatch: no current proc or trapframe\n");
		return -1;
	}

	trapframe_t *tf = p->tf;
	uint64_t num = tf->a7;
	uint64_t a0 = tf->a0;
	uint64_t a1 = tf->a1;
	uint64_t a2 = tf->a2;
	int ret = -1;
	
	switch(num){
		case SYS_write:
			ret = sys_write(a0, a1, a2);
			break;
		case SYS_exit:
			ret = sys_exit((int)a0);
			break;
		default:
			kprintf("unknown syscall %x\n", num);
			ret = -1;
			break;
	}

	tf->a0 = (uint64_t) ret;
	return ret;

}


