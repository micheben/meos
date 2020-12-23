#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_pre_init(void) {
	terminal_initialize();
}

__attribute__ ((constructor)) void _DummyGloablCConstructor(void) {
	printf("_DummyGloablCConstructor is running and printf is available at this point\n");
}


typedef struct registers {
	uint32_t ds;                  // Data segment selector
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
	uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
	uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t* regs) {
	printf("recieved interrupt  %#08X\n", regs->int_no);
}


void kernel_main(void) {
	printf("Hello, kernel World!\n");
	__asm__ __volatile__ ("int $0x3");


	printf("Done...!\n");

}
