.global load_idt     # Allows the C code to call idt_flush().

load_idt:
    mov 4(%esp), %edx  # EDX is 1st argument - IDT record pointer
    lidt (%edx)        # Load the IDT pointer.
    ret



# #define PIC1        0x20        /* IO base address for master PIC */
# #define PIC2        0xA0        /* IO base address for slave PIC */
# #define PIC1_COMMAND    PIC1
# #define PIC1_DATA   (PIC1+1)
# #define PIC2_COMMAND    PIC2
# #define PIC2_DATA   (PIC2+1)
# 
# #define ICW1_ICW4   0x01        /* ICW4 (not) needed */
# #define ICW1_SINGLE 0x02        /* Single (cascade) mode */
# #define ICW1_INTERVAL4  0x04        /* Call address interval 4 (8) */
# #define ICW1_LEVEL  0x08        /* Level triggered (edge) mode */
# #define ICW1_INIT   0x10        /* Initialization - required! */
#  
# #define ICW4_8086   0x01        /* 8086/88 (MCS-80/85) mode */
# #define ICW4_AUTO   0x02        /* Auto (normal) EOI */
# #define ICW4_BUF_SLAVE  0x08        /* Buffered mode/slave */
# #define ICW4_BUF_MASTER 0x0C        /* Buffered mode/master */
# #define ICW4_SFNM   0x10        /* Special fully nested (not) */

.global PIC_remap

PIC_remap:
    # tell both PIC that a reinit will come now
    mov $0x11, %al
    outb %al, $0x20
    outb %al, $0xA0

    # tell both PICs their Interrupt Number Offset
    mov $0x20, %al
    outb %al, $0x21
    mov $0x28, %al
    outb %al, $0xA1

    # tell Master PIC that there is a slave on port 2 (0000 0100)
    mov $0x04, %al
    outb %al, $0x21

    # tell Slave PIC its cascade identity (0000 0010)
    mov $0x02, %al
    outb %al, $0xA1

    # activate 8086/88 (MCS-80/85) mode on both PIC
    mov $0x01, %al
    outb %al, $0x21
    outb %al, $0xA1

    # unmask/activate all IRQs
    mov $0x0, %al
    outb %al, $0x21
    outb %al, $0xA1


