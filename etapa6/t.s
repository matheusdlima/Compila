	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 12, 0
	.globl	_func                           ## -- Begin function func
	.p2align	4, 0x90
_func:                                  ## @func
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	136(%rbp), %eax
	movl	128(%rbp), %eax
	movl	120(%rbp), %eax
	movl	112(%rbp), %eax
	movl	104(%rbp), %eax
	movl	96(%rbp), %eax
	movl	88(%rbp), %eax
	movl	80(%rbp), %eax
	movl	72(%rbp), %eax
	movl	64(%rbp), %eax
	movl	56(%rbp), %eax
	movl	48(%rbp), %eax
	movl	40(%rbp), %eax
	movl	32(%rbp), %eax
	movl	24(%rbp), %eax
	movl	16(%rbp), %eax
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$168, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movl	_c2(%rip), %edi
	movl	_c2(%rip), %esi
	movl	_c2(%rip), %edx
	movl	_c2(%rip), %ecx
	movl	_c2(%rip), %r8d
	movl	_c2(%rip), %r9d
	movl	_c2(%rip), %eax
	movl	%eax, -76(%rbp)                 ## 4-byte Spill
	movl	_c2(%rip), %eax
	movl	%eax, -72(%rbp)                 ## 4-byte Spill
	movl	_c2(%rip), %eax
	movl	%eax, -68(%rbp)                 ## 4-byte Spill
	movl	_c2(%rip), %eax
	movl	%eax, -64(%rbp)                 ## 4-byte Spill
	movl	_b2(%rip), %eax
	movl	%eax, -60(%rbp)                 ## 4-byte Spill
	movl	_c2(%rip), %eax
	movl	%eax, -56(%rbp)                 ## 4-byte Spill
	movl	_c2(%rip), %eax
	movl	%eax, -52(%rbp)                 ## 4-byte Spill
	movl	_c2(%rip), %eax
	movl	%eax, -48(%rbp)                 ## 4-byte Spill
	movl	_c2(%rip), %r13d
	movl	_c2(%rip), %r12d
	movl	_b2(%rip), %r15d
	movl	_c2(%rip), %r14d
	movl	_c2(%rip), %ebx
	movl	_c2(%rip), %r11d
	movl	_c2(%rip), %r10d
	movl	_c2(%rip), %eax
	movl	%eax, -44(%rbp)                 ## 4-byte Spill
	movl	-76(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, (%rsp)
	movl	-72(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, 8(%rsp)
	movl	-68(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, 16(%rsp)
	movl	-64(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, 24(%rsp)
	movl	-60(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, 32(%rsp)
	movl	-56(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, 40(%rsp)
	movl	-52(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, 48(%rsp)
	movl	-48(%rbp), %eax                 ## 4-byte Reload
	movl	%eax, 56(%rsp)
	movl	-44(%rbp), %eax                 ## 4-byte Reload
	movl	%r13d, 64(%rsp)
	movl	%r12d, 72(%rsp)
	movl	%r15d, 80(%rsp)
	movl	%r14d, 88(%rsp)
	movl	%ebx, 96(%rsp)
	movl	%r11d, 104(%rsp)
	movl	%r10d, 112(%rsp)
	movl	%eax, 120(%rsp)
	callq	_func
	movl	%eax, _b2(%rip)
	movl	_b2(%rip), %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax
	addq	$168, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_b                              ## @b
	.p2align	2
_b:
	.long	0x40000000                      ## float 2

	.globl	_c                              ## @c
	.p2align	2
_c:
	.long	0x40a00000                      ## float 5

	.globl	_b2                             ## @b2
.zerofill __DATA,__common,_b2,4,2
	.globl	_c2                             ## @c2
	.p2align	2
_c2:
	.long	5                               ## 0x5

	.globl	_v                              ## @v
	.p2align	2
_v:
	.long	1                               ## 0x1
	.long	2                               ## 0x2

	.globl	_i                              ## @i
	.p2align	2
_i:
	.long	1                               ## 0x1

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d\n"

	.comm	_a,4,2                          ## @a
	.comm	_ch,1,0                         ## @ch
.subsections_via_symbols
