.section .text
.globl _entry


_entry:
	la sp, stack_top
	call kmain
	j .


.section .bss
.align 4

stack:
	.skip 4096
stack_top:
