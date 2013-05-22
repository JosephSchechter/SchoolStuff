# lab7 by Joseph Schechter
# I am unsure why this does not work correctly, but I am 
# submitting this as is with comments saying what i am doing
	.data

#	Define your variable (changeable) data here.

	.section	.rodata
strg32bit1:
	.long 0
	
quizmath1:
	.long 0
quizmath2:
	.long 0
	
	
# the grades are as follows: 1st 7 are quiz (1-7), next 6 are projects (8-13), 
# next is ME (14), next is FP (15), last is FE (16)

gradesfloat:
gradesfloatquiz:
	.long 0, 0, 0, 0, 0, 0, 0			#quiz
gradesfloatproj:
	.long 0, 0, 0, 0, 0, 0				#projects
gradesfloatmidterm:
	.long 0								#ME
gradesfloatfinalproj:	
	.long 0								#FP
gradesfloatfinalexam:
	.long 0								#FE
gradesfloatquizavg:
	.long 0								#quiz avg (-2 quizzes)
gradesfloatprojavg:
	.long 0								#project avg
gradesfloatavg:
	.long 0								#total average


#	Define your constant (read-only) data here.
#	(Things like printf format strings, etc...).

thequizzezstring1:
	.string "\n\nThe quiz grades are:\n\n"
theprojectsstring1:
	.string "\n\nThe project grades are:\n\n"
themidtermstring1:
	.string "\n\nThe midterm grade is:\n\n"
thefinalprojectstring1:
	.string "\n\nThe final project grade is:\n\n"
thefinalexamstring1:
	.string "\n\nThe final exam grade is:\n\n"
number:
	.string "%d"



s1grades:
	.byte 99, 50, 30, 59, 22, 90, 100 	#quiz
	.byte 89, 87, 89, 94, 29, 100		#projects
	.byte 40, 29, 90					#ME, FP, FE
s2grades:
	.byte 77, 66, 99, 89, 82, 96, 70 	#quiz
	.byte 100, 80, 66, 99, 100, 100		#projects
	.byte 77, 44, 77					#ME, FP, FE
s3grades:
	.byte 93, 55, 60, 53, 92, 90, 78 	#quiz
	.byte 100, 83, 88, 84, 89, 80		#projects
	.byte 70, 88, 96					#ME, FP, FE
s4grades:
	.byte 99, 100, 30, 98, 22, 90, 100 	#quiz
	.byte 89, 87, 89, 94, 29, 100		#projects
	.byte 99, 92, 90					#ME, FP, FE

	.text

.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp	# This number ($40) may need to be changed.
				# Depending on how large a frame main needs.

#	Insert your main function assembly code here.

	pushl	%eax
	pushl	$s1grades
	call	printfunc
	popl	%eax
	popl	%eax
	
	pushl	%eax
	pushl	$s2grades
	call	printfunc
	popl	%eax
	popl	%eax
	
	pushl	%eax
	pushl	$s3grades
	call	printfunc
	popl	%eax
	popl	%eax

	pushl	%eax
	pushl	$s4grades
	call	printfunc
	popl	%eax
	popl	%eax
	
	leave
	ret
	.size	main, .-main

#	Insert other functions here.


###############################################################
	.type	printfunc, @function
printfunc:
	
	#eax contains the location of the student's data in bytes
	movl	8(%ebp), %eax
	
	pushl	(%eax)
	call	printbeginning
	addl	$4, %esp


	pushl	(%eax)
	call	quizaverager
	addl	$4, %esp


	pushl	(%eax)
	call	projectaverager
	addl	$4, %esp

	# I didn't finish the last 2 steps in part A, but below is a list of things i would
	#need to do
	
	
	#next function will compare the final exam grade to the averages of the other
	#parts of the grade, it will have a memory spot to place all of the pieces 
	#that were lower, and then compare those pieces to eachother. it will find the lowest
	#2 (or 1 or 0) and it will mark those 2 values down to change the percentage
	#multiplication
	
	
	#the next function will then create the new total average and print out the rounded
	#off piece. The best way to round to 2 decimal places would be to mulitply by 100,
	#then add .5, then round down all the time, then divide by 100 to get it in the correct
	#format. We will then set up a bunch of jumps with comparisons to print out the correct
	#letter grade next to it

	leave
	ret
###############################################################


###############################################################
	.type	printbeginning, @function
printbeginning:
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	movl	8(%ebp), %edx		#the numbers in memory (grades)
	movl	$0, %ebx
	movl	$7, %ecx					#a counter
	
	#printing out the quizzes
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	$thequizzezstring1
	call	printf
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl

