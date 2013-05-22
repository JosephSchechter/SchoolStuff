# lab5 by Joseph Schechter
	.section	.rodata
	.align 32
.LC0:
	.string	"eax: 0x%.8X\tebx: 0x%.8X\tecx: 0x%.8X\tedx: 0x%.8X\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp

#	Insert your assembly code here.
# work by Joseph Schechter
	movl	$232, %eax
	movl	$0x14A, %edx
	xchgl	%eax, %edx
	movl	$0x12345678, %ebx
	movw	$0xFFFF, %bx
	movb	$0xDD, %bl
	movb	$0b01110001, %cl
	addl	$0xFEDCBA98, %ebx
	adcl	%edx, %eax


	movl	%edx, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf

	leave
	ret
	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.5"
