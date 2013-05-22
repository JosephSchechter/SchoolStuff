#	Lab6 show4.s by Joseph Schechter
	.section	.rodata

read4:
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
	
compare4:
	movb	(%ebx), %cl
	cmpb	$0, %cl			#is it a null
	je	out4
	
	cmpb	$65, %cl		#is it before the letters begin (A)
	jb	notletter4
	cmpb	$122, %cl		#is it after the letters end (z)
	ja	notletter4			
	cmpb	$90, %cl		#is it a capital letter (65-90)
	jbe	converttolowercase
	cmpb	$97, %cl		#is it lowercases (97-122)
	jae	converttouppercase
	jmp	notletter4
	
converttolowercase:
	addb	$32, %cl
	jmp	doneconversion
	
converttouppercase:
	addb	$-32, %cl
	jmp	doneconversion


doneconversion:
notletter4:
	addl	$1, %eax		#increase counter
	pushl	%ebx
	pushl	%eax
	
	pushl	%ecx
	pushl	$read4
	call	printf
	addl	$8, %esp
	
	popl	%eax
	popl	%ebx
	
	
	addl	$1, %ebx		#next character
	jmp		compare4

	
out4:
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
