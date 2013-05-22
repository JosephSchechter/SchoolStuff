	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"You entered: "
.LC1:
	.string	"\nSize: %d\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$164, %esp
	movl	$0, -8(%ebp)
	movl	$1819043144, -20(%ebp)
	movl	$1867980911, -16(%ebp)
	movl	$6581362, -12(%ebp)
	movl	$.LC0, (%esp)
	call	printf
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	show_string
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$544237914, -43(%ebp)
	movl	$540226097, -39(%ebp)
	movl	$2100175680, -35(%ebp)
	movl	$810313248, -31(%ebp)
	movl	$1231376441, -27(%ebp)
	movw	$21871, -23(%ebp)
	movb	$0, -21(%ebp)
	movl	$.LC0, (%esp)
	call	printf
	leal	-43(%ebp), %eax
	movl	%eax, (%esp)
	call	show_string
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$1953711476, -62(%ebp)
	movl	$543649353, -58(%ebp)
	movl	$1867081025, -54(%ebp)
	movl	$1766154581, -50(%ebp)
	movw	$30031, -46(%ebp)
	movb	$0, -44(%ebp)
	movl	$.LC0, (%esp)
	call	printf
	leal	-62(%ebp), %eax
	movl	%eax, (%esp)
	call	show_string
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$875770417, -82(%ebp)
	movl	$943142453, -78(%ebp)
	movl	$1596796985, -74(%ebp)
	movl	$2083470635, -70(%ebp)
	movl	$2895423, -66(%ebp)
	movl	$.LC0, (%esp)
	call	printf
	leal	-82(%ebp), %eax
	movl	%eax, (%esp)
	call	show_string
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$1936287828, -136(%ebp)
	movl	$544434464, -132(%ebp)
	movl	$1702063946, -128(%ebp)
	movl	$1394632816, -124(%ebp)
	movl	$1667590243, -120(%ebp)
	movl	$1919251560, -116(%ebp)
	movl	$1277195047, -112(%ebp)
	movl	$540435041, -108(%ebp)
	movl	$1953719668, -104(%ebp)
	movl	$1713398574, -100(%ebp)
	movl	$543517801, -96(%ebp)
	movl	$544370534, -92(%ebp)
	movl	$842167139, -88(%ebp)
	movw	$48, -84(%ebp)
	movl	$.LC0, (%esp)
	call	printf
	leal	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	show_string
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$0, %eax
	addl	$164, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (Debian 4.3.2-1.1) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
