#include "GeneticAlgorithm.h"

#include <cmath>
#include <random>
#include <limits>
#include <algorithm>


bool Chromosome::operator < (const Chromosome& other) const
{
	return this->fitness > other.fitness;
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

	for(size_t i = 0; i < POPULATION_SIZE; ++i)
	{
		newGeneration[i].weights.resize(this->chromosomeSize);
	}

	for(size_t i = 0; i < POPULATION_SIZE; i += 2)
	{
		this->Crossover(this->Select(), this->Select(), newGeneration[i], newGeneration[i+1]);
	}

	this->currentGeneration = newGeneration;

	size_t numChromosomesToMutate = rand() % 10;

	for(size_t i = 0; i < numChromosomesToMutate; ++i)
	{
		this->Mutate(rand() % POPULATION_SIZE);
	}

}


size_t GeneticAlgorithm::Select() const
{
	 std::vector<float> partialSums(POPULATION_SIZE);

	 partialSums[0] = this->currentGeneration[0].fitness;

	 for (size_t i = 1; i < POPULATION_SIZE; ++i)
	 {
		 partialSums[i] = partialSums[i - 1] + this->currentGeneration[i].fitness;
	 }

	 int x = rand();
	 int res = 0;

	 for(int i = 0; i < POPULATION_SIZE && partialSums[i] < x; ++i)
	 {
	    res = i;
	 }

	 return res;
}


void GeneticAlgorithm::Mutate(size_t index)
{
	//size_t numPositionsToMutate = rand() % (this->chromosomeSize), currentPosition;

	//for(size_t i = 0; i < numPositionsToMutate; ++i)
	//{
	size_t currentPosition = rand() % (this->chromosomeSize);
	this->currentGeneration[index].weights[currentPosition] += generateGaussianNoise(0.1, 0.2);
	//}
}


void GeneticAlgorithm::Crossover(size_t parentIndex1, size_t parentIndex2,
								 Chromosome& child1, Chromosome& child2) const
{
	size_t crosspoint1, crosspoint2;

	crosspoint1 = rand() % (this->chromosomeSize);

	do{
		crosspoint2 = rand() % (this->chromosomeSize);
	}while(crosspoint1 == crosspoint2);

	if(crosspoint1 > crosspoint2)
	{
		std::swap(crosspoint1, crosspoint2);
	}

	for(size_t i = 0; i < crosspoint1; ++i)
	{
		child1.weights[i] = this->currentGeneration[parentIndex1].weights[i];
		child2.weights[i] = this->currentGeneration[parentIndex2].weights[i];
	}

	for(size_t i = crosspoint1; i < crosspoint2; ++i)
	{
		child1.weights[i] = this->currentGeneration[parentIndex2].weights[i];
		child2.weights[i] = this->currentGeneration[parentIndex1].weights[i];
	}

	for(size_t i = crosspoint2; i < this->chromosomeSize; ++i)
	{
		child1.weights[i] = this->currentGeneration[parentIndex1].weights[i];
		child2.weights[i] = this->currentGeneration[parentIndex2].weights[i];
	}

}


double generateGaussianNoise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double twoPi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if(!generate) return z1 * sigma + mu;

	double u1, u2;

	do
	{
	   u1 = rand() * (1.0 / RAND_MAX);
	   u2 = rand() * (1.0 / RAND_MAX);
	 }while(u1 <= epsilon);

	z0 = sqrt(-2.0 * log(u1)) * cos(twoPi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(twoPi * u2);

	return z0 * sigma + mu;
}
