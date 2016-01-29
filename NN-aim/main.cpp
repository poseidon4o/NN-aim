#include <iostream>
#include "Game.h"
#include "NeuralNetwork.h"
#include <ctime>


int main(int argc, char * argv[])
{
	NeuralNetwork nets[2];
	Move move;

	SDLWrapper sdl(width, height);
	if (!sdl.initSDL())
	{
		return -1;
	}

	Game game;
	game.init(&sdl);
	srand(time(NULL));

	while (!sdl.quit())
	{
		//call this methods every frame
		SDL_Delay(1);
		sdl.checkForEvent();
		game.move();
		game.draw();

		//methods used to control players
		for (int i = 0; i < 2; ++i)
		{
			move = nets[i].calculateMove(game.playerInFov(i), game.bulletInFov(i), game.canShoot(i), game.currentFov(i));
			game.makeMove(i, move);
		}
	}
	return 0;
}
