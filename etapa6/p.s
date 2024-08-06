## FIXED INIT
	.section	__TEXT,__cstring,cstring_literals
	printIntStr: .asciz	"%d\n"
	printStr: .asciz	"%s\n"
	
	.section	__TEXT,__text,regular,pure_instructions     

## TAC_BEGINFUN                     
	.globl	_main
_main:                                
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_888(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_ENDFUN
	popq	%rbp
	retq

# DATA SECTION
	.section	__DATA,__data
_a:	.long	76    
_888: .long 888
