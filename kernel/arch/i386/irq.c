#include <stdint.h>
#include <stdio.h>

extern void send_divisior_to_PID(uint32_t);

void init_irq0_timer(uint32_t frequency) {
    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / frequency;

    printf("%#08X\n%#08X\n", frequency, divisor);

    send_divisior_to_PID(divisor);
}

// These functions get called from our ASM irq\i.
extern void EOI_master(void);
extern void EOI_slave(void);

static uint32_t system_ticks = 0;
void irq0_handler() {
    ++system_ticks;
    EOI_master();
}

void irq1_handler(void) {
    printf("irq1 handler\n");
    EOI_master();
}

void irq2_handler(void) {
    printf("irq2 handler\n");
    EOI_master();
}

void irq3_handler(void) {
    printf("irq3 handler\n");
    EOI_master();
}

void irq4_handler(void) {
    printf("irq4 handler\n");
    EOI_master();
}

void irq5_handler(void) {
    printf("irq5 handler\n");
    EOI_master();
}

void irq6_handler(void) {
    printf("irq6 handler\n");
    EOI_master();
}

void irq7_handler(void) {
    printf("irq7 handler\n");
    EOI_master();
}

void irq8_handler(void) {
    printf("irq8 handler\n");
    EOI_slave();
    EOI_master();
}

void irq9_handler(void) {
    printf("irq9 handler\n");
    EOI_slave();
    EOI_master();
}

void irq10_handler(void) {
    printf("irq10 handler\n");
    EOI_slave();
    EOI_master();
}

void irq11_handler(void) {
    printf("irq11 handler\n");
    EOI_slave();
    EOI_master();
}

void irq12_handler(void) {
    printf("irq12 handler\n");
    EOI_slave();
    EOI_master();
}

void irq13_handler(void) {
    printf("irq13 handler\n");
    EOI_slave();
    EOI_master();
}

void irq14_handler(void) {
    printf("irq14 handler\n");
    EOI_slave();
    EOI_master();
}

void irq15_handler(void) {
    printf("irq15 handler\n");
    EOI_slave();
    EOI_master();
}

