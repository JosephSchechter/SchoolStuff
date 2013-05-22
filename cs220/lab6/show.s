	.file	"show.c"
	.section	.rodata
.LC0:
	.string	"%s"
	.text
.globl show_string
	.type	show_string, @function
show_string:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	strlen
	leave
	ret
	.size	show_string, .-show_string
	.ident	"GCC: (Debian 4.3.2-1.1) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
