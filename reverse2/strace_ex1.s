	.file	"strace_ex1.c"
	.text
	.section	.rodata
.LC0:
	.string	"Hi there!\n"
	.align 8
.LC1:
	.string	"I'm a cool program that tries to write down a flag.\n"
.LC2:
	.string	"Ok, I'm starting...\n"
.LC3:
	.string	"v3ry_b3utiful_fl4g_yasss"
	.align 8
.LC4:
	.string	"I dunno if it's ok but i tried to.\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$10, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	call	write@PLT
	movl	$52, %edx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	call	write@PLT
	movl	$3, %edi
	call	sleep@PLT
	movl	$20, %edx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	call	write@PLT
	movl	$2, %edi
	call	sleep@PLT
	movl	$24, %edx
	leaq	.LC3(%rip), %rsi
	movl	$1337, %edi
	call	write@PLT
	movl	$35, %edx
	leaq	.LC4(%rip), %rsi
	movl	$1, %edi
	call	write@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
