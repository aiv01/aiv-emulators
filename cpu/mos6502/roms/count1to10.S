.org $0000

lda #0
counter:
    cmp #0
    beq end
    sbc #1

end:
    brk
