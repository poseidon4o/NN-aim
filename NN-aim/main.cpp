#include <iostream>
#include "Game.h"
#include "NeuralNetwork.h"
#include <ctime>

const int gamesCnt = 25;

int main(int argc, char * argv[])
{
	SDLWrapper sdl(width, height);
	if (!sdl.initSDL())
	{
		return -1;
	}
	Move move;

	Game * games = new Game[gamesCnt];
	for (int i = 0; i < gamesCnt; ++i)
		games[i].init(&sdl);
	srand(time(NULL));

	NeuralNetwork * nets[2];
	for (int i = 0; i < 2; ++i)
		nets[i] = new NeuralNetwork[gamesCnt];


	while (!sdl.quit())
	{
		SDL_Delay(5);
		sdl.checkForEvent();
		games[0].draw();
		for (int i = 0; i < gamesCnt; ++i)
		{
			games[0].move();
			for (int j = 0; j < 2; ++j)
			{
				move = nets[j][i].calculateMove(games[i].playerInFov(j), games[i].bulletInFov(j), games[i].canShoot(j), games[i].currentFov(j));
				games[i].makeMove(j, move);
			}
		}


		//if (games[0].end())
		//	games[0].reset();

	}



	delete[] games;
	return 0;
}
