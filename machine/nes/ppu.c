#include <nes.h>

static void ppu_putpixel(SDL_Renderer *renderer, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}

int ppu_tick(SDL_Renderer *renderer)
{
	ppu_putpixel(renderer, 100, 100, 255, 0, 0);
	return 0;
}
