.global load_idt     # Allows the C code to call idt_flush().

load_idt:
   mov 4(%esp), %edx  # EDX is 1st argument - IDT record pointer
   lidt (%edx)        # Load the IDT pointer.
   ret


# TODO:
#  - Check Calling Convetion, there maybe a bug in the following code...
#  - We should not call "CLI", instead the idt entry should specify, if interrupts should be enabeld

# This is our common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.
isr_common_stub:
   pusha                    # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov %ds, %ax             #Lower 16-bits of eax = ds.
   push %eax                #save the data segment descriptor

   mov $0x10, %ax           #load the kernel data segment descriptor
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs

   call isr_handler

   pop %eax        #reload the original data segment descriptor
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs

   popa                     # Pops edi,esi,ebp...

   add $0x08, %esp          #Cleans up the pushed error code and pushed ISR number

   iret           #pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

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
