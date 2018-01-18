#include <nes.h>

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
        fprintf(stderr, "unable to initialize SDL\n");
        goto end;
    }

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(256, 240, 0, &window, &renderer))
    {
            fprintf(stderr, "unable to create window and renderer\n");
	    SDL_Quit();
	    goto end;
    }

    SDL_SetWindowTitle(window, "AIV Nes");


    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;
    // TODO get it from vector table
    cpu.pc = 0;

    int ended = 0;

    int ppu_ticks = 0;
    int cpu_accumulated_ticks = 0;

    while(!ended)
    {
    	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
        	if (event.type == SDL_QUIT) {
			ended = 1;
            		break;
        	}
	}

	ppu_tick(renderer);
	ppu_ticks++;

	if (ppu_ticks >= 3)
	{
		if (cpu_accumulated_ticks <= 0)
		{
			cpu_accumulated_ticks = mos6502_tick(&cpu);
			if (cpu_accumulated_ticks <= 0)
			{
				break;
			}
        fprintf(stdout, "[$%04X] A=$%02X X=$%02X Y=$%02X Flags=$%02X SP=$%02X\n",
            cpu.pc,
            cpu.a,
            cpu.x,
            cpu.y,
            cpu.flags,
            cpu.sp
        );
		}
		// always decrease one accumulated tick
		cpu_accumulated_ticks--;
		ppu_ticks = 0;
	}

        SDL_RenderPresent(renderer);
    }

    ret = 0;

end:
    free(rom);

    return ret;
}
