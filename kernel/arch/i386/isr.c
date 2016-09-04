#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <arch/i386/descriptors/idt.h>
#include <arch/i386/isr.h>
#include <drivers/vga/textmode.h>


extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

void _isr_install() {
    _idt_set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
    _idt_set_gate(1, (unsigned)_isr1, 0x08, 0x8E);
    _idt_set_gate(2, (unsigned)_isr2, 0x08, 0x8E);
    _idt_set_gate(3, (unsigned)_isr3, 0x08, 0x8E);
    _idt_set_gate(4, (unsigned)_isr4, 0x08, 0x8E);
    _idt_set_gate(5, (unsigned)_isr5, 0x08, 0x8E);
    _idt_set_gate(6, (unsigned)_isr6, 0x08, 0x8E);
    _idt_set_gate(7, (unsigned)_isr7, 0x08, 0x8E);
    _idt_set_gate(8, (unsigned)_isr8, 0x08, 0x8E);
    _idt_set_gate(9, (unsigned)_isr9, 0x08, 0x8E);
    _idt_set_gate(10, (unsigned)_isr10, 0x08, 0x8E);
    _idt_set_gate(11, (unsigned)_isr11, 0x08, 0x8E);
    _idt_set_gate(12, (unsigned)_isr12, 0x08, 0x8E);
    _idt_set_gate(13, (unsigned)_isr13, 0x08, 0x8E);
    _idt_set_gate(14, (unsigned)_isr14, 0x08, 0x8E);
    _idt_set_gate(15, (unsigned)_isr15, 0x08, 0x8E);
    _idt_set_gate(16, (unsigned)_isr16, 0x08, 0x8E);
    _idt_set_gate(17, (unsigned)_isr17, 0x08, 0x8E);
    _idt_set_gate(18, (unsigned)_isr18, 0x08, 0x8E);
    _idt_set_gate(19, (unsigned)_isr19, 0x08, 0x8E);
    _idt_set_gate(20, (unsigned)_isr20, 0x08, 0x8E);
    _idt_set_gate(21, (unsigned)_isr21, 0x08, 0x8E);
    _idt_set_gate(22, (unsigned)_isr22, 0x08, 0x8E);
    _idt_set_gate(23, (unsigned)_isr23, 0x08, 0x8E);
    _idt_set_gate(24, (unsigned)_isr24, 0x08, 0x8E);
    _idt_set_gate(25, (unsigned)_isr25, 0x08, 0x8E);
    _idt_set_gate(26, (unsigned)_isr26, 0x08, 0x8E);
    _idt_set_gate(27, (unsigned)_isr27, 0x08, 0x8E);
    _idt_set_gate(28, (unsigned)_isr28, 0x08, 0x8E);
    _idt_set_gate(29, (unsigned)_isr29, 0x08, 0x8E);
    _idt_set_gate(30, (unsigned)_isr30, 0x08, 0x8E);
    _idt_set_gate(31, (unsigned)_isr31, 0x08, 0x8E);
}

const char *exception_messages[] =
{
  "Exception: division by zero",
  "Exception: debug exception",
  "Exception: non-maskable interrupt",
  "Exception: breakpoint",
  "Exception: overflow",
  "Exception: out of bounds",
  "Exception: invalid opcode",
  "Exception: no coprocessor",
  "Exception: double fault",
  "Exception: coprocessor segment overrun",
  "Exception: bad TSS",
  "Exception: segment not present",
  "Exception: STACK FAULT",
  "Exception: GENERAL PROTECTION FAULT",
  "Exception: PAGE FAULT",
  "Exception: unknown interrupt",
  "Exception: COPROCESSOR FAULT"
  "Exception: alignment check",
  "Exception: machine check"
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION",
  "Exception: INTEL RESERVED EXCEPTION"
};

void _fault_handler(i386_registers_t *r) {
  if (r->int_no < 32) {
    //TODO: Replace printing with syscalls or something
    vga_textmode_setcolor(COLOR_RED);
    vga_textmode_writestring("\n");
    vga_textmode_writestring(exception_messages[r->int_no]);
    vga_textmode_writestring("\n\nStack Dump:\n");
    printf("EIP: 0x%x\n", r->eip);
    printf("ESP: 0x%x\n", r->esp);
    printf("Error Code: %d\n", (int)r->err_code);
    printf("\nHALT\n");
    abort();
  }
}
