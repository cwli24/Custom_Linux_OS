#define ASM     1

.text

.globl _idt_handler_table

_divide_by_zero:
    call	div_zero_fault
    iret

_reserved:
    call	reserved_fault
    iret

_non_maskable_interrupt:
    call	nmi_intr
    iret

_breakpoint:
    call	breakpoint_trap
    iret

_overflow:
	call	overflow_trap
	iret
	
_bound_range_exceeded:
	call	bound_range_fault
	iret
	
_undefined_opcode:
	call	invalid_opcode_fault
	iret
	
_no_math_coprocessor:
	call	device_na_fault
	iret
	
_double_fault:
	call	double_fault_abort
	iret
	
_coprocessor_overrun:
	call	seg_overrun_fault
	iret
	
_invalid_tss:
	call	tss_fault
	iret
	
_segment_not_present:
	call	seg_np_fault
	iret

_stack_segment_fault:
	call	ss_fault
	iret
	
_general_protection:
	call	gen_pro_fault
	iret

_page_fault:
	call	page_fault
	iret
	
_intel_reserved:
	call	dne_entry
	iret
	
_floating_point_error:
	call	fpu_math_fault
	iret
	
_alignment_check:
	call	align_fault
	iret
	
_machine_check:
	call	machine_chk_abort
	iret
	
_floating_point_except:
	call	simd_fpe_fault
	

_idt_handler_table:
    .long	_divide_by_zero, _debug_exception, _non_maskable_interrupt, _breakpoint, _overflow,					# vector 0x00-0x04
		_bound_range_exceeded, _undefined_opcode, _no_math_coprocessor, _double_fault, _coprocessor_overrun,	# 0x05 - 0x09
		_invalid_tss, _segment_not_present, _stack_segment_fault, _general_protection, _page_fault				# 0x0A - 0x0E
		_intel_reserved, _floating_point_error, _alignment_check, _machine_check, _floating_point_except		# 0x0F - 0x13