#include <iostream>
#include <ctime>
#include <algorithm>

#include "GeneticAlgorithm.h"
#include "Game.h"
#include "NeuralNetwork.h"

const int gamesCnt = POPULATION_SIZE / 2;

inline void setFitness(Game * games, GeneticAlgorithm& genAlgo)
{
	for (int i = 0; i < gamesCnt; ++i)
	{
		int left, right;
		games[i].getNNRating(left, right);
		games[i].reset();
		genAlgo.SetChromosomeFitness(i * 2, left);
		genAlgo.SetChromosomeFitness(i * 2 + 1, right);
	}
}
//makes move on every game
inline void makeMove(Game * games, NeuralNetwork * nets[2])
{
	Move move;
	for (int i = 0; i < gamesCnt; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			move = nets[j][i].calculateMove(games[i].playerInFov(j), games[i].bulletInFov(j), games[i].canShoot(j), games[i].currentFov(j));
			games[i].makeMove(j, move);
			games[i].move();
		}
	}
}

int main(int argc, char * argv[])
{
	SDLWrapper sdl(width, height);
	if (!sdl.initSDL())
	{
		return -1;
	}

	Game * games = new Game[gamesCnt];
	for (int i = 0; i < gamesCnt; ++i)
		games[i].init(&sdl);
	srand(time(NULL));

	GeneticAlgorithm genAlgo(55);
	auto nnVals = genAlgo.GetGeneration();

	NeuralNetwork * nets[2];
	for (int i = 0; i < 2; ++i)
		nets[i] = new NeuralNetwork[gamesCnt];

	while (!sdl.quit())
	{

		//set new NNs
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < gamesCnt; ++j)
			{
<<<<<<< HEAD
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
=======
				nets[i][j].setWeights(nnVals[i * gamesCnt + j].weights);
>>>>>>> 7521975236e33665246335460bbf9c346b5bd7be
			}
		}

		while (!sdl.quit() && !games[0].end())
		{
			SDL_Delay(5);
			sdl.checkForEvent();
			games[0].draw();
			makeMove(games, nets);
		}
		setFitness(games, genAlgo);
		genAlgo.NextGenetarion();
	}


	for (int i = 0; i < 2; ++i)
		delete[] nets[i];
	delete[] games;
	return 0;
}
