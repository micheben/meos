#include <stdint.h>
#include <stdio.h>

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
