.org $0000

ldy #1
cpy number
cpy number2
cpy number3

brk

.org $0100

number
.db	$1
number2
.db	$0
number3
.db	$2
