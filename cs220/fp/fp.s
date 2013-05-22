	.file	"fp.c"
.globl size
	.bss
	.align 4
	.type	size, @object
	.size	size, 4
size:
	.zero	4
	.text
.globl assemblypart
	.type	assemblypart, @function
assemblypart:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
	movl	$0, -8(%ebp)
	movl	8(%ebp), %edx
#APP
# 12 "fp.c" 1
	movl	$0, %ecx
	movb	(%edx), %al
	addl	$1, %edx
	movb	(%edx), %bl
	cmpb	%al, %bl
	jle	end
	movb	%al, (%edx)
	addl	$-1, %edx
	movb	%bl, (%edx)
	movl	$1, %ecx
	end:
	
# 0 "" 2
#NO_APP
	movl	%ecx, %edx
	movl	%edx, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	$16, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	assemblypart, .-assemblypart
.globl sort
	.type	sort, @function
sort:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	strlen
	movl	%eax, -12(%ebp)
	movl	$0, -8(%ebp)
.L9:
	movl	$0, -8(%ebp)
	movl	$0, -4(%ebp)
	jmp	.L4
.L5:
	movl	-4(%ebp), %eax
	addl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	assemblypart
	addl	%eax, -8(%ebp)
	addl	$1, -4(%ebp)
.L4:
	movl	-12(%ebp), %eax
	subl	$1, %eax
	cmpl	-4(%ebp), %eax
	jg	.L5
	cmpl	$0, -8(%ebp)
	jle	.L6
	movl	$0, -8(%ebp)
	movl	-12(%ebp), %eax
	subl	$2, %eax
	movl	%eax, -4(%ebp)
	jmp	.L7
.L8:
	movl	-4(%ebp), %eax
	addl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	assemblypart
	addl	%eax, -8(%ebp)
	subl	$1, -4(%ebp)
.L7:
	cmpl	$0, -4(%ebp)
	jns	.L8
.L6:
	cmpl	$0, -8(%ebp)
	jg	.L9
	movl	$0, %eax
	leave
	ret
	.size	sort, .-sort
	.section	.rodata
.LC0:
	.string	"%c"
.LC1:
	.string	"\nYou put in a newline only."
	.align 4
.LC2:
	.string	"The size of the string is %d characters including null and its sorted version is: %s\n"
	.align 4
.LC3:
	.string	"size of the string is %d characters (not including null)\n"
.LC4:
	.string	"the string is: %s\n"
.LC5:
	.string	"\n\nThe sorted string is: %s\n"
	.text
.globl fp
	.type	fp, @function
fp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	$128, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -12(%ebp)
	leal	-17(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	scanf
	movzbl	-17(%ebp), %eax
	cmpb	$10, %al
	jne	.L14
	movl	$.LC1, (%esp)
	call	puts
	movl	size, %eax
	addl	-12(%ebp), %eax
	movb	$10, (%eax)
	movl	size, %edx
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	jmp	.L13
.L18:
	movl	size, %eax
	movl	%eax, %edx
	addl	-12(%ebp), %edx
	movzbl	-17(%ebp), %eax
	movb	%al, (%edx)
	movl	size, %eax
	addl	$1, %eax
	movl	%eax, size
	movl	-16(%ebp), %eax
	leal	-1(%eax), %edx
	movl	size, %eax
	cmpl	%eax, %edx
	jne	.L15
	sall	-16(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -4(%ebp)
	movl	$0, -8(%ebp)
	jmp	.L16
.L17:
	movl	-8(%ebp), %eax
	movl	%eax, %edx
	addl	-4(%ebp), %edx
	movl	-8(%ebp), %eax
	addl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	movb	%al, (%edx)
	addl	$1, -8(%ebp)
.L16:
	movl	size, %eax
	cmpl	%eax, -8(%ebp)
	jle	.L17
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
.L15:
	leal	-17(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	scanf
.L14:
	movzbl	-17(%ebp), %eax
	cmpb	$10, %al
	jne	.L18
	movl	size, %eax
	addl	$1, %eax
	addl	-12(%ebp), %eax
	movb	$10, (%eax)
	movl	size, %eax
	movl	%eax, 4(%esp)
	movl	$.LC3, (%esp)
	call	printf
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC4, (%esp)
	call	printf
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	sort
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC5, (%esp)
	call	printf
.L13:
	movl	$0, size
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	movl	$0, %eax
	leave
	ret
	.size	fp, .-fp
	.ident	"GCC: (Debian 4.3.2-1.1) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
