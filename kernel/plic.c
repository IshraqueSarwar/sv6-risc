#include "plic.h"
#include "printf.h"
#include "memlayout.h"
#include "types.h"

static inline void mmio_write(uint64_t addr, uint32_t value){
	*(volatile uint32_t*)addr = value;
}

static inline uint32_t mmio_read(uint64_t addr){
	return *(volatile uint32_t*)addr;
}

#define PLIC_SUPERVISOR_CONTEXT 1

void plic_init(void){

	mmio_write(PLIC_PRIORITY+UART0_IRQ * 4, 1);
	mmio_write(PLIC_ENABLE_TARGET(PLIC_SUPERVISOR_CONTEXT) + (UART0_IRQ/32)*4,
			1u<<(UART0_IRQ % 32));

	mmio_write(PLIC_CONTEXT_PRIORITY(PLIC_SUPERVISOR_CONTEXT), 0);
}

int plic_claim(void){
	uint32_t irq = mmio_read(PLIC_CONTEXT_CLAIM(PLIC_SUPERVISOR_CONTEXT));
	return (int) irq;
}


void plic_complete(int irq){
	if(irq<=0)return;
	mmio_write(PLIC_CONTEXT_CLAIM(PLIC_SUPERVISOR_CONTEXT), (uint32_t)irq);
}


