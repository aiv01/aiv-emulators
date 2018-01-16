.org $0000

lda #$aa
cmp #$aa
beq isEqual
brk


isEqual:
    lda #$bb
    brk
