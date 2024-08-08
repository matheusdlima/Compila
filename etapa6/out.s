## FIXED INIT
.section	__TEXT,__cstring,cstring_literals
printIntStr: .asciz	"%d\n"
printFloatStr: .asciz	"%f\n"
printStr: .asciz	"%s\n"
_STRINGteste:	.asciz	"teste"
.section	__TEXT,__text,regular,pure_instructions

## TAC_BEGINFUN
	.globl	_main
_main:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_VET	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp1@GOTPCREL(%rip), %rcx
	movl	_v+8(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRINGteste(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC_VET	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp5@GOTPCREL(%rip), %rcx
	movl	_v+36(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTmYWeeirT_emp5(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_PRINTREAL
	movss	_FLOATf(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	leaq	printFloatStr(%rip), %rdi
	movb	$1, %al
	callq	_printf
	xorl	%eax, %eax

## TAC_PRINTCHAR
	leaq	printIntStr(%rip), %rdi
	movl	_CHAR71(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_PRINTBOOL
	movb	_BOOLtrue(%rip), %al
	andb	$1, %al
	movzbl	%al, %esi
	leaq	printIntStr(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC_PRINTBOOL
	movb	_BOOLfalse(%rip), %al
	andb	$1, %al
	movzbl	%al, %esi
	leaq	printIntStr(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

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

_BOOLfalse:	.byte   0
_INT0:	.long   0
_INT1:	.long   1
_INT2:	.long   2
_INT3:	.long   3
_INT4:	.long   4
_INT5:	.long   5
_INT6:	.long   6
_INT7:	.long   7
_INT8:	.long   8
_INT9:	.long   9
_CHAR71:	.long   71
_BOOLtrue:	.byte   1
_CHAR98:	.long   98
_INT10:	.long   10
_FLOAT5.:	.float  5.
_INT100:	.long   100
_FLOAT9.:	.float  9.
_FLOAT2.5:	.float  2.5
_CHAR120:	.long   120
_CHAR97:	.long   97
_INT55:	.long   55
_INT199:	.long   199
_CHARa:	.long	97
_TRUEb:	.long	1
_CHARc:	.long	120
_CHARd:	.long	100
_INTnumber:	.long	199
_INTi:	.long	1
	.globl	_v
_v:
	.long	'a'
	.long	1
	.long	'b'
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	8
_FLOATf:	.float	2.5

	.comm	_INTmYWeeirT_emp0,4,2
	.comm	_INTmYWeeirT_emp14,4,2
	.comm	_INTmYWeeirT_emp1,4,2
	.comm	_INTmYWeeirT_emp2,4,2
	.comm	_INTmYWeeirT_emp3,4,2
	.comm	_FALSEmYWeeirT_emp15,1,0
	.comm	_FALSEmYWeeirT_emp10,1,0
	.comm	_INTmYWeeirT_emp4,4,2
	.comm	_INTmYWeeirT_emp5,4,2
	.comm	_INTmYWeeirT_emp6,4,2
	.comm	_INTmYWeeirT_emp16,4,2
	.comm	_INTmYWeeirT_emp11,4,2
	.comm	_INTmYWeeirT_emp7,4,2
	.comm	_FLOATmYWeeirT_emp8,4,2
	.comm	_FLOATmYWeeirT_emp9,4,2
	.comm	_INTmYWeeirT_emp12,4,2
	.comm	_FALSEmYWeeirT_emp13,1,0
