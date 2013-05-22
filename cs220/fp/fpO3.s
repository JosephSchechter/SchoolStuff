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
	movl	%edx, -20(%ebp)
	movl	%eax, -16(%ebp)
	movl	%edi, -24(%ebp)
	.p2align 4,,7
	.p2align 3
.L10:
	cmpl	-20(%ebp), %ecx
	jl	.L5
.L12:
	testl	%esi, %esi
	jle	.L6
	movl	-16(%ebp), %eax
	testl	%eax, %eax
	js	.L6
	movl	-24(%ebp), %esi
	xorl	%edi, %edi
	movl	-16(%ebp), %ecx
	.p2align 4,,7
	.p2align 3
.L7:
#APP
# 12 "fp.c" 1
	movl	$0, %edx
	movb	(%esi), %al
	addl	$1, %esi
	movb	(%esi), %bl
	cmpb	%al, %bl
	jle	end
	movb	%al, (%esi)
	addl	$-1, %esi
	movb	%bl, (%esi)
	movl	$1, %edx
	end:
	
# 0 "" 2
#NO_APP
	subl	$1, %esi
	addl	%edx, %edi
	subl	$1, %ecx
	jns	.L7
	testl	%edi, %edi
	jle	.L6
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	cmpl	-20(%ebp), %ecx
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
	pushl	%esi
	movl	$128, %esi
	pushl	%ebx
	subl	$44, %esp
	movl	$128, (%esp)
	leal	-13(%ebp), %edi
	call	malloc
	movl	%edi, 4(%esp)
	movl	$.LC0, (%esp)
	movl	%eax, -40(%ebp)
	call	scanf
	movzbl	-13(%ebp), %edx
	cmpb	$10, %dl
	jne	.L25
	jmp	.L33
	.p2align 4,,7
	.p2align 3
.L16:
	movl	%edi, 4(%esp)
	movl	$.LC0, (%esp)
	call	scanf
	movzbl	-13(%ebp), %edx
	cmpb	$10, %dl
	je	.L31
.L25:
	movl	size, %eax
	movl	-40(%ebp), %ecx
	movb	%dl, (%ecx,%eax)
	movl	size, %eax
	leal	-1(%esi), %edx
	addl	$1, %eax
	cmpl	%edx, %eax
	movl	%eax, size
	jne	.L16
	addl	%esi, %esi
	movl	%esi, (%esp)
	call	malloc
	movl	size, %ecx
	testl	%ecx, %ecx
	movl	%eax, %ebx
	js	.L17
	xorl	%edx, %edx
	.p2align 4,,7
	.p2align 3
.L18:
	movl	-40(%ebp), %ecx
	movzbl	(%ecx,%edx), %eax
	movb	%al, (%ebx,%edx)
	addl	$1, %edx
	cmpl	%edx, size
	jge	.L18
.L17:
	movl	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	movl	%ebx, -40(%ebp)
	jmp	.L16
	.p2align 4,,7
	.p2align 3
.L31:
	movl	-40(%ebp), %edx
	xorl	%esi, %esi
	movl	size, %eax
	movb	$10, 1(%edx,%eax)
	movl	size, %eax
	movl	$.LC3, (%esp)
	movl	%eax, 4(%esp)
	call	printf
	movl	-40(%ebp), %ecx
	movl	$.LC4, (%esp)
	movl	%ecx, 4(%esp)
	call	printf
	movl	-40(%ebp), %edi
	movl	%edi, (%esp)
	call	strlen
	xorl	%ecx, %ecx
	leal	-1(%eax), %edx
	subl	$2, %eax
	addl	%eax, %edi
	movl	%edx, -36(%ebp)
	movl	%eax, -32(%ebp)
	movl	%edi, -44(%ebp)
	.p2align 4,,7
	.p2align 3
.L29:
	cmpl	-36(%ebp), %ecx
	jl	.L21
.L32:
	testl	%esi, %esi
	jle	.L22
	movl	-32(%ebp), %edx
	testl	%edx, %edx
	js	.L22
	movl	-44(%ebp), %esi
	xorl	%edi, %edi
	movl	-32(%ebp), %ecx
	.p2align 4,,7
	.p2align 3
.L23:
#APP
# 12 "fp.c" 1
	movl	$0, %edx
	movb	(%esi), %al
	addl	$1, %esi
	movb	(%esi), %bl
	cmpb	%al, %bl
	jle	end
	movb	%al, (%esi)
	addl	$-1, %esi
	movb	%bl, (%esi)
	movl	$1, %edx
	end:
	
# 0 "" 2
#NO_APP
	subl	$1, %esi
	addl	%edx, %edi
	subl	$1, %ecx
	jns	.L23
	testl	%edi, %edi
	jle	.L22
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	cmpl	-36(%ebp), %ecx
	jge	.L32
.L21:
	movl	-40(%ebp), %edx
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
	jmp	.L29
	.p2align 4,,7
	.p2align 3
.L22:
	movl	-40(%ebp), %eax
	movl	$.LC5, (%esp)
	movl	%eax, 4(%esp)
	call	printf
.L15:
	movl	-40(%ebp), %edx
	movl	$0, size
	movl	%edx, (%esp)
	call	free
	addl	$44, %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L33:
	movl	$.LC1, (%esp)
	call	puts
	movl	-40(%ebp), %edx
	movl	size, %eax
	movb	$10, (%edx,%eax)
	movl	%edx, 8(%esp)
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
