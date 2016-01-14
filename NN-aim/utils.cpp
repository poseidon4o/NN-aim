#include "utils.h"
#include <cmath>

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
	*(Uint32 *)target_pixel = pixel;
}

void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
	static const int BPP = 4;

	double r = (double)radius;

	for (double dy = 1; dy <= r; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
		int x = cx - dx;

		Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
		Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;

		for (; x <= cx + dx; x++)
		{
			*(Uint32 *)target_pixel_a = pixel;
			*(Uint32 *)target_pixel_b = pixel;
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}
	}
}

SDL_Surface *  drawCircle(const float radius, const char red, const char green, const char blue)
{
	const int size = static_cast<int>((radius + 0.5f) * 2);
	SDL_Surface * result = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);
	fill_circle(result, size / 2, size / 2, radius, SDL_MapRGB(result->format, red, green, blue));

	return result;
}
