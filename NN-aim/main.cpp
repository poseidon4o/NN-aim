#include <iostream>
#include "SDLWrapper.h"
#include "SDL.h"


int main(int argc, char * argv[])
{
	int cnt = 0, x1, y1, x2, y2;
	SDLWrapper sdl(640, 480);
	sdl.initSDL();

	while (!sdl.quit())
	{
		sdl.checkForEvent();
		sdl.setPixelsColor(static_cast<int>(rand()) % 640, static_cast<int>(rand()) % 480, 2,
			static_cast<unsigned char>(rand()), static_cast<unsigned char>(rand()), static_cast<unsigned char>(rand()));
		sdl.update();
	}
	return 0;
}