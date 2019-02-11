	.file	"brightc.c"
	.comm	pix,4,4
	.comm	i,4,4
	.comm	j,4,4
	.comm	k,4,4
	.globl	row
	.data
	.align 4
	.type	row, @object
	.size	row, 4
row:
	.long	480
	.globl	col
	.align 4
	.type	col, @object
	.size	col, 4
col:
	.long	640
	.globl	chan
	.align 4
	.type	chan, @object
	.size	chan, 4
chan:
	.long	3
	.comm	img,921600,32
	.comm	newimg,921600,32
	.globl	alpha
	.align 8
	.type	alpha, @object
	.size	alpha, 8
alpha:
	.long	0
	.long	1072955392
	.globl	beta
	.type	beta, @object
	.size	beta, 1
beta:
	.byte	25
	.text
	.globl	brighten
	.type	brighten, @function
brighten:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, i(%rip)
	jmp	.L2
.L9:
	movl	$0, j(%rip)
	jmp	.L3
.L8:
	movl	$0, k(%rip)
	jmp	.L4
.L7:
	movl	i(%rip), %edx
	movl	col(%rip), %eax
	imull	%eax, %edx
	movl	j(%rip), %eax
	addl	%eax, %edx
	movl	chan(%rip), %eax
	imull	%eax, %edx
	movl	k(%rip), %eax
	leal	(%rdx,%rax), %ecx
	movl	i(%rip), %edx
	movl	col(%rip), %eax
	imull	%eax, %edx
	movl	j(%rip), %eax
	addl	%eax, %edx
	movl	chan(%rip), %eax
	imull	%eax, %edx
	movl	k(%rip), %eax
	addl	%edx, %eax
	cltq
	movzbl	img(%rax), %eax
	movzbl	%al, %eax
	cvtsi2sd	%eax, %xmm0
	movsd	alpha(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	cvttsd2siq	%xmm0, %rax
	movl	%eax, %edx
	movzbl	beta(%rip), %eax
	movzbl	%al, %eax
	addl	%edx, %eax
	movl	%eax, pix(%rip)
	movl	pix(%rip), %eax
	cmpl	$255, %eax
	jg	.L5
	movl	pix(%rip), %eax
	jmp	.L6
.L5:
	movl	$-1, %eax
.L6:
	movslq	%ecx, %rdx
	movb	%al, newimg(%rdx)
	movl	k(%rip), %eax
	addl	$1, %eax
	movl	%eax, k(%rip)
.L4:
	movl	k(%rip), %edx
	movl	chan(%rip), %eax
	cmpl	%eax, %edx
	jl	.L7
	movl	j(%rip), %eax
	addl	$1, %eax
	movl	%eax, j(%rip)
.L3:
	movl	j(%rip), %edx
	movl	col(%rip), %eax
	cmpl	%eax, %edx
	jl	.L8
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
.L2:
	movl	i(%rip), %edx
	movl	row(%rip), %eax
	cmpl	%eax, %edx
	jl	.L9
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	brighten, .-brighten
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-28)"
	.section	.note.GNU-stack,"",@progbits
