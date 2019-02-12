	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_thread_func_one        ## -- Begin function thread_func_one
	.p2align	4, 0x90
_thread_func_one:                       ## @thread_func_one
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	pushq	%rax
	.cfi_offset %rbx, -24
	cmpb	$0, _stop(%rip)
	jne	LBB0_3
## %bb.1:
	leaq	L_str.3(%rip), %rbx
	.p2align	4, 0x90
LBB0_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	$1, %edi
	xorl	%eax, %eax
	callq	_sleep
	movq	%rbx, %rdi
	callq	_puts
	cmpb	$0, _stop(%rip)
	je	LBB0_2
LBB0_3:
	leaq	L_str(%rip), %rdi
	callq	_puts
	xorl	%eax, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_thread_func_two        ## -- Begin function thread_func_two
	.p2align	4, 0x90
_thread_func_two:                       ## @thread_func_two
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movb	$1, _stop(%rip)
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset %rbx, -24
	leaq	_thread_func_one(%rip), %rdx
	leaq	-24(%rbp), %rdi
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	callq	_pthread_create
	testl	%eax, %eax
	jne	LBB2_1
## %bb.2:
	leaq	_thread_func_two(%rip), %rdx
	xorl	%ebx, %ebx
	leaq	-16(%rbp), %rdi
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	callq	_pthread_create
	testl	%eax, %eax
	je	LBB2_3
LBB2_1:
	leaq	L_str.5(%rip), %rdi
	callq	_puts
	movl	$-1, %ebx
LBB2_4:
	movl	%ebx, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	retq
LBB2_3:
	movq	-24(%rbp), %rdi
	xorl	%esi, %esi
	callq	_pthread_join
	movq	-16(%rbp), %rdi
	xorl	%esi, %esi
	callq	_pthread_join
	jmp	LBB2_4
	.cfi_endproc
                                        ## -- End function
	.globl	_stop                   ## @stop
.zerofill __DATA,__common,_stop,1,0
	.section	__TEXT,__cstring,cstring_literals
	.p2align	4               ## @str
L_str:
	.asciz	"thread one sleep end"

	.p2align	4               ## @str.3
L_str.3:
	.asciz	"thread one sleeping"

	.p2align	4               ## @str.5
L_str.5:
	.asciz	"pthread create failed!"


.subsections_via_symbols
