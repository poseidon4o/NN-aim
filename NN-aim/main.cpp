#include <iostream>
#include <ctime>
#include <algorithm>

#include "GeneticAlgorithm.h"
#include "Game.h"
#include "NeuralNetwork.h"
#include "RandomGenerator.h"

const int gamesCnt = POPULATION_SIZE / 2;

inline void setFitness(Game * games, GeneticAlgorithm& genAlgo)
{
	for (int i = 0; i < gamesCnt; ++i)
	{
		int left, right;
		games[i].getNNRating(left, right);
		games[i].reset();
		genAlgo.AddChromosomeFitness(i * 2, left);
		genAlgo.AddChromosomeFitness(i * 2 + 1, right);
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
	RandomGen::explicitSeed(time(NULL));

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
				nets[i][j].setWeights(nnVals[i * gamesCnt + j].weights);
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

	RandomGen::getInstance().gaussian(1, 1);
	for (int i = 0; i < 2; ++i)
		delete[] nets[i];
	delete[] games;
	return 0;
}
