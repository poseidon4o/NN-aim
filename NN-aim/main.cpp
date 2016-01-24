#include <iostream>
#include "Game.h"


int main(int argc, char * argv[])
{
	SDLWrapper sdl(width, height);
	if (!sdl.initSDL())
	{
		return -1;
	}

	Game game;
	game.init(&sdl);

	while (!sdl.quit())
	{
		sdl.checkForEvent();
		game.move();
		game.draw();
		game.turnLeft(0);
		game.turnRight(1);

		SDL_Delay(5);
	}
	return 0;
}
