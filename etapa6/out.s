## FIXED INIT
.section	__TEXT,__cstring,cstring_literals
printIntStr: .asciz	"%d\n"
printFloatStr: .asciz	"%f\n"
readIntStr: .asciz	"%d"
readFloatStr: .asciz	"%f"
printStr: .asciz	"%s"
_STRING16041765196113750995:	.asciz	"b = ~b ->  "
_STRING12328719795569653691:	.asciz	"d = d - 5 ->  "
_STRING6048186195195000451:	.asciz	"digite o valor de d: \n"
_STRING11676679939604644714:	.asciz	"i = 0 ->  "
_STRING9790939547036807759:	.asciz	"i = a + i  ->  "
_STRING5937925058351471584:	.asciz	"number = v[8] -> "
_STRING10042128117035228350:	.asciz	"f = 5.5 / 2. ->  "
_STRING14929583638074647166:	.asciz	"retornou da função\n"
_STRING6950845483759:	.asciz	"i = "
_STRING9560460703016506023:	.asciz	"entrou na função\n"
_STRING10688820508414138744:	.asciz	"f = 2.0 * 9. ->  "

.section	__TEXT,__text,regular,pure_instructions

## TAC_BEGINFUN
	.globl	_main
_main:
	pushq	%rbp
	movq	%rsp, %rbp

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

## TAC_ADD	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp0@GOTPCREL(%rip), %rcx
	movl	_CHARa(%rip), %edx
	addl	_INTi(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTi@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp0(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING9790939547036807759(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTi(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_SUB	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp1@GOTPCREL(%rip), %rcx
	movl	_INTd(%rip), %edx
	subl	_INT5(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTd@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp1(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING12328719795569653691(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTd(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_MUL	xorl	%eax, %eax
	movq	_FLOATmYWeeirT_emp2@GOTPCREL(%rip), %rdx
	movss	_FLOAT2.0(%rip), %xmm0
	mulss	_FLOAT9.(%rip), %xmm0
	movss	%xmm0, (%rdx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_FLOATf@GOTPCREL(%rip), %rcx
	movl	_FLOATmYWeeirT_emp2(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING10688820508414138744(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTREAL
	movss	_FLOATf(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	leaq	printFloatStr(%rip), %rdi
	movb	$1, %al
	callq	_printf

## TAC_DIV	xorl	%eax, %eax
	movq	_FLOATmYWeeirT_emp3@GOTPCREL(%rip), %rcx
	movss	_FLOAT5.5(%rip), %xmm0
	divss	_FLOAT2.(%rip), %xmm0
	movss	%xmm0, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_FLOATf@GOTPCREL(%rip), %rcx
	movl	_FLOATmYWeeirT_emp3(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING10042128117035228350(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTREAL
	movss	_FLOATf(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	leaq	printFloatStr(%rip), %rdi
	movb	$1, %al
	callq	_printf

## TAC NOT
	movl    _BOOLb(%rip), %eax
	xorl    $1, %eax
	movl    %eax, _BOOLmYWeeirT_emp4(%rip)

## TAC_COPY
	xorl	%eax, %eax
	movq	_BOOLb@GOTPCREL(%rip), %rcx
	movl	_BOOLmYWeeirT_emp4(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING16041765196113750995(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTBOOL
	movb	_BOOLb(%rip), %al
	andb	$1, %al
	movzbl	%al, %esi
	leaq	printIntStr(%rip), %rdi
	movb	$0, %al
	callq	_printf

## TAC OR
	movl    $0, %eax
	testl   %eax, %eax
	jnz     .Ltrue1
	movl    $1, %eax
	jmp     .Lend1
.Ltrue1:
	movl    $1, %eax
.Lend1:
	movl    %eax, _BOOLmYWeeirT_emp5(%rip)

## TAC_COPY
	xorl	%eax, %eax
	movq	_BOOLcondicao@GOTPCREL(%rip), %rcx
	movl	_BOOLmYWeeirT_emp5(%rip), %edx
	movl	%edx, (%rcx)

## TAC JFALSE
	movl _BOOLcondicao(%rip), %eax
	testl %eax, %eax
	jz   .mYLabe_l2

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTi@GOTPCREL(%rip), %rcx
	movl	_INT0(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING11676679939604644714(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTi(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC LABEL
.mYLabe_l0:

## TAC LESS
	movl    _INTi(%rip), %eax
	cmpl    _INT10(%rip), %eax
	setl    %al
	movzbl  %al, %eax
	movl    %eax, _BOOLmYWeeirT_emp6(%rip)

## TAC JFALSE
	movl _BOOLmYWeeirT_emp6(%rip), %eax
	testl %eax, %eax
	jz   .mYLabe_l1

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING6950845483759(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTi(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC_ADD	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp7@GOTPCREL(%rip), %rcx
	movl	_INTi(%rip), %edx
	addl	_INT1(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTi@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp7(%rip), %edx
	movl	%edx, (%rcx)

## TAC JUMP
	jmp .mYLabe_l0

## TAC LABEL
.mYLabe_l1:

## TAC_VEC
	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp8@GOTPCREL(%rip), %rcx
	movl	_INTv+32(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTnumber@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp8(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING5937925058351471584(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_PRINTINT
	leaq	printIntStr(%rip), %rdi
	movl	_INTnumber(%rip), %esi
	movb	$0, %al
	callq	_printf

## TAC LABEL
.mYLabe_l2:

## TAC CALL
	subq	$24, %rsp
	movl	_INT4(%rip), %edi
	movl	_INT3(%rip), %esi
	movl	_INT2(%rip), %edx
	movl	_INTi(%rip), %ecx
	call	_func
	movl	%eax, _INTmYWeeirT_emp9(%rip)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTnumber@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp9(%rip), %edx
	movl	%edx, (%rcx)

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING14929583638074647166(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC RETURN
	movl	_INT0(%rip), %eax

## TAC_ENDFUN
	addq	$24, %rsp
	popq	%rbp
	retq

## TAC_BEGINFUN
	.globl	_func
_func:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_PRINTSTR
	leaq	printStr(%rip), %rdi
	leaq	_STRING9560460703016506023(%rip), %rsi
	movb	$0, %al
	callq	_printf

## TAC_ENDFUN
	popq	%rbp
	retq

# DATA SECTION
	.section	__DATA,__data

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
_FLOAT5.5:	.float  5.5
_FLOAT2.:	.float  2.
_BOOLtrue:	.byte   1
_CHAR98:	.long   98
_INT10:	.long   10
_INT100:	.long   100
_FLOAT9.:	.float  9.
_FLOAT2.5:	.float  2.5
_CHAR120:	.long   120
_CHAR97:	.long   97
_FLOAT2.0:	.float  2.0
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
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	8
	.long	9
	.comm	_INTmatrix,400,4
	.globl _FLOATf
_FLOATf:	.float	2.5
	.globl _BOOLcondicao
_BOOLcondicao:	.long    1

	.comm	_INTmYWeeirT_emp0,4,2
	.comm	_INTmYWeeirT_emp1,4,2
	.comm	_FLOATmYWeeirT_emp2,4,2
	.comm	_FLOATmYWeeirT_emp3,4,2
	.comm	_BOOLmYWeeirT_emp4,1,0
	.comm	_BOOLmYWeeirT_emp5,1,0
	.comm	_BOOLmYWeeirT_emp6,1,0
	.comm	_INTmYWeeirT_emp7,4,2
	.comm	_INTmYWeeirT_emp8,4,2
	.comm	_INTmYWeeirT_emp9,4,2
