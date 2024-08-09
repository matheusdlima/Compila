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
	movl	_c2(%rip), %esi
	movslq	_i(%rip), %rdx
	leaq	_v(%rip), %rcx
	movl	%esi, (%rcx,%rdx,4)
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
	.p2align	2
_b2:
	.long	2                               ## 0x2

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

	.comm	_a,4,2                          ## @a
.subsections_via_symbols
