	.section	.rodata
	.align 32
.LC0:
	.string	"eax: 0x%.8X\tebx: 0x%.8X\tecx: 0x%.8X\tedx: 0x%.8X\nesi: 0x%.8X\tedi: 0x%.8X\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp

#	Insert your assembly code here.
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B1 Addition
#	The number 0xA4259929E9492903 across eax and ebx
	movl	$0xA4259929, %eax
	movl	$0xE9492903, %ebx
#	The number 0x2013AD2494AEFF72 across ecx and edx
	movl	$0x2013AD24, %ecx
	movl	$0x94AEFF72, %edx
	addl	%edx, %ebx
	adcl	%ecx, %eax
#	answer should be across eax and ebx should be 0xC439464E 0x7DF82875
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B2 Addition
#	The number 0x2425292949290322 across eax and ebx
	movl	$0x24252929, %eax
	movl	$0x49290322, %ebx
#	The number 0x2022474529AF72E2 across ecx and edx
	movl	$0x20224745, %ecx
	movl	$0x29AF72E2, %edx
	addl	%edx, %ebx
	adcl	%ecx, %eax
#	answer should be across eax and ebx should be 0x4447706E ebx: 0x72D87604
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B3   2 More Additions (B3a and B3b)
#	B3a Addition
#	The number 0x9BA4210FB5234679 across eax and ebx
	movl	$0x9BA4210F, %eax
	movl	$0xB5234679, %ebx
#	The number 0x3BDEC147821ECFBA across ecx and edx
	movl	$0x3BDEC147, %ecx
	movl	$0x821ECFBA, %edx
	addl	%edx, %ebx
	adcl	%ecx, %eax
#	answer should be across eax and ebx should be 0xD782E257 ebx: 0x37421633
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B3b Addition
#	The number 0x3EBA7469FEC4DB10 across eax and ebx
	movl	$0x3EBA7469, %eax
	movl	$0xFEC4DB10, %ebx
#	The number 0x1125BBB96BEDC142 across ecx and edx
	movl	$0x1125BBB9, %ecx
	movl	$0x6BEDC142, %edx
	addl	%edx, %ebx
	adcl	%ecx, %eax
#	answer should be across eax and ebx should be 0x4FE03023 ebx: 0x6AB29C52
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print


#	B4 Division
#	dividing the 128 bit 0xA241A35FE34383E4AF4563EADBCB47EF by 0x182341AA
#	format is [edx:eax]/arg -> eax R edx
#	i start w/ a 32 bit # to prevent it from overloading, put a 0 in edx
	movl	$0x00000000, %edx
	movl	$0xA241A35F, %eax
	movl	$0x182341AA, %ebx
	divl	%ebx
	pushl	%eax
#	now we can divide fully edx:eax/arg for next groups of 32:32 bits
	movl	$0xE34383E4, %eax
	divl	%ebx
	pushl	%eax
	movl	$0xAF4563EA, %eax
	divl	%ebx
	push	%eax
	movl	$0xDBCB47EF, %eax
	divl	%ebx
#	division is complete, we'll put the remainder in esi, the answer will be in eax:ebx:ecd:edx
	movl	%edx, %esi
	movl	%eax, %edx
	popl	%ecx
	popl	%ebx
	popl	%eax
#	The answer will be 0x00000006:0xB8DC2950:0xDADC05DC:0x9ACE14B4 R 0x0713D467
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print
	

#	B5 3 more divisions(B5a, B5b, B5c)
#	B5a Division
#	dividing the 128 bit 0x398BF18A09CF572E3DDEB4711490BDFF by 0x49A0CC56
#	format is [edx:eax]/arg -> eax R edx
#	i start w/ a 32 bit # to prevent it from overloading, put a 0 in edx
	movl	$0x00000000, %edx
	movl	$0x398BF18A, %eax
	movl	$0x49A0CC56, %ebx
	divl	%ebx
	pushl	%eax
#	now we can divide fully edx:eax/arg for next groups of 32:32 bits
	movl	$0x09CF572E, %eax
	divl	%ebx
	pushl	%eax
	movl	$0x3DDEB471, %eax
	divl	%ebx
	push	%eax
	movl	$0x1490BDFF, %eax
	divl	%ebx
#	division is complete, we'll put the remainder in esi, the answer will be in eax:ebx:ecd:edx
	movl	%edx, %esi
	movl	%eax, %edx
	popl	%ecx
	popl	%ebx
	popl	%eax
#	The answer will be 0x00000000:0xC815F955:0xD63C996D:0x07648220 R 0x0D1B873F
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B5b Division
#	dividing the 128 bit 0x2166FFD98A063C89DEF7633219AABE65 by 0x896A8BBC
#	format is [edx:eax]/arg -> eax R edx
#	i start w/ a 32 bit # to prevent it from overloading, put a 0 in edx
	movl	$0x00000000, %edx
	movl	$0x2166FFD9, %eax
	movl	$0x896A8BBC, %ebx
	divl	%ebx
	pushl	%eax
