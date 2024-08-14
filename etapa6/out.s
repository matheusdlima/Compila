## FIXED INIT
.section	__TEXT,__cstring,cstring_literals
printIntStr: .asciz	"%d\n"
printFloatStr: .asciz	"%f\n"
readIntStr: .asciz	"%d"
readFloatStr: .asciz	"%f"
printStr: .asciz	"%s\n"
_STRING6048186195195000451:	.asciz	"digite o valor de d: \n"

.section	__TEXT,__text,regular,pure_instructions

## TAC_BEGINFUN
	.globl	_main
_main:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_VEC
	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp0@GOTPCREL(%rip), %rcx
	movl	_INTv+8(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTnumber@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp0(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING6048186195195000451(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC READ
	leaq	readIntStr(%rip), %rdi
	leaq	_INTd(%rip), %rsi
	movl	$0, %eax
	callq	_scanf

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTd(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC NOT
	movl    _BOOLfalse(%rip), %eax
	xorl    $1, %eax
	movl    %eax, _BOOLmYWeeirT_emp1(%rip)

## TAC_COPY
	xorl	%eax, %eax
	movq	_BOOLb@GOTPCREL(%rip), %rcx
	movl	_BOOLmYWeeirT_emp1(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTBOOL
	movb	_BOOLb(%rip), %al
	andb	$1, %al
	movzbl	%al, %esi
	leaq	printIntStr(%rip), %rdi
	movb	$0, %al
	callq	_printf

## TAC_ATTRVEC
	xorl	%eax, %eax
	movl	_INT52(%rip), %esi
	movslq	_INT2(%rip), %rdx
	leaq	_INTv(%rip), %rcx
	movl	%esi, (%rcx,%rdx,4)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTv@GOTPCREL(%rip), %rcx
	movl	_INT2(%rip), %edx
	movl	%edx, (%rcx)

## TAC_VEC
	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp2@GOTPCREL(%rip), %rcx
	movl	_INTv+8(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTmYWeeirT_emp2(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC RETURN
	movl	_INT0(%rip), %eax

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
_BOOLtrue:	.byte   1
_CHAR98:	.long   98
_INT10:	.long   10
_INT100:	.long   100
_INT52:	.long   52
_FLOAT2.5:	.float  2.5
_CHAR120:	.long   120
_CHAR97:	.long   97
_INT199:	.long   199
	.globl _CHARa
_CHARa:	.long	97
	.globl _BOOLb
_BOOLb:	.long    1
	.globl _CHARc
_CHARc:	.long	120
	.globl _INTd
_INTd:	.long	0
	.globl _INTnumber
_INTnumber:	.long	199
	.globl _INTi
_INTi:	.long	1
	.globl	_INTv
_INTv:
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
	.comm	_INTmatrix,400,4
	.globl _FLOATf
_FLOATf:	.float	2.5

	.comm	_INTmYWeeirT_emp0,4,2
	.comm	_BOOLmYWeeirT_emp1,1,0
	.comm	_INTmYWeeirT_emp2,4,2
