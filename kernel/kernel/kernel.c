#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_pre_init(void) {
    terminal_initialize();
}

__attribute__ ((constructor)) void _DummyGloablCConstructor(void) {
    printf("_DummyGloablCConstructor is running and printf is available at this point\n");
}


void kernel_main(void) {
    printf("Hello, kernel World!\n");

    for (;;) { }
}
