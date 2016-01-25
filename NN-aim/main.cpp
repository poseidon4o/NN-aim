#include <iostream>
#include "Game.h"
#include <ctime>


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
		//call this methods every frame
		SDL_Delay(5);
		sdl.checkForEvent();
		game.move();
		game.draw();
		int move = 0;
		srand(time(NULL));
		//methods used to control players
		for (int i = 0; i < 2; ++i)
		{
			move = rand() % 4;
			switch (move)
			{
			case 0:
				game.turnLeft(i);
			case 1:
				game.turnRight(i);
			case 2:
				game.move(i);
			case 3:
				game.shoot(i);
			}
		}
	}
	return 0;
}
