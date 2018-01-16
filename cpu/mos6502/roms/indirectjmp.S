.org $0000

loop:
	jmp (address)
	nop
	nop
	nop
	nop
	nop

foo:
	inc number
	jmp loop

.org $0100

address
.dw	foo

number
.db	$aa
