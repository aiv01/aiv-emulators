#include <mos6502.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SDL_MAIN_HANDLED 1
#include <SDL.h>

static void usage()
{
    fprintf(stdout, "nes <rom>\n");
}

static unsigned char *load_rom(char *filename, int *rom_size)
{
#ifndef _WIN32
    FILE *f = fopen(filename, "rb");
#else
    FILE *f = NULL;
    fopen_s(&f, filename, "rb");
#endif
    if (!f)
    {
        fprintf(stderr, "unable to open file %s\n", filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);

    unsigned char *data = malloc(file_size);
    if (!data)
    {
        fprintf(stderr, "unable to allocate memory\n");
        fclose(f);
        return NULL;
    }
    memset(data, 0, file_size);

    fseek(f, 0, SEEK_SET);

    if (fread(data, 1, file_size, f) != file_size)
    {
        fprintf(stderr, "error while reading binary image\n");
        fclose(f);
	free(data);
        return NULL;
    }

    fclose(f);

    *rom_size = file_size;
    return data;
 
}

int main(int argc, char *argv[])
{
    int ret = -1;
    if (argc < 2)
    {
        usage();
        fprintf(stderr, "you need to specify a rom file\n");
        return -1;
    }

    int rom_size = 0;
    unsigned char *rom = load_rom(argv[1], &rom_size);
    if (!rom)
    {
        fprintf(stderr, "unable to open rom file\n");
        return -1;
    }

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        goto end;
    }

    SDL_Window *window = SDL_CreateWindow("Nes",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            256,
            240,
            0);

    if (!window)
    {
        SDL_Quit();
	goto end;
    }

    mos6502_t cpu;
    mos6502_init(&cpu);

    cpu.sp = 0xFF;
    // get it from vector table
    cpu.pc = 0;

    ret = 0;

end:
    free(rom);

    return ret;
}
