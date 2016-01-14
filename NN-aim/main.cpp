#include <iostream>
#include "SDLWrapper.h"
#include "SDL.h"
#include "utils.h"

int main(int argc, char * argv[])
{
	SDLWrapper sdl(640, 480);
	sdl.initSDL();

	Vector2 from(0.f,0.f), step(5.f, 5.f);
	SDL_Surface * p1 = drawCircle(20, 0xff, 0, 0xff);
	SDL_Texture * tex = sdl.createTex(p1);

	while (!sdl.quit())
	{
		sdl.checkForEvent();
		sdl.clear();
		sdl.drawTex(tex, from);
		sdl.update();

		from += step;
		from.x = from.getIntX() % 640;
		from.y = from.getIntY() % 480;
		SDL_Delay(10);
	}
	return 0;
}
