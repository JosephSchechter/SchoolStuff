	.file	"fp.c"
	.text
.globl assemblypart
	.type	assemblypart, @function
assemblypart:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
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
	movl	%ecx, %eax
	popl	%ebx
	popl	%ebp
	ret
	.size	assemblypart, .-assemblypart
.globl sort
	.type	sort, @function
sort:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	cld
	movl	8(%ebp), %edi
	movl	$0, %eax
	movl	$-1, %ecx
	repnz scasb
	notl	%ecx
	subl	$1, %ecx
	movl	%ecx, -16(%ebp)
	movl	$0, %esi
	movl	$0, %ebx
	movl	%ecx, %eax
	subl	$2, %eax
	movl	%eax, -20(%ebp)
	movl	8(%ebp), %eax
	addl	-20(%ebp), %eax
	movl	%eax, -24(%ebp)
	jmp	.L10
.L5:
	movl	8(%ebp), %eax
	addl	%ebx, %eax
	movl	%eax, (%esp)
	call	assemblypart
	addl	%eax, %esi
	addl	$1, %ebx
.L10:
	movl	-16(%ebp), %eax
	subl	$1, %eax
	cmpl	%eax, %ebx
	jl	.L5
	testl	%esi, %esi
	jle	.L6
	movl	-20(%ebp), %ebx
	testl	%ebx, %ebx
	js	.L6
	movl	-24(%ebp), %edi
	movl	$0, %esi
.L7:
	movl	%edi, (%esp)
	call	assemblypart
	addl	%eax, %esi
	subl	$1, %edi
	subl	$1, %ebx
	jns	.L7
	testl	%esi, %esi
	jle	.L6
	movl	$0, %esi
	movl	$0, %ebx
	jmp	.L10
.L6:
	movl	$0, %eax
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	sort, .-sort
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%c"
.LC1:
	.string	"\nYou put in a newline only."
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC2:
	.string	"The size of the string is %d characters including null and its sorted version is: %s\n"
	.align 4
.LC3:
	.string	"size of the string is %d characters (not including null)\n"
	.section	.rodata.str1.1
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
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$128, (%esp)
	call	malloc
	movl	%eax, %ebx
	leal	-13(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	scanf
	movzbl	-13(%ebp), %edx
	movl	$128, %esi
	cmpb	$10, %dl
	jne	.L19
	movl	$.LC1, (%esp)
	call	puts
	movl	size, %eax
	movb	$10, (%ebx,%eax)
	movl	%ebx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	jmp	.L13
.L19:
	movl	size, %eax
	movb	%dl, (%ebx,%eax)
	addl	$1, %eax
	movl	%eax, size
	leal	-1(%esi), %edx
	cmpl	%edx, %eax
	jne	.L14
	addl	%esi, %esi
	movl	%esi, (%esp)
	call	malloc
	movl	%eax, %ecx
	movl	%eax, %edi
	cmpl	$0, size
	js	.L15
	movl	$0, %edx
.L16:
	movzbl	(%ebx,%edx), %eax
	movb	%al, (%ecx,%edx)
	addl	$1, %edx
	cmpl	%edx, size
	jge	.L16
.L15:
	movl	%ebx, (%esp)
	call	free
	movl	%edi, %ebx
.L14:
	leal	-13(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	scanf
	movzbl	-13(%ebp), %edx
	cmpb	$10, %dl
	jne	.L19
	movl	size, %eax
	movb	$10, 1(%ebx,%eax)
	movl	%eax, 4(%esp)
	movl	$.LC3, (%esp)
	call	printf
	movl	%ebx, 4(%esp)
	movl	$.LC4, (%esp)
	call	printf
	movl	%ebx, (%esp)
	call	sort
	movl	%ebx, 4(%esp)
	movl	$.LC5, (%esp)
	call	printf
.L13:
	movl	$0, size
	movl	%ebx, (%esp)
	call	free
	movl	$0, %eax
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	fp, .-fp
.globl size
	.bss
	.align 4
	.type	size, @object
	.size	size, 4
size:
	.zero	4
	.ident	"GCC: (Debian 4.3.2-1.1) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
