#include <stdint.h>

#include <string.h>

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;
idt_ptr_t idt_ptr;

// A struct describing an interrupt gate.
struct idt_entry_struct {
    uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
    uint16_t sel;                 // Kernel segment selector.
    uint8_t  always0;             // This must always be zero.
    uint8_t  flags;               // More flags. See documentation.
    uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;
idt_entry_t idt_entries[256];

// These extern directives let us access the addresses of our ASM ISR handlers. (defined in isr_asm.S)
extern void  isr0();
extern void  isr1();
extern void  isr2();
extern void  isr3();
extern void  isr4();
extern void  isr5();
extern void  isr6();
extern void  isr7();
extern void  isr8();
extern void  isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// 16 Interupt Request Lines for external devices  (defined in irq_asm.S)
extern void irq0();       // isr32
extern void irq1();       // isr33
extern void irq2();       // isr34
extern void irq3();       // isr35
extern void irq4();       // isr36
extern void irq5();       // isr37
extern void irq6();       // isr38
extern void irq7();       // isr39
extern void irq8();       // isr40
extern void irq9();       // isr41
extern void irq10();      // isr42
extern void irq11();      // isr43
extern void irq12();      // isr44
extern void irq13();      // isr45
extern void irq14();      // isr46
extern void irq15();      // isr47

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags;
}

// ASM Function in idt_asm.S. Loads the given IDT Pointer to registers
extern void load_idt(idt_ptr_t *idt_ptr);
extern void PIC_remap(void);

#define P        1 << 7  // Present, always 1
#define DPL      0 << 5  // privilege lvl 0  Todo: Change to 3 for user space code?
#define S        0 << 4  // s=0 for interrupt gates
#define GATETYPE 0xE     // 32 Bit Interrupt Gate
#define FLAGS ( P | DPL | S | GATETYPE )

void init_default_idt() {
    size_t i;
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

    PIC_remap();

    idt_set_gate( 0, (uint32_t) isr0, 0x08, FLAGS);
    idt_set_gate( 1, (uint32_t) isr1, 0x08, FLAGS);
    idt_set_gate( 2, (uint32_t) isr2, 0x08, FLAGS);
    idt_set_gate( 3, (uint32_t) isr3, 0x08, FLAGS);
    idt_set_gate( 4, (uint32_t) isr4, 0x08, FLAGS);
    idt_set_gate( 5, (uint32_t) isr5, 0x08, FLAGS);
    idt_set_gate( 6, (uint32_t) isr6, 0x08, FLAGS);
    idt_set_gate( 7, (uint32_t) isr7, 0x08, FLAGS);
    idt_set_gate( 8, (uint32_t) isr8, 0x08, FLAGS);
    idt_set_gate( 9, (uint32_t) isr9, 0x08, FLAGS);
    idt_set_gate(10, (uint32_t)isr10, 0x08, FLAGS);
    idt_set_gate(11, (uint32_t)isr11, 0x08, FLAGS);
    idt_set_gate(12, (uint32_t)isr12, 0x08, FLAGS);
    idt_set_gate(13, (uint32_t)isr13, 0x08, FLAGS);
    idt_set_gate(14, (uint32_t)isr14, 0x08, FLAGS);
    idt_set_gate(15, (uint32_t)isr15, 0x08, FLAGS);
    idt_set_gate(16, (uint32_t)isr16, 0x08, FLAGS);
    idt_set_gate(17, (uint32_t)isr17, 0x08, FLAGS);
    idt_set_gate(18, (uint32_t)isr18, 0x08, FLAGS);
    idt_set_gate(19, (uint32_t)isr19, 0x08, FLAGS);
    idt_set_gate(20, (uint32_t)isr20, 0x08, FLAGS);
    idt_set_gate(21, (uint32_t)isr21, 0x08, FLAGS);
    idt_set_gate(22, (uint32_t)isr22, 0x08, FLAGS);
    idt_set_gate(23, (uint32_t)isr23, 0x08, FLAGS);
    idt_set_gate(24, (uint32_t)isr24, 0x08, FLAGS);
    idt_set_gate(25, (uint32_t)isr25, 0x08, FLAGS);
    idt_set_gate(26, (uint32_t)isr26, 0x08, FLAGS);
    idt_set_gate(27, (uint32_t)isr27, 0x08, FLAGS);
    idt_set_gate(28, (uint32_t)isr28, 0x08, FLAGS);
    idt_set_gate(29, (uint32_t)isr29, 0x08, FLAGS);
    idt_set_gate(30, (uint32_t)isr30, 0x08, FLAGS);
    idt_set_gate(31, (uint32_t)isr31, 0x08, FLAGS);

    idt_set_gate(32, (uint32_t) irq0, 0x08, FLAGS);
    idt_set_gate(33, (uint32_t) irq1, 0x08, FLAGS);
    idt_set_gate(34, (uint32_t) irq2, 0x08, FLAGS);
    idt_set_gate(35, (uint32_t) irq3, 0x08, FLAGS);
    idt_set_gate(36, (uint32_t) irq4, 0x08, FLAGS);
    idt_set_gate(37, (uint32_t) irq5, 0x08, FLAGS);
    idt_set_gate(38, (uint32_t) irq6, 0x08, FLAGS);
    idt_set_gate(39, (uint32_t) irq7, 0x08, FLAGS);
    idt_set_gate(40, (uint32_t) irq8, 0x08, FLAGS);
    idt_set_gate(41, (uint32_t) irq9, 0x08, FLAGS);
    idt_set_gate(42, (uint32_t)irq10, 0x08, FLAGS);
    idt_set_gate(43, (uint32_t)irq11, 0x08, FLAGS);
    idt_set_gate(44, (uint32_t)irq12, 0x08, FLAGS);
    idt_set_gate(45, (uint32_t)irq13, 0x08, FLAGS);
    idt_set_gate(46, (uint32_t)irq14, 0x08, FLAGS);
    idt_set_gate(47, (uint32_t)irq15, 0x08, FLAGS);

//  for (i=48; i<256; i++)
//      idt_set_gate(i, (uint32_t) irq0, 0x08, FLAGS);

    load_idt(&idt_ptr);
}

