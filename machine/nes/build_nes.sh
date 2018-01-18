clang -o nes cpu/mos6502/src/* machine/nes/nes.c machine/nes/ppu.c -Icpu/mos6502/include/ -Imachine/nes -I$SDL_INCLUDE -L$SDL_LIB -lSDL2
