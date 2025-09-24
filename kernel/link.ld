OUTPUT_ARCH("riscv")
ENTRY(_entry)



SECTIONS {
	. = 0x80200000;
	
	PROVIDE(_kernel_start = .);

	.text : {
		*(.text*)
	}

	.rodata : { *(.rodata*) }
	
	.data : { *(.data*) }
	
	.bss : { *(.bss*) }

	. = ALIGN(0x1000);
	PROVIDE(_kernel_end = .);

}

