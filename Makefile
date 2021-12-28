OBJECTS = boot.o io.o kmain.o printk.o fb/fb.o
CC = gcc
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector \
	 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c \
	 -I$(PWD)/include -g

LDFLAGS = -T link.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

all: vmfox

vmfox: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o vmfox

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o fb/*.o vmfox
