#include <iostream>
#include "SDLWrapper.h"
#include "SDL.h"
#include "Dot.h"

int main(int argc, char * argv[])
{
	SDLWrapper sdl(640, 480);
	sdl.initSDL();
	Dot test(200.f, 200.f, 10.f);

	Vector2 from(0.f,0.f), size(40.f,40.f) ,step(20.f, 20.f);


	while (!sdl.quit())
	{
		sdl.checkForEvent();
		sdl.clear();
		sdl.drawLine(from, from + size, 0xff, 0x00, 0x00);
		sdl.update();

		from += step;
		from.x = from.getIntX() % 640;
		from.y = from.getIntY() % 480;
		SDL_Delay(10);
	}
	return 0;
}
