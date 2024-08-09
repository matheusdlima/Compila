## FIXED INIT
	.section	__TEXT,__cstring,cstring_literals
	printIntStr: .asciz	"%d\n"
	printFloatStr: .asciz	"%f\n"
	printStr: .asciz	"%s\n"
	
	.comm	_v,8,2                          ## @v
	.section	__TEXT,__text,regular,pure_instructions     

## TAC_BEGINFUN                     
	.globl	_main
_main:                                
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_7.7(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_PRINTREAL
	movss	_b(%rip), %xmm0                 ## xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	leaq	printFloatStr(%rip), %rdi
	movb	$1, %al
	callq	_printf
	xorl	%eax, %eax

## TAC_PRINTBOOL
	movb	_b(%rip), %al
	andb	$1, %al
	movzbl	%al, %esi
	leaq	printIntStr(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax
	
## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	L_.str.1(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC_PRINTVETINT
	movl	_v+index(%rip), %esi
	leaq	printIntStr(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC_VET
	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp1@GOTPCREL(%rip), %rcx
	movl	_v+8(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_c@GOTPCREL(%rip), %rcx
	movl	_b(%rip), %edx
	movl	%edx, (%rcx)

## TAC_ADD
	xorl	%eax, %eax
	movq	_a@GOTPCREL(%rip), %rcx
	movl	_c(%rip), %edx
	addl	_b(%rip), %edx
	movl	%edx, (%rcx)

## TAC_ENDFUN
	popq	%rbp
	retq

# DATA SECTION
	.section	__DATA,__data
	.globl	_vec
_a:	.long	76    
_INT888: .long 888
_FLOAT7.7: .float 7.7
_BOOL1: .byte 1

.comm _INTmYWeeirT_emp1,4,2
