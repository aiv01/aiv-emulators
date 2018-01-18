#include <mos6502.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SDL_MAIN_HANDLED 1
#include <SDL.h>

int ppu_tick(SDL_Renderer *, mos6502_t *);
void ppu_register_write(unsigned short, unsigned char);
unsigned char ppu_register_read(unsigned short);

void ppu_load(unsigned char *, int);
