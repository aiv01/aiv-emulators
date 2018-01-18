clang -o nes cpu/mos6502/src/* machine/nes/nes.c -Icpu/mos6502/include/ -I$SDL_INCLUDE -L$SDL_LIB -lSDL2
