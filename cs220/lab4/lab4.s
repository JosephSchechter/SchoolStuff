	.data
#	Lab4 by Joseph Schechter

##########################################################################################

#	Define your variable (changeable) data here.
var3:
	.long 0, 0, 0
var4:
	.long 0, 0, 0, 0
var6:
	.long 0, 0, 0, 0, 0, 0
var9:
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0
var128a:
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
var128b:
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
var128result:
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
howmanya:
	.long 1
howmanyb:
	.long 1

##########################################################################################


##########################################################################################
	.section	.rodata

#	Define your constant (read-only) data here.
list3a:
	.long 1, 6, 2
list3b:
	.long 4, 5, 6
list4a:
	.long 9, 4, 6, 7
list4b:
	.long 3, 5, 8, 1
list6a:
	.long 1, 2, 4, 8, 16, 32
list6b:
	.long 0, 5, 10, 15, 20, 25
list9a:
	.long 1, 1, 5, 6, 7, 99, 23, 64, 0
list9b:
	.long 2, 44, 55, 1, 5, 66, 1, 0, 9
	
	
#	(Things like printf format strings, etc...).
newline:
	.string "\n"
newnum:
	.string "%d\n"
finishfunc:
	.string "End\n\n"
howlongquestion:
	.string "How long do you want your array to be? Type a number and end it with a letter or non-numerical character(Like a period): "
typenumprompt:
	.string	"\nType in the value of the list: "
readlistnum:
	.string "%3d"
nonnumskip:
	.string "%*[^0-9]"
number:
	.string "%d"
testnumber:
	.string "\n\nThe list size is: %d\n"
doneline:
	.string "%9999[^\n]"
main1:
	.string "\n\nI will show 2 different size list prints:\n\n"
main2:
	.string "\n\nI will show 2 different size list adds:\n\n"
main3:
	.string "\n\nI will ask for a value of the size of the list, I will print that value out, \nthen I will get the actual numbers in the list, then I will print those out\nThis will happen 2 times because we want 2 lists to compare \n\n"
main4:
	.string "\n\nAnd now the printout:\n"
	
##########################################################################################



##########################################################################################

	.text

.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp	# This number ($40) may need to be changed.
				# Depending on how large a frame main needs.

#	Insert your main function assembly code here.

	pushl	$main1
	call	printf
	popl	%edx

#	print out list3a
	pushl	$list3a
	pushl	$3
	call	printfunc
	addl	$8, %esp

#	print out list 9a
	pushl	$list9a
	pushl	$9
	call	printfunc
	addl	$8, %esp

	pushl	$main2
	call	printf
	popl	%edx
	
#	add list 3a and 3b
	pushl	$var3
	pushl	$list3a
	push	$list3b
	pushl	$3
	call	addfunc
	addl	$16, %esp

#	add list 6a and 6b
	pushl	$var6
	pushl	$list6a
	pushl	$list6b
	pushl	$6
	call	addfunc
	addl	$16, %esp
	
	pushl	$main3
	call	printf
	popl	%edx

#	user inputs list 1 (var128a)
	pushl	$var128a
	pushl	$howmanya
	call	readlist
	addl	$8, %esp
	
	pushl	%ecx
	pushl	$testnumber
	call	printf
	popl	%ebx
	popl	%ecx
	
	
	pushl	%ecx	#This is the value of howmanya
	
	pushl	$var128a
	pushl	howmanya
	call	printfunc
	addl	$8, %esp

#	user inputs list 2 (var128b)
	pushl	$var128b
	pushl	$howmanyb
	call	readlist
	addl	$8, %esp
	
	pushl	%ecx
	pushl	$testnumber
	call	printf
	popl	%ebx
	popl	%ecx
	
	pushl	%ecx	#This is the value of howmanyb
	
	pushl	$var128b
	pushl	howmanyb
	call	printfunc
	addl	$8, %esp
	
	popl	%ebx	#This is the size of howmanyb	
	popl	%ecx	#This is the size of howmanya

	cmpl	%ebx, %ecx	# howmanya - howmanyb
	js		lessthan
	
#	add list var128a and var128b (if howmanya is bigger than howmanyb, or they are equal)

	pushl	$main4
	call	printf
	popl	%edx
	
	
	pushl	$var128result
	pushl	$var128a
	pushl	$var128b
	pushl	howmanya
	call	addfunc
	addl	$16, %esp
	
	jmp		exitout
	
