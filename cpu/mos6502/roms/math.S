.org	$0000

lda #100
sta varA
sbc #1
sta varB

brk

.org	$0200
varA:
.db 0
varB:
.db 0
