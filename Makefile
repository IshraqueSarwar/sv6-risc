PLATFORM = riscv64-unknown-elf
CC = $(PLATFORM)-gcc
LD = $(PLATFORM)-ld

CFLAGS = -Wall -Wextra -O2 -ffreestanding -nostdlib \
	 -march=rv64imac -mabi=lp64 -mcmodel=medany

OBJS = kernel/entry.o kernel/uart.o kernel/kmain.o kernel/printf.o \
       kernel/kalloc.o kernel/spinlock.o

all: kernel.elf


kernel.elf: $(OBJS)
	$(LD) -T kernel/link.ld -o $@ $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<


run: kernel.elf
	qemu-system-riscv64 -machine virt -nographic -kernel kernel.elf

clean:
	rm -f $(OBJS) kernel.elf