lessthan:
#	add list var128b and var128a (if howmanyb is bigger than howmanya)

	pushl	$main4
	call	printf
	popl	%edx
	
	pushl	$var128result
	pushl	$var128a
	pushl	$var128b
	pushl	howmanyb
	call	addfunc
	addl	$16, %esp

exitout:
	leave
	ret
	.size	main, .-main
	
##########################################################################################

#	Insert other functions here.



##########################################################################################

#	printfunc
#	this function prints a list of longs in memory separated by \n
#	arg1= size of stack, arg2= address of start of list

	.type	printfunc, @function
printfunc:
	pushl	%ebp		#enter code
	movl	%esp, %ebp	#enter code
	
	movl	12(%ebp), %eax	#the start address
	movl	8(%ebp), %ecx	#the size

pfstart1:
#	protecting the registers and printf the number
	pushl	%eax
	pushl	%ecx
	pushl	(%eax)		#the value in eax
	pushl	$newnum		#%d\n
	call	printf
	addl	$8, %esp
	popl	%ecx
	popl	%eax
        addl	$4, %eax
	loop	pfstart1

	pushl	$finishfunc
	call	printf
	addl	$4, %esp

	leave
	ret

##########################################################################################
	
	
	
	
##########################################################################################

#	addfunc	
#	this function adds 2 same-lenght lists of longs
#	arg1= size of the 3 lists, arg2= address of start of list1, 
#	arg3= address of start oflist 2, arg4= address of the output list


	.type	addfunc, @function
addfunc:
	pushl	%ebp		#enter code
	movl	%esp, %ebp	#enter code
	
	movl	8(%ebp), %ecx		#the size
	movl	12(%ebp), %eax		#the start addr of listb
	movl	16(%ebp), %ebx	#the start addr of lista
	movl	20(%ebp), %edx	#the start addr of var3
	pushl	%esi

	pushl	%edx
	pushl	%ecx

afstart1:	
	movl	$0, %esi
	addl	(%eax), %esi
	addl	(%ebx), %esi
	movl	%esi, (%edx)
	addl	$4, %eax
	addl	$4, %ebx
	addl	$4, %edx
	loop	afstart1
	
	popl	%ecx
	popl	%edx
	
	pushl	%edx
	pushl	%ecx
	call	printfunc
	addl	$8, %esp

	popl	%esi
	leave
	ret
	
##########################################################################################




##########################################################################################

#	readlist
#	reads a list of up to 128 longs (in decimal) from the user using scanf()'s "%d"
#	and stores them sequentially. The user should be able to indicate how many numbers to enter
#	arg1= starting address where the values are stored
#	return= the number of values entered

	.type	readlist, @function
readlist:
	pushl	%ebp		#enter code
	movl	%esp, %ebp	#enter code
	
	movl	8(%ebp), %edx   #howmany
	movl	12(%ebp), %eax	#the list
	
#	tell the user to say how many #'s he will imput

	pushl	%eax
	pushl	%edx
	pushl	%ebp
	pushl	$howlongquestion
	call	printf
	popl	%ebx
	popl	%ebp
	popl	%edx
	popl	%eax

#	user inputs value

	pushl	%eax
	pushl	%edx
	pushl	%ebp
	
	pushl	%edx
	
	pushl	$nonnumskip
	call	scanf
	popl	%ebx
	
	pushl	$newnum
	call	scanf
	popl	%ebx
		
	popl	%ebx
	
	popl	%ebp
	popl	%edx
	popl	%eax




	

	pushl	%eax
	pushl	%ebp
	pushl	%edx
	pushl	(%edx)
	pushl	$newnum
	call	printf

	popl	%ebx
	popl	%ebx

	popl	%edx
	popl	%ebp
	popl	%eax
	
	
	
	movl	(%edx), %ecx
getnumloop:
	pushl	%ecx
	
	pushl	%eax
	pushl	%ebp
	pushl	%edx
	pushl	$typenumprompt
	call	printf
	
	popl	%ebx
	
	popl	%edx
	popl	%ebp
	popl	%eax
	
	
	pushl	%edx
	pushl	%ebp
	pushl	%eax
	
	pushl	%eax
	
	pushl	$nonnumskip
	call	scanf
	popl	%ebx
	
	pushl	$newnum
	call	scanf
	popl	%ebx
	
	popl	%ebx
	
	popl	%eax
	popl	%ebp
	popl	%edx
	
	addl	$4, %eax
	popl	%ecx
	loop	getnumloop
	
	movl	(%edx), %ecx


	leave
	ret
	
##########################################################################################
	
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.5"
