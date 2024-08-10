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

## TAC CALL
	movl	_INTi(%rip), %edi
	movl	_INTi(%rip), %esi
	movl	_INTi(%rip), %edx
	movl	_INTi(%rip), %ecx
	movl	_INTi(%rip), %r8d
	movl	_INTi(%rip), %r9d
	movl	_INTi(%rip), %r13d
	movl	_INTi(%rip), %r12d
	movl	_INTi(%rip), %r15d
	movl	_INTi(%rip), %r14d
	movl	_INTi(%rip), %ebx
	movl	_INTi(%rip), %r11d
	movl	_INTi(%rip), %r10d
	movl	_INTi(%rip), %eax
	movl	_INTi(%rip), %eax
	movl	%eax, -76(%rbp)		## 4-byte Spill
	movl	_INTi(%rip), %eax
	movl	%eax, -72(%rbp)		## 4-byte Spill
	movl	_INTi(%rip), %eax
	movl	%eax, -68(%rbp)		## 4-byte Spill
	movl	_INTi(%rip), %eax
	movl	%eax, -64(%rbp)		## 4-byte Spill
	movl	_INTi(%rip), %eax
	movl	%eax, -60(%rbp)		## 4-byte Spill
	movl	_INT9(%rip), %eax
	movl	%eax, -56(%rbp)		## 4-byte Spill
	movl	_INT8(%rip), %eax
	movl	%eax, -52(%rbp)		## 4-byte Spill
	movl	-76(%rbp), %eax		## 4-byte Reload
	movl	%eax, 0(%rsp)
	movl	-72(%rbp), %eax		## 4-byte Reload
	movl	%eax, 8(%rsp)
	movl	-68(%rbp), %eax		## 4-byte Reload
	movl	%eax, 16(%rsp)
	movl	-64(%rbp), %eax		## 4-byte Reload
	movl	%eax, 24(%rsp)
	movl	-60(%rbp), %eax		## 4-byte Reload
	movl	%eax, 32(%rsp)
	movl	-56(%rbp), %eax		## 4-byte Reload
	movl	%eax, 40(%rsp)
	movl	-52(%rbp), %eax		## 4-byte Reload
	movl	%eax, 48(%rsp)
	movl	%edi, 0(%rsp)
	movl	%esi, 8(%rsp)
	movl	%edx, 16(%rsp)
	movl	%ecx, 24(%rsp)
	movl	%r8d, 32(%rsp)
	movl	%r9d, 40(%rsp)
	movl	%r13d, 48(%rsp)
	movl	%r12d, 56(%rsp)
	movl	%r15d, 64(%rsp)
	movl	%r14d, 72(%rsp)
	movl	%ebx, 80(%rsp)
	movl	%r11d, 88(%rsp)
	movl	%r10d, 96(%rsp)
	movl	%eax, 104(%rsp)
	call	_incn

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTnumber@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp0(%rip), %edx
	movl	%edx, (%rcx)

## TAC_VEC
	xorl	%eax, %eax
	movq	_INTmYWeeirT_emp1@GOTPCREL(%rip), %rcx
	movl	_INTv+8(%rip), %edx
	movl	%edx, (%rcx)

## TAC_COPY
	xorl	%eax, %eax
	movq	_INTnumber@GOTPCREL(%rip), %rcx
	movl	_INTmYWeeirT_emp1(%rip), %edx
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
	.comm	_INTmYWeeirT_emp1,4,2
	.comm	_BOOLmYWeeirT_emp2,1,0
	.comm	_INTmYWeeirT_emp3,4,2
