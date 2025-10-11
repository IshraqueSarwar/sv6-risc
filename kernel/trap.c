#include "types.h"
#include "trap.h"
#include "printf.h"
#include "plic.h"


void trap_handler(void){
	uint64_t scause, sepc, stval;

	asm volatile("csrr %0, scause"	: "=r"(scause));
	asm volatile("csrr %0, sepc"	: "=r"(sepc));
	asm volatile("csrr %0, stval"	: "=r"(stval));
	
	int is_interrupt = (scause >> 63) & 1;
	uint64_t cause = scause & 0xfff;
	

	if(is_interrupt){
	kprintf("[INTERRUPT] scause=%x, sepc=%x, stval=%x\n", scause, sepc, stval);
		/*switch(cause){
			cause 1:
				// handle_software_interrupt();
				break;
			cause 5:
				// handle_timer_interrupt();
				break;
			cause 9:
				// handle_external_interrupt();
				break;
		}*/
	}else{	
	kprintf("[EXCEPTION] scause=%x, sepc=%x, stval=%x\n", scause, sepc, stval);
		
		/*switch(cause){
			cause 2:
				//handle_illegal_instructions();
				break;
			cause 8:
				// handle_ecall();
				break;
			cause 12:
				//handle_instruction_page_fault();
				break;
		
		
		
		}*/
	
	}


}



