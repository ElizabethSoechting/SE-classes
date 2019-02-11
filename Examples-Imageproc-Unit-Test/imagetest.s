	.file	"imagetest.c"
	.section	.rodata
.LC1:
	.string	"Use: brighten inputfile"
.LC3:
	.string	"brighter%d.ppm"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1843856, %rsp
	movl	%edi, -1843812(%rbp)
	movq	%rsi, -1843824(%rbp)
	movl	$1, -4(%rbp)
	movl	$0, -1843788(%rbp)
	movl	$0, -1843792(%rbp)
	movl	$0, -1843796(%rbp)
	movabsq	$4608308318706860032, %rax
	movq	%rax, -16(%rbp)
	movb	$25, -17(%rbp)
	cmpl	$1, -1843812(%rbp)
	jg	.L2
	movl	$.LC1, %edi
	call	puts
	movl	$-1, %edi
	call	exit
.L2:
	movb	$0, -544(%rbp)
	movq	-1843824(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdi
	leaq	-1843792(%rbp), %r9
	leaq	-1843788(%rbp), %r8
	leaq	-1843784(%rbp), %rcx
	leaq	-544(%rbp), %rdx
	leaq	-1843780(%rbp), %rsi
	leaq	-922176(%rbp), %rax
	movq	%rdi, 8(%rsp)
	leaq	-1843796(%rbp), %rdi
	movq	%rdi, (%rsp)
	movq	%rax, %rdi
	call	readppm
	movabsq	$4607182418800017408, %rax
	movq	%rax, -16(%rbp)
	jmp	.L3
.L6:
	movb	$0, -17(%rbp)
	jmp	.L4
.L5:
	movl	$0, %eax
	call	brighten
	movzbl	-17(%rbp), %eax
	cvtsi2sd	%eax, %xmm0
	movl	-1843796(%rbp), %r8d
	movl	-1843792(%rbp), %ecx
	movl	-1843788(%rbp), %edx
	movq	-16(%rbp), %rax
	leaq	-1843776(%rbp), %rsi
	leaq	-922176(%rbp), %rdi
	movapd	%xmm0, %xmm1
	movq	%rax, -1843832(%rbp)
	movsd	-1843832(%rbp), %xmm0
	call	scaleImage
	movl	-4(%rbp), %edx
	leaq	-576(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf
	movl	-1843784(%rbp), %ecx
	movl	-1843780(%rbp), %esi
	leaq	-576(%rbp), %rdi
	leaq	-544(%rbp), %rdx
	leaq	-1843776(%rbp), %rax
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	writeppm
	addl	$1, -4(%rbp)
	addb	$25, -17(%rbp)
.L4:
	cmpb	$100, -17(%rbp)
	jbe	.L5
	movsd	-16(%rbp), %xmm1
	movsd	.LC2(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
.L3:
	movsd	.LC4(%rip), %xmm0
	ucomisd	-16(%rbp), %xmm0
	jnb	.L6
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC2:
	.long	0
	.long	1072693248
	.align 8
.LC4:
	.long	0
	.long	1074790400
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",@progbits
