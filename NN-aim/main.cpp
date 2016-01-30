#include <iostream>
#include "Game.h"
#include "NeuralNetwork.h"
#include <ctime>


int main(int argc, char * argv[])
{
	NeuralNetwork nets[2];
	Move move;
	const auto FPS = 60;


	SDLWrapper sdl(width, height);
	if (!sdl.initSDL())
	{
		return -1;
	}

	Game game;
	game.init(&sdl);
	srand(time(NULL));

	auto lastDraw = SDL_GetTicks();

	while (!sdl.quit())
	{
		auto now = SDL_GetTicks();
		if (now - lastDraw >= 1000 / FPS) {
			//call this methods every frame
			sdl.checkForEvent();
			game.move();
			game.draw();
			if (game.end())
				game.reset();
		}

		//methods used to control players
		for (int i = 0; i < 2; ++i)
		{
			move = nets[i].calculateMove(game.playerInFov(i), game.bulletInFov(i), game.canShoot(i), game.currentFov(i));
			game.makeMove(i, move);
		}
	}
	return 0;
}
