/*
 * Sets up the IDT, filling the table with the respective handling functions
 */

#include "idt_handle.h"

// Function pointer array for all 20 default exception handlers (wrapper)
void (*except_ptr[20]) = {
    _divide_by_zero, _reserved, _non_maskable_interrupt, _breakpoint, _overflow,
    _bound_range_exceeded, _undefined_opcode, _no_math_coprocessor, _double_fault, _coprocessor_overrun,
    _invalid_tss, _segment_not_present, _stack_segment_fault, _general_protection, _page_fault,
    _intel_reserved, _floating_point_error, _alignment_check, _machine_check, _floating_point_except
};

// Function pointer array for all 16 PIC interrupt lines handlers (wrapper)
void (*intr_ptr[16]) = {
    0, _keyboard_intr, 0, 0, 0, 0, 0, 0,        // master PIC ([2] is slave, is not used)
	_rtc_intr, 0, 0, 0, _mouse_intr, 0, 0, 0    // slave PIC
};

/*
 * void idt_init(void);
 *   Inputs: void
 *   Return Value: none
 *   Function: Puts the exceptions, interrupts, and system call
 *              vectors inside the IDT, with their associated wrappers
 */
void idt_init(){
    idt_desc_t idt_entry, empty_entry;
    empty_entry.present = 0;
    int i;
    
    // Fill in idt table entries #0 - #19 as non-interruptible gates
    SET_INTR_GATE(idt_entry);
    
    for(i = 0; i < USED_EXCEPTIONS; i++) {
        SET_IDT_ENTRY(idt_entry, except_ptr[i]);
        idt[i] = idt_entry;
    }
    
    /* entries #20 - #31 are empty : intel reserved
       entries #32 - #255 are user-defined : devices will request them as needed */
    for(i = USED_EXCEPTIONS; i < NUM_VEC; i++)
        idt[i] = empty_entry;

	// Fill in idt table below this code as interruptible gates
    SET_TRAP_GATE(idt_entry);
	
	// defining entries #32 - #47 map to master & slave PICs interrupts
	for(i = 0; i < PIC_INTRS; i++)
        if(intr_ptr[i]) {
			//	fill in VALID (only) intr handlers from PIC lines starting at IDT index #32 / 0x20
			SET_IDT_ENTRY(idt_entry, intr_ptr[i]);
			idt[i + 32] = idt_entry;
		}
    
    // Fill in idt table entry #128 / 0x80 with system call handler (as trap)
    idt_entry.dpl = 3;              //system calls are avail to user programs at DPL 3
    SET_IDT_ENTRY(idt_entry, _syscall);
    idt[128] = idt_entry;
    
    // Load the interrupt table
    lidt(idt_desc_ptr);
}

#define RETURN_256 do{\
    asm volatile(\
        "movl 0x100, %%eax"\
        :\
        :\
        :"%eax"\
    );\
}while(0)

/* ========== Exception Handlers ========== */

/*	DESCRIPTION: exception invoked for IDT vector 0x00
	INPUT:	none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void div_zero_fault() {
    printf("Divide-by-zero fault occurred. Do you even math?\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x01
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void reserved_fault() {
    printf("RESERVED. You got an exception for intel used only...\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x02
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void nmi_intr() {
    printf("Non-maskable interrupt triggered. Hardware wants attention bad.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x03
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void breakpoint_trap() {
    printf("Breakpoint thrown. How long is this going to take?\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x04
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void overflow_trap() {
    printf("Overflow detected. It's too big.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x05
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void bound_range_fault() {
    printf("Bounds exceeded. Try a tigher fit.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x06
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void invalid_opcode_fault() {
    printf("Invalid opcode used. This is x86, bruh...\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x07
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void device_na_fault() {
    printf("Device not available fault. You gonna wait today.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x08
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void double_fault_abort() {
    printf("Double fault, abort! RIP, GG.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x09
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void seg_overrun_fault() {
    printf("Coprocessor Segment Overrun (reserved). Really shouldn't be getting this...\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x0A
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void tss_fault() {
    printf("Invalid task state segment. No context switching for you, ha.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x0B
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void seg_np_fault() {
    printf("Segment not present. Is your brain segment present?\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x0C
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void ss_fault() {
    printf("Stack segment fault. Have fun debugging.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x0D
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void gen_pro_fault() {
    printf("General protection fault. You're violating me.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x0E
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void page_fault() {
    uint32_t cr2;

    // Get the error stored in cr2
    asm volatile (
        "movl %%cr2, %%eax;"
        "movl %%eax, %0;"
        : "=m"(cr2)
        :
        : "%eax"
    );

    printf("Page fault encountered with error %x\n", cr2);
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x0F
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void dne_entry() {
    printf("Intel reserved. Why are you even getting this?!\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x10
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void fpu_math_fault() {
    printf("x87 FPU Floating-Point Error. No one actually knows...\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x11
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void align_fault() {
    printf("Alignment check faulted. Guess your brain also needs re-alignment.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x12
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void machine_chk_abort() {
    printf("Machine check failed, abort! Another RIP, GG.\n");
    RETURN_256;
    return;
}

/*	DESCRIPTION: exception invoked for IDT vector 0x13
	INPUT: none
	OUTPUT: none
	EFFECTS: prints offending error msg, stalls system indefinitely
*/
void simd_fpe_fault() {
    printf("Floating point exception. IDEK, but GL.\n");
    RETURN_256;
    return;
}
