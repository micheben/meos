# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp

    cli   # Disable interrupts during setup of GDT, IDT and PIT

    # Init the GDT and the IDT
    call init_default_gdt
    call init_default_idt

    push $100
    call init_irq0_timer
    add $0x04, %esp    # Cleans up the pushed error code and ISR number,

    sti  # Enable Interrupts

    # Call the pre Init, so some of the functionality is avaliable for global constructors.
    call kernel_pre_init

    # Call the global constructors.
    call _init

    # Transfer control to the main kernel.
    call kernel_main

    # Hang if kernel_main unexpectedly returns.
    cli

    push $69
    call putchar
    add $0x04, %esp

    push $82
    call putchar
    add $0x04, %esp

    push $82
    call putchar
    add $0x04, %esp

    push $82
    call putchar
    add $0x04, %esp

1:  hlt
    jmp 1b
.size _start, . - _start
