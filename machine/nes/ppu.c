#include <nes.h>

static unsigned int ppu_ticks;
static unsigned int ppu_scanline;

typedef struct nes_ppu_state
{
	unsigned char ctrl;
	unsigned char mask;
	unsigned char status;
	unsigned char scroll_x;
	unsigned char scroll_y;
	unsigned char scroll_second_write;
	unsigned short addr;
	unsigned char addr_second_write;
	unsigned char pattern_table0[4096];
	unsigned char nametable0[1024];
} nes_ppu_state_t;

nes_ppu_state_t nes_ppu;

static void ppu_putpixel(SDL_Renderer *renderer, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

void ppu_load(unsigned char *chr, int size)
{
	memcpy(nes_ppu.pattern_table0, chr, size);
}

static void ppu_draw(SDL_Renderer *renderer, int x, int y)
{
	// draw background
	int tile_x = x / 8;
	int tile_y = y / 8;

	int tile_index = tile_y * 32 + tile_x;

	int tile_id = nes_ppu.nametable0[tile_index];

	unsigned char *pattern_table_base_address = nes_ppu.pattern_table0 + tile_id * 16;
	unsigned char cell_x = x % 8;
	unsigned char cell_y = y % 8;

	unsigned char pixel_line0 = pattern_table_base_address[cell_y];
	unsigned char pixel0 = (pixel_line0 >> (7 - cell_x)) & 0x01;

	unsigned char pixel_line1 = pattern_table_base_address[cell_y + 8];
	unsigned char pixel1 = (pixel_line1 >> (7 - cell_x)) & 0x01;

	unsigned char color = (pixel1 << 1 | pixel0);

	switch(color)
	{
		case 0:
			ppu_putpixel(renderer, x, y, 255, 0, 0);
			break;
		case 1:
			ppu_putpixel(renderer, x, y, 255, 255, 0);
			break;
		case 2:
			ppu_putpixel(renderer, x, y, 0, 255, 0);
			break;
		case 3:
			ppu_putpixel(renderer, x, y, 0, 0, 255);
			break;
	}

	// draw sprite

}

int ppu_tick(SDL_Renderer *renderer, mos6502_t *cpu)
{
	/*if (ppu_scanline == 242)
	{
	fprintf(stderr, "scanline %u cycle %d\n", ppu_scanline, ppu_ticks);
	}*/
	
	if (ppu_scanline >= 1 && ppu_scanline <= 240)
	{
		if (ppu_ticks >= 1 && ppu_ticks <= 256)
		{
			int x = ppu_ticks-1;
			int y = ppu_scanline-1;
			ppu_draw(renderer, x, y);
		}
	}

	if (ppu_scanline == 242 && ppu_ticks == 0)
	{
		nes_ppu.status |= 0x80;
		// trigger NMI
		if (nes_ppu.ctrl >> 7)
		{
			cpu->interrupt(cpu, 0);
		}
		SDL_RenderPresent(renderer);
	}

	if (ppu_scanline == 261 && ppu_ticks == 0)
	{
		nes_ppu.status &= 0x7f;
	}

	ppu_ticks++;

	if (ppu_ticks >= 340)
	{
		ppu_scanline++;
		ppu_ticks = 0;
	}

	if (ppu_scanline >= 262)
	{
		ppu_scanline = 0;
		ppu_ticks = 0;
	}


	return 0;
}

static void ppu_write(unsigned short address, unsigned char value)
{
	fprintf(stderr, "%04X\n", address);
	unsigned short page = address >> 8;
	switch(page)
	{
		case 0x00:
			nes_ppu.pattern_table0[address] = value;
			break;
		case 0x20:
			nes_ppu.nametable0[address - 0x2000] = value;
			break;
	}
}

void ppu_register_write(unsigned short address, unsigned char value)
{
	switch(address)
	{
		case 0:
			nes_ppu.ctrl = value;
			break;
		case 6:
			if (nes_ppu.addr_second_write)
			{
				nes_ppu.addr = nes_ppu.addr << 8 | value;
				fprintf(stderr, "ADDR 2 %04x\n", nes_ppu.addr);
			}
			else 
			{
				nes_ppu.addr = value;
				fprintf(stderr, "ADDR 1 %04x\n", nes_ppu.addr);
			}
			nes_ppu.addr_second_write = !nes_ppu.addr_second_write;
			break;
		case 7:
			ppu_write(nes_ppu.addr, value);
			break;
	}
	fprintf(stdout, "PPU WRITE %04X %02X\n", address, value);
}

unsigned char ppu_register_read(unsigned short address)
{
	fprintf(stdout, "PPU READ %04X\n", address);
	return 0;
}