#	now we can divide fully edx:eax/arg for next groups of 32:32 bits
	movl	$0x8A063C89, %eax
	divl	%ebx
	pushl	%eax
	movl	$0xDEF76332, %eax
	divl	%ebx
	push	%eax
	movl	$0x19AABE65, %eax
	divl	%ebx
#	division is complete, we'll put the remainder in esi, the answer will be in eax:ebx:ecd:edx
	movl	%edx, %esi
	movl	%eax, %edx
	popl	%ecx
	popl	%ebx
	popl	%eax
#	The answer will be 0x00000000:0x3E3A1D8F:0xF7EE9DB1:0x67FE7F32 R 0x1F012FAD
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B5c Division
#	dividing the 128 bit 0xA9820BCF7665EE387621445CCFBB1299 by 0xCBDE12AA
#	format is [edx:eax]/arg -> eax R edx
#	i start w/ a 32 bit # to prevent it from overloading, put a 0 in edx
	movl	$0x00000000, %edx
	movl	$0xA9820BCF, %eax
	movl	$0xCBDE12AA, %ebx
	divl	%ebx
	pushl	%eax
#	now we can divide fully edx:eax/arg for next groups of 32:32 bits
	movl	$0x7665EE38, %eax
	divl	%ebx
	pushl	%eax
	movl	$0x7621445C, %eax
	divl	%ebx
	push	%eax
	movl	$0xCFBB1299, %eax
	divl	%ebx
#	division is complete, we'll put the remainder in esi, the answer will be in eax:ebx:ecd:edx
	movl	%edx, %esi
	movl	%eax, %edx
	popl	%ecx
	popl	%ebx
	popl	%eax
#	The answer will be 0x00000000:0xD4DAAC57:0x60375DD9:0x45CC78E2 R 0x0B76E885
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print


#	B6 Multiplication
#	want to multiply the numbers 0x[24252929][49290322] * 0x[2013AD24][94AEFF72] call it [f1][f2]*[w1][w2]
#	multiply w2*f2
	movl	$0x94AEFF72, %eax
	movl	$0x49290322, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w2*f1
	movl	$0x94AEFF72, %eax
	movl	$0x24252929, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f2
	movl	$0x2013AD24, %eax
	movl	$0x49290322, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f1
	movl	$0x2013AD24, %eax
	movl	$0x24252929, %edx
	mull	%edx
#	all the multiplication is finished, now i have to add all the pieces in different places
	movl	%eax, %ebx
	movl	%edx, %eax
	popl	%ecx
	addl	%ecx, %ebx
	adcl	$0, %eax
	popl	%ecx
	popl	%edx
	addl	%edx, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
#	the answer will be across eax:ebx:ecx:edx; 0x04876C59:0x7E3E6FCD:0x71504EBA:0x377E4324
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print
	
	

#	B7 3 More Multiplications (B7a, B7b, B7c)
#	B7a Multiplication
#	want to multiply the numbers 0x[9C86B3AA][DE87F377] * 0x[5BEF4322][8AFECCDE] call it [f1][f2]*[w1][w2]
#	multiply w2*f2
	movl	$0x8AFECCDE, %eax
	movl	$0xDE87F377, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w2*f1
	movl	$0x8AFECCDE, %eax
	movl	$0x9C86B3AA, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f2
	movl	$0x5BEF4322, %eax
	movl	$0xDE87F377, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f1
	movl	$0x5BEF4322, %eax
	movl	$0x9C86B3AA, %edx
	mull	%edx
#	all the multiplication is finished, now i have to add all the pieces in different places
	movl	%eax, %ebx
	movl	%edx, %eax
	popl	%ecx
	addl	%ecx, %ebx
	adcl	$0, %eax
	popl	%ecx
	popl	%edx
	addl	%edx, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
#	the answer will be across eax:ebx:ecx:edx; 0x38362CAB:0xD986112A:0x2F598671:0x05F9F532
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B7b Multiplication
#	want to multiply the numbers 0x[DD855421][BAAF443D] * 0x[667A8E62][1BB9CF72] call it [f1][f2]*[w1][w2]
#	multiply w2*f2
	movl	$0x1BB9CF72, %eax
	movl	$0xBAAF443D, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w2*f1
	movl	$0x1BB9CF72, %eax
	movl	$0xDD855421, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f2
	movl	$0x667A8E62, %eax
	movl	$0xBAAF443D, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f1
	movl	$0x667A8E62, %eax
	movl	$0xDD855421, %edx
	mull	%edx
#	all the multiplication is finished, now i have to add all the pieces in different places
	movl	%eax, %ebx
	movl	%edx, %eax
	popl	%ecx
	addl	%ecx, %ebx
	adcl	$0, %eax
	popl	%ecx
	popl	%edx
	addl	%edx, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
