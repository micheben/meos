.global send_divisior_to_PID
send_divisior_to_PID:
    mov $0x34, %al                  #channel 0, lobyte/hibyte, rate generator
    outb %al, $0x43

    mov 4(%esp), %eax                   # set EDA to 1st argument - the divisior
    outb %al,$0x40                       #Set low byte of PIT reload value

    mov %ah,%al                         #ax = high 8 bits of reload value
    outb %al,$0x40                       #Set high byte of PIT reload value

    # unmask/activate all IRQs
    mov $0x0, %al
    outb %al, $0x21
    outb %al, $0xA1


.global EOI_master
EOI_master:
    mov $0x20, %al
    outb %al, $0x20
    ret

.global EOI_slave
EOI_slave:
    mov $0x20, %al
    outb %al, $0xA0
    ret

.global irq0
irq0:
    pusha
    call irq0_handler
    popa
    iret

.global irq1
irq1:
    pusha
    call irq1_handler
    popa
    iret

.global irq2
irq2:
    pusha
    call irq2_handler
    popa
    iret

.global irq3
irq3:
    pusha
    call irq3_handler
    popa
    iret

.global irq4
irq4:
    pusha
    call irq4_handler
    popa
    iret

.global irq5
irq5:
    pusha
    call irq5_handler
    popa
    iret

.global irq6
irq6:
    pusha
    call irq6_handler
    popa
    iret

.global irq7
irq7:
    pusha
    call irq7_handler
    popa
    iret

.global irq8
irq8:
    pusha
    call irq8_handler
    popa
    iret

.global irq9
irq9:
    pusha
    call irq9_handler
    popa
    iret

.global irq10
irq10:
    pusha
    call irq10_handler
    popa
    iret

.global irq11
irq11:
    pusha
    call irq11_handler
    popa
    iret

.global irq12
irq12:
    pusha
    call irq12_handler
    popa
    iret

.global irq13
irq13:
    pusha
    call irq13_handler
    popa
    iret

.global irq14
irq14:
    pusha
    call irq14_handler
    popa
    iret

.global irq15
irq15:
    pusha
    call irq15_handler
    popa
    iret
