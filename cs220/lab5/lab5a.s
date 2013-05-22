#	Lab5a By Joseph Schechter	
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

#	Start of calling functions
	call	myfunc1

	leave
	ret
	.size	main, .-main


#######################################################################



#######################################################################

#	myfunc1 
#	calls myfunc2

	.type	myfunc1, @function
myfunc1:
	pushl	%ebp		#enter code
	movl	%esp, %ebp	#enter code

	call	myfunc2

	leave
	ret
#######################################################################


#######################################################################

#	myfunc2
#	calls myfunc3	

	.type	myfunc2, @function
myfunc2:
	pushl	%ebp		#enter code
	movl	%esp, %ebp	#enter code

	call	myfunc3

	leave
	ret
#######################################################################


#######################################################################

#	myfunc3
#	
#	

	.type	myfunc3, @function
myfunc3:
	pushl	%ebp		#enter code
	movl	%esp, %ebp	#enter code
	subl	$4, %esp	#32 bit local variable
	
	fldpi
	fld1	

	fdivp	%st, %st(1)	#divides st(1)/st stores to st
	fsts	-4(%ebp)	#local variables are at -4,-8 etc ebp


	leave
	ret
#######################################################################


	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.5"
