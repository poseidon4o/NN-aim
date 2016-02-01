#include <iostream>
#include <ctime>
#include <algorithm>

#include "GeneticAlgorithm.h"
#include "Game.h"
#include "NeuralNetwork.h"


void dumpChrom(const GeneticAlgorithm& genAlgo)
{

}

const int gamesCnt = 500;

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

	GeneticAlgorithm genAlgo(55);
	auto nnVals = genAlgo.GetGeneration();

	NeuralNetwork * nets[2];
	for (int i = 0; i < 2; ++i)
		nets[i] = new NeuralNetwork[gamesCnt / 2];

	while (!sdl.quit())
	{

		for (int i = 0; i < 2; ++i)
		{
			std::random_shuffle(nnVals.begin(), nnVals.end());
			//set new NNs
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < gamesCnt / 2; ++j)
				{
					nets[i][j].setWeights(nnVals[i * gamesCnt / 2 + j].weights);
				}
			}

			while (!sdl.quit() && !games[0].end())
			{
				SDL_Delay(1);
				sdl.checkForEvent();
				games[0].draw();
				for (int i = 0; i < gamesCnt / 2; ++i)
				{
					for (int j = 0; j < 2; ++j)
					{
						move = nets[j][i].calculateMove(games[i].playerInFov(j), games[i].bulletInFov(j), games[i].canShoot(j), games[i].currentFov(j));
						games[i].makeMove(j, move);
						games[i].move();
					}
				}
			}

			for (int i = 0; i < gamesCnt; ++i)
			{
				float left, right;
				games[i].getNNRaitng(left, right);
				games[i].reset();
				genAlgo.AddChromosomeFitness(i * 2, left);
				genAlgo.AddChromosomeFitness(i * 2 + 1, right);
			}
		}

		genAlgo.NextGenetarion();
	}


	for (int i = 0; i < 2; ++i)
		delete[] nets[i];
	delete[] games;
	return 0;
}
