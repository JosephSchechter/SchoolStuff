#	Lab6 show5.s by Joseph Schechter
	.data
storage51:
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1
storage52:
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0
######################################
	.section	.rodata
refreshstorage:
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1
	.byte -1	
ones:
	.byte 1
	.byte 1
	.byte 1
	.byte 1
	.byte 1
	.byte 1
	.byte 1
	.byte 1
read5:
	.string	"%s"



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
	
	movl	$0, %eax		#eax is the mmx counter and what is returned
							#eax will be split up into ah and al, 
							#ah will be a boolean of if we encounter a null or not
							#al will be the counter, i expect us not to use over 256 mmx registers which is 2048 characters
							
	movl    8(%ebp), %ebx	#ebx has the string location
	movl	$storage51, %edx	#mem addr of storage51 into edx
	movl	$0, %ecx		#will hold the character in cl and a storage counter in ch
	movb	$1, %ah		#ah is a check for if there was a null meaning no more reading to be done, 0 = done
	
restart5:
	movb	(%ebx), %cl
	cmpb	$0, %cl			#is the value a null
	jne	okayval
	movb	$8, %ch			#if it is null, we will put a -1 in there so when it adds 1, it
	addb	$-1, %cl		#will be a null that is called to print
	movb	$0, %ah			#the code won't read any more after this group of 8 bytes
okayval:
	cmpb	$127, %cl		#will check if the value go out of range (only 127 ascii chars), if so, 
	jne	notoutbounds		#set it to 1 less and eventually it will add 1 to get 
	addb	$-1, %cl		#back to what it originally was, a sort of saturation method
notoutbounds:
	movb	%cl, (%edx)		#copy the value into my storage space
	addb	$1, %ch
	cmpb	$9, %ch			#is the memory 64 bits full
	je	fillmmx
	addl	$1, %edx
	addl	$1, %ebx
	jmp	restart5

fillmmx:
	movl	$storage51, %edx	
#	movb	$0, %ch
	movq	storage51, %mm0
	paddsb	ones, %mm0
	movq	%mm0, storage52
#	pushl	%ecx
#	movl	$refreshstorage, %ecx
#	movsb	(%ecx), storage51
#	popl	%ecx
	addb	$1, %al
	
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%esi
	pushl	%edi
	pushfl
	pushl	$storage52
	pushl	$read5
	call	printf
	popl	%ebx
	popl	%ebx
	popfl
	popl	%edi
	popl	%esi
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	
	cmpb	$0, %ah			#time to finish
	je	out5

#	addl	$8, %ebx
#	addl	$64, %ebx		#next set of bits to read
	jmp	restart5

out5:	
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
