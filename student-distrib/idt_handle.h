#ifndef IDT_HANDLE_H
#define IDT_HANDLE_H

#ifndef ASM

#include "x86_desc.h"
#include "lib.h"
#include "keyboard.h"
#include "rtc.h"

//  designate idt_desc_t struct as trap gate with default values
#define SET_TRAP_GATE(str)          \
do {                                \
    str.seg_selector = KERNEL_CS;   \
    str.reserved4 = 0x00;           \
    str.reserved3 = 1;              \
    str.reserved2 = 1;              \
    str.reserved1 = 1;              \
    str.size = 1;                   \
    str.reserved0 = 0;              \
    str.dpl = 0;                    \
    str.present = 1;                \
} while(0)
	
//  designate idt_desc_t struct as interrupt gate with default values
#define SET_INTR_GATE(str)          \
do {                                \
    str.seg_selector = KERNEL_CS;   \
    str.reserved4 = 0x00;           \
    str.reserved3 = 0;              \
    str.reserved2 = 1;              \
    str.reserved1 = 1;              \
    str.size = 1;                   \
    str.reserved0 = 0;              \
    str.dpl = 0;                    \
    str.present = 1;                \
} while(0)

//  initializes interrupt descriptor table
extern void idt_init(void);

/*	exception handler functions #0 - #19 defined by i386	*/
void _divide_by_zero(void), _reserved(void), _non_maskable_interrupt(void), _breakpoint(void), _overflow(void), _bound_range_exceeded(void), 
    _undefined_opcode(void), _no_math_coprocessor(void), _double_fault(void), _coprocessor_overrun(void), _invalid_tss(void), _segment_not_present(void), 
    _stack_segment_fault(void), _general_protection(void), _page_fault(void), _intel_reserved(void), _floating_point_error(void), _alignment_check(void), 
    _machine_check(void), _floating_point_except(void);

// void _system_call(void);

#endif /* ASM */

#endif /* IDT_HANDLE_H */
