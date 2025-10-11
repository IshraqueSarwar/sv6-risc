#ifndef PLIC_H
#define PLIC_H

#include "types.h"

void plic_init(void);
int plic_claim(void);
void plic_complete(int irq);

#define UART0_IRQ 10

#endif
