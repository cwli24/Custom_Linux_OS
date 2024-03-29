#ifndef IDT_HANDLE_H
#define IDT_HANDLE_H

//	number of default exceptions in IDT
#define USED_EXCEPTIONS	20
//	number of PIC interrupts in IDT
#define PIC_INTRS	16

#ifndef ASM

#include "x86_desc.h"
#include "lib.h"
#include "timer.h"
#include "keyboard.h"
#include "rtc.h"
#include "syscalls.h"

// Designate idt_desc_t struct as trap gate with default values, used for exceptions
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
	
// Designate idt_desc_t struct as interrupt gate with default values, used for interrupts
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

// Prints the exception message, then calls sys_halt to terminate the program
#define PRINT_MESSAGE(message)      \
do {                                \
    printf(message);                \
    except_raised = 1;              \
    sys_halt(0);                    \
    return;                         \
} while(0)

// Initializes interrupt descriptor table
extern void idt_init(void);

/* NOTE: the function declarations below are imported from idt_handle_wrap.S (asm wrappers for respective C functions) */

// Exception handler functions #0 - #19
void _divide_by_zero(void), _reserved(void), _non_maskable_interrupt(void), _breakpoint(void), _overflow(void), _bound_range_exceeded(void),
    _undefined_opcode(void), _no_math_coprocessor(void), _double_fault(void), _coprocessor_overrun(void), _invalid_tss(void), 
    _segment_not_present(void), _stack_segment_fault(void), _general_protection(void), _page_fault(void), _intel_reserved(void),
    _floating_point_error(void), _alignment_check(void), _machine_check(void), _floating_point_except(void);

// Interrupt handler functions #32 - #47
void _pit_intr(void), _keyboard_intr(void), _rtc_intr(void), _mouse_intr(void);
    
// System call function #128
uint32_t _syscall();

#endif /* ASM */

#endif /* IDT_HANDLE_H */
