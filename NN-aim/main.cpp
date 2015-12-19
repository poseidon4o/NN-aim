#include <iostream>
#include "SDLWrapper.h"
#include "SDL.h"


int main(int argc, char * argv[])
{
	SDLWrapper sdl(640, 480);
	sdl.initSDL();

	while (!sdl.quit())
	{
		sdl.checkForEvent();
		sdl.setPixelsColor(static_cast<int>(rand()) % sdl.getWidth(), static_cast<int>(rand()) % sdl.getHeight(), 2,
			static_cast<unsigned char>(rand()) % 255, static_cast<unsigned char>(rand()) % 255, static_cast<unsigned char>(rand()) % 255);
		sdl.update();
	}
	return 0;
}