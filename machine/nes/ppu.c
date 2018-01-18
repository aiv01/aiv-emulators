#include <nes.h>

static unsigned int ppu_ticks;
static unsigned int ppu_scanline;

static void ppu_putpixel(SDL_Renderer *renderer, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

static void ppu_draw(SDL_Renderer *renderer, int x, int y)
{
	// draw background

	// draw sprite
}

int ppu_tick(SDL_Renderer *renderer)
{
	if (ppu_ticks >= 340)
	{
		ppu_scanline++;
		ppu_ticks = 0;
	}

	if (ppu_scanline >= 262)
	{
		ppu_scanline = 0;
	}

	if (ppu_scanline >= 1 && ppu_scanline <= 240)
	{
		if (ppu_ticks >= 1 && ppu_ticks <= 256)
		{
			int x = ppu_ticks-1;
			int y = ppu_scanline-1;
			ppu_draw(renderer, x, y);
		}
	}

	return 0;
}
