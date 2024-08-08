	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 12, 0
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
	xorl	%eax, %eax
	movq	_b@GOTPCREL(%rip), %rcx
	movl	_vec+8(%rip), %edx
	movl	%edx, (%rcx)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__DATA,__data
	.globl	_vec                            ## @vec
	.p2align	4
_vec:
	.long	1                               ## 0x1
	.long	2                               ## 0x2
	.long	3                               ## 0x3
	.long	4                               ## 0x4
	.long	5                               ## 0x5

	.comm	_b,4,2                          ## @b
	.comm	_c,4,2                          ## @c
	.comm	_d,1,0                          ## @d
	.comm	_f,1,0                          ## @f
.subsections_via_symbols
