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
	movl	_i(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_c(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_ENDFUN
	popq	%rbp
	retq

## TAC_BEGINFUN
	.globl	_incn
_incn:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_ENDFUN
	popq	%rbp
	retq

# DATA SECTION
.section	__DATA,__data

_mYWeeirT_emp22:	.long	0
_mYWeeirT_emp26:	.long	0
_a:	.long	0
_b:	.long	0
_c:	.long	0
_d:	.long	0
_f:	.long	0
_i:	.long	0
_mYWeeirT_emp0:	.long	0
_mYWeeirT_emp19:	.long	0
_mYWeeirT_emp14:	.long	0
_mYWeeirT_emp1:	.long	0
_mYWeeirT_emp2:	.long	0
_mYWeeirT_emp23:	.long	0
_mYWeeirT_emp3:	.long	0
_mYWeeirT_emp27:	.long	0
_mYWeeirT_emp15:	.long	0
_mYWeeirT_emp10:	.long	0
_mYWeeirT_emp4:	.long	0
_mYWeeirT_emp5:	.long	0
_mYWeeirT_emp20:	.long	0
_mYWeeirT_emp6:	.long	0
_mYWeeirT_emp24:	.long	0
_mYWeeirT_emp16:	.long	0
_mYWeeirT_emp11:	.long	0
_mYWeeirT_emp7:	.long	0
_number:	.long	0
_mYWeeirT_emp28:	.long	0
_mYWeeirT_emp30:	.long	0
_mYWeeirT_emp8:	.long	0
_mYWeeirT_emp9:	.long	0
_mYWeeirT_emp17:	.long	0
_mYWeeirT_emp21:	.long	0
_mYWeeirT_emp12:	.long	0
_mYWeeirT_emp25:	.long	0
_mYWeeirT_emp29:	.long	0
_mYWeeirT_emp18:	.long	0
_mYWeeirT_emp31:	.long	0
_mYWeeirT_emp13:	.long	0
