#	Lab5b By Joseph Schechter	
	.section	.rodata
	.align 32
.LC0:
	.string	"eax: 0x%.8X\tebx: 0x%.8X\tecx: 0x%.8X\tedx: 0x%.8X\n"
	.text
#######################################################################
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp

#	push 2 values, then call incadd (adding 3+4=7)
	pushl	$3
	pushl	$4
	call	incadd
	addl	$8, %esp
	
#	push 2 values, then call incadd (adding 6+5=11)
	pushl	$6
	pushl	$5
	call	incadd
	addl	$8, %esp


	leave
	ret
	.size	main, .-main


#######################################################################



#######################################################################

#	incadd
#	perform an addition of two unsigned 32-bit numbers recursively
#	using only increment (inc)

	.type	incadd, @function
incadd:
	pushl	%ebp		#enter code
	movl	%esp, %ebp	#enter code

	pushfl

	movl	8(%ebp), %ecx
	movl	12(%ebp), %ebx

	cmpl	$0, %ecx
	je	endinc

	inc	%ebx

	dec	%ecx

	pushl	%ebx
	pushl	%ecx
	call	incadd
	addl	$8, %esp


endinc:
	movl	%ebx, %eax

	popfl

	leave
	ret
#######################################################################



	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.5"
