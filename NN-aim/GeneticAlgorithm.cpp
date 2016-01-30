#include "GeneticAlgorithm.h"

#include <random>
#include <algorithm>


bool Chromosome::operator < (const Chromosome& other) const
{
	return this->fitness < other.fitness;
}


GeneticAlgorithm::GeneticAlgorithm(size_t chromosomeSize)
{
	this->chromosomeSize = chromosomeSize;

	this->currentGeneration.resize(POPULATION_SIZE);

	for(size_t i = 0; i < POPULATION_SIZE; ++i)
	{
		this->currentGeneration[i].weights = std::vector<float>(this->chromosomeSize);
		float a = 0.f, b = 1.f;
		for(size_t j = 0; j < chromosomeSize; ++j)
		{
			this->currentGeneration[i].weights[j] =
					(b - a) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + a;
		}
	}
}


std::vector<Chromosome> GeneticAlgorithm::GetGeneration() const
{
	return this->currentGeneration;
}


void GeneticAlgorithm::SetChromosomeFitness(size_t chromosomeIndex, float fitness)
{
	this->currentGeneration[chromosomeIndex].fitness = fitness;
}


void GeneticAlgorithm::NextGenetarion()
{
	sort(this->currentGeneration.begin(), this->currentGeneration.end());

	std::vector<Chromosome> newGeneration(POPULATION_SIZE);

}


void GeneticAlgorithm::Crossover(size_t parentIndex1, size_t parentIndex2,
								 Chromosome& child1, Chromosome& child2)
{
	size_t crosspoint1, crosspoint2;

	crosspoint1 = rand() % (this->chromosomeSize);

	do{
		crosspoint2 = rand() % (this->chromosomeSize);
	}while(crosspoint1 == crosspoint2);

	for(size_t  i  = 0; i < crosspoint1; ++i)
	{
		child1.weights[i] = this->currentGeneration[parentIndex1].weights[i];
		child2.weights[i] = this->currentGeneration[parentIndex2].weights[i];
	}

	for(size_t  i  = crosspoint1; i < crosspoint2; ++i)
	{
		child1.weights[i] = this->currentGeneration[parentIndex2].weights[i];
		child2.weights[i] = this->currentGeneration[parentIndex1].weights[i];
	}

	for(size_t  i  = crosspoint2; i < this->chromosomeSize; ++i)
	{
		child1.weights[i] = this->currentGeneration[parentIndex1].weights[i];
		child2.weights[i] = this->currentGeneration[parentIndex2].weights[i];
	}

}
