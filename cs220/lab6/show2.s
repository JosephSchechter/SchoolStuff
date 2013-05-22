#	Lab6 show2.s by Joseph Schechter
	.section	.rodata

read2:
	.string	"%c"


.globl show_string
	.type	show_string, @function
show_string:
	pushl	%ebp
	movl	%esp, %ebp
	
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%edi
	pushl	%esi
	pushfl
	
	movl	$0, %eax		#eax is the string counter and what is returned
	movl    8(%ebp), %ebx	#ebx has the string location
	
compare2:
	movb	(%ebx), %cl
	cmpb	$0, %cl			#is it a null
	je	out2
	
	pushl	%ebx
	pushl	%eax
	
	pushl	%ecx
	pushl	$read2
	call	printf
	addl	$8, %esp
	
	popl	%eax
	popl	%ebx
	
	addl	$1, %ebx		#next character
	addl	$1, %eax		#increase counter
	jmp		compare2

	
out2:
	popfl
	popl	%esi
	popl	%edi
	popl	%edx
	popl	%ecx
	popl	%ebx
	
	leave
	ret
	.size	show_string, .-show_string
	.ident	"GCC: (Debian 4.3.2-1.1) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
