#include <iostream>
#include <ctime>
#include <algorithm>

#include "GeneticAlgorithm.h"
#include "Game.h"
#include "NeuralNetwork.h"
#include "RandomGenerator.h"

#include <thread>

const int gamesCnt = POPULATION_SIZE / 2;

inline void setFitness(Game * games, GeneticAlgorithm& genAlgo)
{
	for (int i = 0; i < gamesCnt; ++i)
	{
		int left, right;
		games[i].getNNRating(left, right);
		games[i].reset();
		genAlgo.AddChromosomeFitness(i, left);
		genAlgo.AddChromosomeFitness(i + gamesCnt, right);
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

void runRound(Game * games, GeneticAlgorithm& genAlgo, NeuralNetwork * nets[2], SDLWrapper& sdl, bool display, bool shuffle = true)
{
	auto& nnVals = genAlgo.GetGeneration();
	if(shuffle)
		std::random_shuffle(nnVals.begin(), nnVals.end());
	else
		std::sort(nnVals.begin(), nnVals.end());

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
		sdl.checkForEvent();
		if (display)
		{
			SDL_Delay(1);
			games[0].draw();
		}
		makeMove(games, nets);
	}
	setFitness(games, genAlgo);
}

void runRounds(int iterCnt, Game* games, GeneticAlgorithm& genAlgo, NeuralNetwork * nets[2], SDLWrapper& sdl, bool display)
{
	for(int i = 0; i < iterCnt; ++i)
	{
		runRound(games, genAlgo, nets, sdl, false);
	}
}

void displayGame(NeuralNetwork nets[2], SDLWrapper& sdl)
{
	Game game;
	while(!sdl.quit() && !game.end())
	{
		sdl.checkForEvent();
		SDL_Delay(1);
		game.draw();

		Move move;

		for(int i = 0; i < 2; ++i)
		{
			move = nets[i].calculateMove(game.playerInFov(i), game.bulletInFov(i),
					game.canShoot(i), game.currentFov(i));
			game.makeMove(i, move);
			game.move();
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
	//RandomGen::explicitSeed(time(NULL));

	GeneticAlgorithm genAlgo(55);
	auto& nnVals = genAlgo.GetGeneration();

	NeuralNetwork * nets[2];
	for (int i = 0; i < 2; ++i)
		nets[i] = new NeuralNetwork[gamesCnt];

	int iteration = 0;
	char iterChar[64];

	while (!sdl.quit())
	{
		sprintf(iterChar, "NN-Aim :) Iter: %d", iteration);
		sdl.setWinTitle(iterChar);

		int gameIndex = RandomGen::getInstance().intInRange(0, gamesCnt - 1);
		NeuralNetwork displayGameNets[2];
		displayGameNets[0].setWeights(nnVals[gameIndex].weights);
		displayGameNets[1].setWeights(nnVals[gamesCnt + gameIndex].weights);

		std::thread rounds(runRounds, 10, games, std::ref(genAlgo), nets, std::ref(sdl), false);
//		for (int i = 0; i < 10; ++i)
//		{
//			runRound(games, genAlgo, nets, sdl, false);
//		}

		displayGame(displayGameNets, sdl);

		rounds.join();

		runRound(games, genAlgo, nets, sdl, true, false);

		genAlgo.NextGenetarion();
		iteration++;
	}

	RandomGen::getInstance().gaussian(1, 1);
	for (int i = 0; i < 2; ++i)
		delete[] nets[i];
	delete[] games;
	return 0;
}
