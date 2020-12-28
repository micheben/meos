#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_pre_init(void) {
	terminal_initialize();
}

__attribute__ ((constructor)) void _DummyGloablCConstructor(void) {
	printf("_DummyGloablCConstructor is running and printf is available at this point\n");
}


static uint32_t i = 0;
void kernel_main(void) {
	printf("Hello, kernel World!\n");

	for (;;) {
		++i;
		if (i == 0)
			printf("overflow\n");
	}
}
