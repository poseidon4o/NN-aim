#include "GeneticAlgorithm.h"
#include <random>

GeneticAlgorithm::GeneticAlgorithm(size_t chromosomeSize)
{
	currentGeneration.resize(POPULATION_SIZE);

	for(size_t i = 0; i < POPULATION_SIZE; ++i)
	{
		currentGeneration[i].weights = std::vector<float>(chromosomeSize);
		float a = 0.f, b = 1.f;
		for(size_t j = 0; j < chromosomeSize; ++j)
		{
			currentGeneration[i].weights[j] =
					(b - a) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + a;
		}
	}
}




