#	Lab6 show3.s by Joseph Schechter
	.section	.rodata

read3:
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
	
compare3:
	movb	(%ebx), %cl
	cmpb	$0, %cl			#is it a null
	je	out3
	
	cmpb	$65, %cl	#A
	je	vowel3
	cmpb	$69, %cl	#E
	je	vowel3
	cmpb	$73, %cl	#I
	je	vowel3
	cmpb	$79, %cl	#O
	je	vowel3
	cmpb	$85, %cl	#U
	je	vowel3
	cmpb	$97, %cl	#a
	je	vowel3
	cmpb	$101, %cl	#e
	je	vowel3
	cmpb	$105, %cl	#i
	je	vowel3
	cmpb	$111, %cl	#o
	je	vowel3
	cmpb	$117, %cl	#u
	je	vowel3
	
	jmp	notvowel3

vowel3:
	addl	$1, %eax		#increase counter
	
notvowel3:
	pushl	%ebx
	pushl	%eax
	
	pushl	%ecx
	pushl	$read3
	call	printf
	addl	$8, %esp
	
	popl	%eax
	popl	%ebx
	
	
	addl	$1, %ebx		#next character
	jmp		compare3

	
out3:
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
