	.file	"repeat.c"
	.section	.rodata
.LC0:
	.string	"Enter a phrase: "
.LC1:
	.string	"%[^\n\r]"
.LC2:
	.string	"You entered: "
.LC3:
	.string	"\nSize: %d\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%ecx
	subl	$1072, %esp
	cld
	movl	$0, -12(%ebp)
	leal	-1036(%ebp), %eax
	movl	%eax, -1052(%ebp)
	movl	$0, -1056(%ebp)
	movl	$1024, %eax
	cmpl	$4, %eax
	jb	.L2
	movl	$256, -1060(%ebp)
	movl	-1052(%ebp), %edi
	movl	-1060(%ebp), %ecx
	movl	-1056(%ebp), %eax
	rep stosl
.L2:
	movl	$.LC0, (%esp)
	call	printf
	leal	-1036(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	scanf
	movl	$.LC2, (%esp)
	call	printf
	leal	-1036(%ebp), %eax
	movl	%eax, (%esp)
	call	show_string
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC3, (%esp)
	call	printf
	movl	$0, %eax
	addl	$1072, %esp
	popl	%ecx
	popl	%edi
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (Debian 4.3.2-1.1) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
