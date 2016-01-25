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
	int cnt = 0;
	while (!sdl.quit())
	{
		cnt++;
		sdl.checkForEvent();
		game.move();
		game.draw();
		game.turnLeft(0);
		game.turnRight(1);
		game.shoot(0);
		game.shoot(1);
		if (cnt > 500)
		{
			SDL_Delay(500);
			cnt = 0;
			game.reset();
		}
		SDL_Delay(5);
	}
	return 0;
}
