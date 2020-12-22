.global load_idt     # Allows the C code to call idt_flush().

load_idt:
    mov 4(%esp), %edx  # EDX is 1st argument - IDT record pointer
    lidt (%edx)        # Load the IDT pointer.
    ret


# TODO:
#  - Pass Struct as point
#  - We should not call "CLI", instead the idt entry should specify, if interrupts should be enabeld

# This is our common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.

.macro repush offset
    mov \offset(%esp), %eax
    push %eax
.endm

isr_common_stub:
    push %eax                # current eax
    mov %ds, %ax             #Lower 16-bits of eax = ds.
    push %eax                #save ds
    # Stack bevor building our struct. (1)
    # (32) ss
    # (28) useresp
    # (24) eflags
    # (20) cs
    # (16) eip
    # (12) err_code
    # ( 8) int_no
    # ( 4) eax
    # ( 0) ds
    #-------------------------
    # Now we build our registers parameter struct  (Hint since each repush increments esp, the offset stays the same
    repush 32        # load ss       into eax and repush
    repush 32        # load useresp  into eax and repush
    repush 32        # load eflags   into eax and repush
    repush 32        # load cs       into eax and repush
    repush 32        # load eip      into eax and repush
    repush 32        # load err_code into eax and repush
    repush 32        # load int_no   into eax and repush

    mov 32(%esp), %eax # Restore eax from bevor function call
    pusha              # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov %ds, %ax     # load ds into eax again, (easier than with the offset, because of pusha
    push %eax        # ... and push onto stack
    #
    # Struct is now complete (16 elements with each 32 Bit)
    #------------------------

    mov $0x10, %ax   #load the kernel data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    call isr_handler

    # Now first of all, we have to remove all the struct parameter parts, because they may (and will) be trashed by the c code / gcc
    # (Remember: We call isr_handler by value, so we transfer ownership of the specific stack content to the c code)
    add $0x40, %esp       # Hint: We have 16 * 32Bit Variables, so 64 Bytes Stack Content ( => 0x40)
    #-------------------------
    # Stack is the same as in (1)
    pop %eax        #reload the original data segment descriptor
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    add $0x0C, %esp          # Cleans up the pushed eax Value, the error code and ISR number,
                                     # Hint: %eax is a scratch register, so we don't have to restore it,
                                     #       we only pushed the content, so we can give the true value to our c function

    iret           #pops the 5 remaining values: CS, EIP, EFLAGS, SS, and ESP

.macro isr_noerrcode i  #define a macro, taking one parameter
    .global isr\i
    isr\i:
        cli
        push $0
        push $\i
        jmp isr_common_stub
.endm

.macro isr_errcode i
    .global isr\i
    isr\i:
        cli
        push $\i
        jmp isr_common_stub
.endm


isr_noerrcode  0
isr_noerrcode  1
isr_noerrcode  2
isr_noerrcode  3
isr_noerrcode  4
isr_noerrcode  5
isr_noerrcode  6
isr_noerrcode  7
isr_errcode    8
isr_noerrcode  9
isr_errcode   10
isr_errcode   11
isr_errcode   12
isr_errcode   13
isr_errcode   14
isr_noerrcode 15
isr_noerrcode 16
isr_noerrcode 17
isr_noerrcode 18
isr_noerrcode 19
isr_noerrcode 20
isr_noerrcode 21
isr_noerrcode 22
isr_noerrcode 23
isr_noerrcode 24
isr_noerrcode 25
isr_noerrcode 26
isr_noerrcode 27
isr_noerrcode 28
isr_noerrcode 29
isr_noerrcode 30
isr_noerrcode 31
