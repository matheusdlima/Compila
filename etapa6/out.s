## FIXED INIT
.section	__TEXT,__cstring,cstring_literals
printIntStr: .asciz	"%d\n"
printFloatStr: .asciz	"%f\n"
printStr: .asciz	"%s\n"
_STRING11615476595672465551:	.asciz	"A era=15\n"
_STRING229376933500078:	.asciz	"OK!\n"
_STRING5704575246960342605:	.asciz	"Nao tem como isso...\n"
_STRING229378415316238:	.asciz	"teste"

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

## TAC_DIV	xorl	%eax, %eax
	movl	%eax, -4(%rbp)
	movq	_INTmYWeeirT_emp1@GOTPCREL(%rip), %rcx
	movl	_INT9(%rip), %eax
	cltd
	idivl	_INT2(%rip)
	movl   %eax, %edx
	movl   -4(%rbp), %eax
	movl	%edx, (%rcx)

## TAC_COPY
xorl	%eax, %eax
	movq	_CHARd@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp1(%rip), %edx
	movl	%edx, (%rcx)

## TAC NOT
	movl    _BOOLfalse(%rip), %eax
	xorl    $1, %eax
	movl    %eax, _BOOLmYWeeirT_emp2(%rip)

## TAC_COPY
xorl	%eax, %eax
	movq	_BOOLb@GOTPCREL(%rip), %rcx
	movl	_BOOLmYWeeirT_emp2(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTBOOL
	movb	_BOOLb(%rip), %al
	andb	$1, %al
	movzbl	%al, %esi
	leaq	printIntStr(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING229378415316238(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

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
	movq	_INTmYWeeirT_emp3@GOTPCREL(%rip), %rcx
	movl	_INTv+8(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTmYWeeirT_emp3(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC LABEL
.mYLabe_l0:

## TAC LESS
	movl    _INTi(%rip), %eax
	cmpl    _INT10(%rip), %eax
	setl    %al
	movzbl  %al, %eax
	movl    %eax, _BOOLmYWeeirT_emp4(%rip)

## TAC JFALSE
	movl _BOOLmYWeeirT_emp4(%rip), %eax
	testl %eax, %eax
	jz   .mYLabe_l1

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTi(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_ADD	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp5@GOTPCREL(%rip), %rcx
	movl	_INTi(%rip), %edx
	addl	_INT2(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
xorl	%eax, %eax
	movq	_INTi@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp5(%rip), %edx
	movl	%edx, (%rcx)

## TAC JUMP
	jmp .mYLabe_l0

## TAC LABEL
.mYLabe_l1:

## TAC NOT
	movl    _BOOLb(%rip), %eax
	xorl    $1, %eax
	movl    %eax, _BOOLmYWeeirT_emp6(%rip)

## TAC JFALSE
	movl _BOOLmYWeeirT_emp6(%rip), %eax
	testl %eax, %eax
	jz   .mYLabe_l2

## TAC_ADD	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp7@GOTPCREL(%rip), %rcx
	movl	_CHARa(%rip), %edx
	addl	_INT1(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
xorl	%eax, %eax
	movq	_CHARa@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp7(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING11615476595672465551(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC LABEL
.mYLabe_l2:

## TAC EQ
	movl    _INTi(%rip), %eax
	cmpl    _INT100(%rip), %eax
	sete    %al
	movzbl  %al, %eax
	movl    %eax, _BOOLmYWeeirT_emp8(%rip)

## TAC JFALSE
	movl _BOOLmYWeeirT_emp8(%rip), %eax
	testl %eax, %eax
	jz   .mYLabe_l3

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING5704575246960342605(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC JUMP
	jmp .mYLabe_l4

## TAC LABEL
.mYLabe_l3:

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING229376933500078(%rip), %rsi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax

## TAC LABEL
.mYLabe_l4:

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
	.globl _CHARd
_CHARd:	.long	100
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
	.comm	_INTmYWeeirT_emp1,4,2
	.comm	_BOOLmYWeeirT_emp2,1,0
	.comm	_INTmYWeeirT_emp3,4,2
	.comm	_BOOLmYWeeirT_emp4,1,0
	.comm	_INTmYWeeirT_emp5,4,2
	.comm	_BOOLmYWeeirT_emp6,1,0
	.comm	_INTmYWeeirT_emp7,4,2
	.comm	_BOOLmYWeeirT_emp8,1,0