#	the answer will be across eax:ebx:ecx:edx; 0x58AD2C44:0x62278FE8:0x517B172D:0x994EB62A
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	B7c Multiplication
#	want to multiply the numbers 0x[8ABF1926][A63298DD] * 0x[BB509800][2DFEAACC] call it [f1][f2]*[w1][w2]
#	multiply w2*f2
	movl	$0x2DFEAACC, %eax
	movl	$0xA63298DD, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w2*f1
	movl	$0x2DFEAACC, %eax
	movl	$0x8ABF1926, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f2
	movl	$0xBB509800, %eax
	movl	$0xA63298DD, %edx
	mull	%edx
	pushl	%eax
	pushl	%edx
#	multiply w1*f1
	movl	$0xBB509800, %eax
	movl	$0x8ABF1926, %edx
	mull	%edx
#	all the multiplication is finished, now i have to add all the pieces in different places
	movl	%eax, %ebx
	movl	%edx, %eax
	popl	%ecx
	addl	%ecx, %ebx
	adcl	$0, %eax
	popl	%ecx
	popl	%edx
	addl	%edx, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
	addl	%edx, %ecx
	adcl	$0, %ebx
	adcl	$0, %eax
	popl	%edx
#	the answer will be across eax:ebx:ecx:edx; 0x65854578:0xA75775BF:0x755EB83C:0x8E1A921C
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	C1 color code separation
	movw	$34927, %ax
#	blue (5 bits) (all of these are less than 8 bits, so we can use b instead of w, 
# 	but for backward addition I should keep it 16bits)
	movw	%ax, %bx
	andw	$0b0000000000011111, %bx
#	green (6 bits, need to go 5 to the right)
	rorw	$5, %ax
	movw	%ax, %cx
	andw	$0b0000000000111111, %cx
	rorw	$-5, %ax
#	red (5 bits, need to go 5 to the left)
	rolw	$5, %ax
	movw	%ax, %dx
	andw	$0b0000000000011111, %dx
	rolw	$-5, %ax
#	ebx should be 0xXXXX000F, ecx should be 0xXXX0003, edx should be 0xXXXX0011
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	C2 color code computation red=13, green=25, blue=11
	andw	$0, %ax
	movw	$11, %bx
	movw	$25, %cx
	movw	$13, %dx
#	add red, move left 6 for green
	addw	%dx, %ax
	rolw	$6, %ax
#	add green, move left 5 for blue
	addw	%cx, %ax
	rolw	$5, %ax
#	add blue, and we're done
	addw	%bx, %ax
#	eax should be 0xXXXX6B2B
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	C3a 2 More Color Code Separation (C3a1 and C3a2)
#	C3a1 color code separation
	movw	$16720, %ax
#	blue (5 bits) (all of these are less than 8 bits, so we can use b instead of w, 
# 	but for backward addition I should keep it 16bits)
	movw	%ax, %bx
	andw	$0b0000000000011111, %bx
#	green (6 bits, need to go 5 to the right)
	rorw	$5, %ax
	movw	%ax, %cx
	andw	$0b0000000000111111, %cx
	rorw	$-5, %ax
#	red (5 bits, need to go 5 to the left)
	rolw	$5, %ax
	movw	%ax, %dx
	andw	$0b0000000000011111, %dx
	rolw	$-5, %ax
#	ebx should be 0xXXXX0010, ecx should be 0xXXX000A, edx should be 0xXXXX0008
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	C3a2 color code separation
	movw	$9822, %ax
#	blue (5 bits) (all of these are less than 8 bits, so we can use b instead of w, 
# 	but for backward addition I should keep it 16bits)
	movw	%ax, %bx
	andw	$0b0000000000011111, %bx
#	green (6 bits, need to go 5 to the right)
	rorw	$5, %ax
	movw	%ax, %cx
	andw	$0b0000000000111111, %cx
	rorw	$-5, %ax
#	red (5 bits, need to go 5 to the left)
	rolw	$5, %ax
	movw	%ax, %dx
	andw	$0b0000000000011111, %dx
	rolw	$-5, %ax
#	ebx should be 0xXXXX001E, ecx should be 0xXXX0032, edx should be 0xXXXX0004
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print


#	C3b 2 More Color Code Computation (C3b1 and C3b2)
#	C3b1 color code computation red=5, green=20, blue=1
	andw	$0, %ax
	movw	$1, %bx
	movw	$20, %cx
	movw	$5, %dx
#	add red, move left 6 for green
	addw	%dx, %ax
	rolw	$6, %ax
#	add green, move left 5 for blue
	addw	%cx, %ax
	rolw	$5, %ax
#	add blue, and we're done
	addw	%bx, %ax
#	eax should be 0xXXXX2A81
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

#	C3b2 color code computation red=31, green=18, blue=16
	andw	$0, %ax
	movw	$16, %bx
	movw	$18, %cx
	movw	$31, %dx
#	add red, move left 6 for green
	addw	%dx, %ax
	rolw	$6, %ax
#	add green, move left 5 for blue
	addw	%cx, %ax
	rolw	$5, %ax
#	add blue, and we're done
	addw	%bx, %ax
#	eax should be 0xXXXXFA50
#	print the registers
	pushf
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	pushl	$.LC0
	call	printf
	popl	%eax
	popl	%eax
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popf
#	end register print

	leave
	ret
	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.5"
