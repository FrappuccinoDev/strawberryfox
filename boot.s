global strawberryloader

MAGIC_NUMBER equ 0x1badb002
FLAGS equ (1 << 0) | (1 << 1)
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)
KERNEL_STACK_SIZE equ 16384

section .multiboot
align 4
header_start:
;	dd 0x1badb002
;	dd (1 << 0) | (1 << 1)
;	dd -(0x1badb002 + ((1 << 0) | (1 << 1)))
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
header_end:

section .bss
align 16
kernel_stack:
	resb KERNEL_STACK_SIZE
stack_top:

section .text
align 4

strawberryloader:
	cli
	;mov esp, kernel_stack + KERNEL_STACK_SIZE
	;mov ebp, kernel_stack + KERNEL_STACK_SIZE
	mov esp, stack_top
	mov ebp, stack_top
	extern kmain
	push ebx
	call kmain
	cli
.haltloop:
	hlt
	jmp .haltloop