quizprintingbegin:	
	movb	(%edx), %bl
	
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	%ebx
	pushl	$number	
	call	printf
	popl	%eax
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	addl	$1, %edx	#next byte value (next grade)
	loop	quizprintingbegin
	
	###########################
	#now print out the projects
	
	movl	$6, %ecx					#a counter
	
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	$theprojectsstring1
	call	printf
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	
projprintingbegin:	
	movb	(%edx), %bl
	
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	%ebx
	pushl	$number	
	call	printf
	popl	%eax
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	addl	$1, %edx	#next byte value (next grade)
	loop	projprintingbegin
	
	###########################
	#now print out the ME
	
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	$themidtermstring1
	call	printf
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	movb	(%edx), %bl
	
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	%ebx
	pushl	$number	
	call	printf
	popl	%eax
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	addl	$1, %edx	#next byte value (next grade)
	
	
	###########################
	#now print out the FP
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	$thefinalprojectstring1
	call	printf
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	movb	(%edx), %bl
	
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	%ebx
	pushl	$number	
	call	printf
	popl	%eax
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	addl	$1, %edx	#next byte value (next grade)
	
	
	###########################
	#now print out the FE
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	$thefinalexamstring1
	call	printf
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	movb	(%edx), %bl
	
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	
	pushl	%ebx
	pushl	$number	
	call	printf
	popl	%eax
	popl	%eax
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	addl	$1, %edx	#next byte value (next grade)
	
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	leave
	
	ret
###############################################################



###############################################################
	.type	quizaverager, @function
quizaverager:
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx

	movl	$0, %ebx					#useful for converting to float
	movl	8(%ebp), %edx				#the numbers in memory (grades)
	movl	$7, %ecx					#a counter

	
	#we will try to put all of the parts in float form in their memory location
quizloop1:
	movb	(%edx), %bl
	movl	%ebx, strg32bit1
	fildl	strg32bit1	#loads my quiz grade onto the stack
	addl	$1, %edx	#next byte value (next grade)
	loop	quizloop1

	#now all 7 quizzes are on the float stack, time to put them in memory
		
	movl	gradesfloatquiz, %ebx	#where the quizzes will be stored in float
	movl	$7, %ecx
quizloop2:
	fstps	(%ebx)		#pops the quiz off the stack and puts it into the memory location
	addl	$4, %ebx	#goes to next float spot for next quiz
	loop	quizloop2
	
	#clearing out the float, make them all 0
	movl	$8, %ecx
clearfloat:
	fldz
	loop	clearfloat
	
	#now we will reorder them by bringing 2 at a time into the float stack
	#compare them, if they are in the wrong order, we will put them back reversed
	#then we will compare the next 2, we will do this a few times to make sure they
	#are all in the right order
	
	movl	gradesfloatquiz, %ebx
	movl	gradesfloatquiz, %edx
	addl	$4, %edx
	
	
	movl	$50, %eax		#pick a high number because I want to make sure its in the right order
orderquizzes:
	movl	$6, %ecx
comparequizzes:	
	fldz
	flds	(%ebx)
	flds	(%edx)
	
	#here i am getting errors on my fadd part, so i 
	#commented them out to compile correctly
	#the errors are "suffix or operands invalid " 
#	fadd	%st(1), %st(2)	#adding the 1st quiz added to the stack to a 0
	fsub	%st, %st(2)		#st2 - st0 =new st2
	#put a zero on, then add it to the result, so we can pop it off and test it
	fldz
	fadd	%st(2), %st
	fstps	strg32bit1
	testl	$0x80000000, strg32bit1		#tests if it is a negative value or not
#	jz	posvalue1					#positive, so they dont need to be reordered
#	jnz	negvalue1
	
posvalue1:
	fstps	(%edx)
	fstps	(%ebx)
	jmp	outposvalue1
negvalue1:
	fstps	(%ebx)
	fstps	(%edx)
outposvalue1:
	addl	$4, %ebx	#next comparison
	addl	$4, %edx
	loop	comparequizzes
	
	movl	$gradesfloatquiz, %ebx
	movl	$gradesfloatquiz, %edx
	addl	$4, %edx
	decl	%eax
	jnz		orderquizzes
	
	#once the eax counter reaches 0, it will be in order
	#now we find the average of the top 5
	
	movl	$5, %ecx
	movl	$gradesfloatquiz, %ebx
avgquizgrademath1:
	flds	(%ebx)
	addl	$4, %ebx
	loop	avgquizgrademath1
	
	#the top 5 are on the fpstack, now we add them all togeather
	movl	$4, %ecx
avgquizgrademath2:
	faddp
	loop	avgquizgrademath2
	
	#now we put a 5 onto the stack
	movl	$5, strg32bit1
	fildl	strg32bit1
	
	#now we divide st1 by st0(the 5)
	fdivrp
	fstps	gradesfloatquizavg
	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	leave
	ret
###############################################################

###############################################################
	.type	projectaverager, @function
projectaverager:
	pushfl
	pushl	%edi
	pushl	%esi
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx


	movl	$0, %ebx					#useful for converting to float
	movl	8(%ebp), %edx				#the numbers in memory (grades)
	addl	$7, %edx					#get to the projects
	movl	$6, %ecx					#a counter

projloop1:
	movb	(%edx), %bl
	movl	%ebx, strg32bit1
	fildl	strg32bit1	#loads my project grade onto the stack
	addl	$1, %edx	#next byte value (next grade)
	loop	projloop1
	
	movl	$5, %ecx
projloop2:
	faddp
	loop	projloop2
	
	#now we put a 5 onto the stack
	movl	$5, strg32bit1
	fildl	strg32bit1
	
	#now we divide st1 by st0(the 5)
	fdivrp
	fstps	gradesfloatprojavg
	
		
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	popl	%esi
	popl	%edi
	popfl
	
	leave
	ret
###############################################################


	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.5"
