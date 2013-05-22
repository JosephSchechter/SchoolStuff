	.file	"fp.c"
	.text
	.p2align 4,,15
.globl assemblypart
	.type	assemblypart, @function
assemblypart:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	pushl	%ebx
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
	.p2align 4,,15
.globl sort
	.type	sort, @function
sort:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	xorl	%esi, %esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	strlen
	movl	8(%ebp), %edi
	xorl	%ecx, %ecx
	leal	-1(%eax), %edx
	subl	$2, %eax
	addl	%eax, %edi
	movl	%edx, -16(%ebp)
	movl	%eax, -20(%ebp)
	movl	%edi, -24(%ebp)
	.p2align 4,,7
	.p2align 3
.L10:
	cmpl	-16(%ebp), %ecx
	jl	.L5
.L12:
	testl	%esi, %esi
	jle	.L6
	movl	-20(%ebp), %esi
	testl	%esi, %esi
	js	.L6
	movl	-24(%ebp), %ecx
	xorl	%edi, %edi
	.p2align 4,,7
	.p2align 3
.L7:
#APP
# 12 "fp.c" 1
	movl	$0, %edx
	movb	(%ecx), %al
	addl	$1, %ecx
	movb	(%ecx), %bl
	cmpb	%al, %bl
	jle	end
	movb	%al, (%ecx)
	addl	$-1, %ecx
	movb	%bl, (%ecx)
	movl	$1, %edx
	end:
	
# 0 "" 2
#NO_APP
	subl	$1, %ecx
	addl	%edx, %edi
	subl	$1, %esi
	jns	.L7
	testl	%edi, %edi
	jle	.L6
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	cmpl	-16(%ebp), %ecx
	jge	.L12
.L5:
	movl	8(%ebp), %edx
	addl	%ecx, %edx
	addl	$1, %ecx
#APP
# 12 "fp.c" 1
	movl	$0, %edi
	movb	(%edx), %al
	addl	$1, %edx
	movb	(%edx), %bl
	cmpb	%al, %bl
	jle	end
	movb	%al, (%edx)
	addl	$-1, %edx
	movb	%bl, (%edx)
	movl	$1, %edi
	end:
	
# 0 "" 2
#NO_APP
	addl	%edi, %esi
	jmp	.L10
	.p2align 4,,7
	.p2align 3
.L6:
	addl	$28, %esp
	xorl	%eax, %eax
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
	.p2align 4,,15
.globl fp
	.type	fp, @function
fp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	$128, %edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	$128, (%esp)
	call	malloc
	movl	$.LC0, (%esp)
	movl	%eax, %ebx
	leal	-13(%ebp), %eax
	movl	%eax, 4(%esp)
	call	scanf
	movzbl	-13(%ebp), %edx
	cmpb	$10, %dl
	jne	.L21
	jmp	.L26
	.p2align 4,,7
	.p2align 3
.L16:
	leal	-13(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	scanf
	movzbl	-13(%ebp), %edx
	cmpb	$10, %dl
	je	.L25
.L21:
	movl	size, %eax
	movb	%dl, (%ebx,%eax)
	movl	size, %eax
	leal	-1(%edi), %edx
	addl	$1, %eax
	cmpl	%edx, %eax
	movl	%eax, size
	jne	.L16
	addl	%edi, %edi
	movl	%edi, (%esp)
	call	malloc
	movl	%eax, %esi
	movl	size, %eax
	testl	%eax, %eax
	js	.L17
	xorl	%edx, %edx
	.p2align 4,,7
	.p2align 3
.L18:
	movzbl	(%ebx,%edx), %eax
	movb	%al, (%esi,%edx)
	addl	$1, %edx
	cmpl	%edx, size
	jge	.L18
.L17:
	movl	%ebx, (%esp)
	movl	%esi, %ebx
	call	free
	jmp	.L16
	.p2align 4,,7
	.p2align 3
.L25:
	movl	size, %eax
	movb	$10, 1(%ebx,%eax)
	movl	size, %eax
	movl	$.LC3, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	movl	%ebx, 4(%esp)
	movl	$.LC4, (%esp)
	call	printf
	movl	%ebx, (%esp)
	call	sort
	movl	%ebx, 4(%esp)
	movl	$.LC5, (%esp)
	call	printf
.L15:
	movl	%ebx, (%esp)
	movl	$0, size
	call	free
	addl	$28, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L26:
	movl	$.LC1, (%esp)
	call	puts
	movl	size, %eax
	movb	$10, (%ebx,%eax)
	movl	%ebx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
	jmp	.L15
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
