.org $0000

lda #$aa
ldx #$bb
ldy #$cc

jsr helloWorld

adc #1

brk

helloWorld:
	php ; push flags
	pha ; push A
	txa
	pha ; push X (taken from A)
	tya
	pha ; push Y (taken from A)
	; do something ...
	lda #$dd
	ldx #$ee
	ldy #$ff
	; reset
	pla
	tay ; pull Y (taken from A)
	pla
	tax ; pull X (taken from A)
	pla ; pull A
	plp ; pull flags
	rts
