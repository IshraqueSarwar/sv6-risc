#include "memlayout.h"
#include "types.h"

#define UART0 0x10000000L


void uart_init(void){
}


void uart_putc(char c){
	//we create the pointer *uart to the memory location defined by UART0
	volatile uint8_t *uart = (uint8_t *)UART0;
	// we place the charater at the mem addr *uart->UART0
	*uart = c;
}


void uart_puts(const char *s){
	// while the pointer of *s doesnt reach null pointer
	while(*s){
		// we put the char pointered by *s and increment it
		uart_putc(*s++);
	}

}

