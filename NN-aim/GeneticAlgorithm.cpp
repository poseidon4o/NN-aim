#include "GeneticAlgorithm.h"

#include <cmath>
#include <random>
#include <limits>
#include <algorithm>

const float mu = 0.3;
const float sigma = 0.6;
const int maxMutations = 1;

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
		float a = -1.f, b = 1.f;
		for(size_t j = 0; j < chromosomeSize; ++j)
		{
			this->currentGeneration[i].weights[j] =
					(b - a) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + a;
		}
	}

	this->generationNumber = 1;
}


std::vector<Chromosome> GeneticAlgorithm::GetGeneration() const
{
	return this->currentGeneration;
}


void GeneticAlgorithm::AddChromosomeFitness(size_t chromosomeIndex, int fitness)
{
	this->currentGeneration[chromosomeIndex].fitness += fitness;
}


void GeneticAlgorithm::NextGenetarion()
{
	sort(this->currentGeneration.begin(), this->currentGeneration.end());

	std::vector<Chromosome> newGeneration(POPULATION_SIZE);

	for(size_t i = 0; i < POPULATION_SIZE; ++i)
	{
		newGeneration[i].weights.resize(this->chromosomeSize);
	}

	for(size_t i = 0; i < POPULATION_SIZE; ++i)
	{
		this->Crossover(this->Select(), this->Select(), newGeneration[i]);
	}

	this->currentGeneration = newGeneration;

	size_t numChromosomesToMutate = rand() % maxMutations;

	for(size_t i = 0; i < numChromosomesToMutate; ++i)
	{
		this->Mutate(rand() % POPULATION_SIZE);
	}

	++(this->generationNumber);
}


size_t GeneticAlgorithm::Select() const
{
	 std::vector<float> partialSums(POPULATION_SIZE);

	 partialSums[0] = this->currentGeneration[0].fitness;

	 for (size_t i = 1; i < POPULATION_SIZE; ++i)
	 {
		 partialSums[i] = partialSums[i - 1] + this->currentGeneration[i].fitness;
	 }

	 int x = rand() % static_cast<int>(partialSums[POPULATION_SIZE - 1]);

	 int res = 0;

	 for(int i = 0; i < POPULATION_SIZE && partialSums[i] < x; ++i)
	 {
	    res = i;
	 }

	 return res;
}


void GeneticAlgorithm::Mutate(size_t index)
{
	size_t numPositionsToMutate = rand() % 10;
	size_t currentPosition;
	//float currentSigma = sigma - (0.005 * this->generationNumber);
	//float currentMu = fabs(mu - (0.0001 * this->generationNumber));

	for(size_t i = 0; i < numPositionsToMutate; ++i)
	{
		currentPosition = rand() % (this->chromosomeSize);
		this->currentGeneration[index].weights[currentPosition] += generateGaussianNoise(mu, sigma);
	}
}


void GeneticAlgorithm::Crossover(size_t parentIndex1, size_t parentIndex2, Chromosome& child) const
{
	for(size_t i = 0; i < this->chromosomeSize; ++i)
	{
		child.weights[i] = 0.5 * (this->currentGeneration[parentIndex1].weights[i] +
								  this->currentGeneration[parentIndex1].weights[i]);
	}
	/*
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

	for(size_t i = crosspoint1; i < this->chromosomeSize; ++i)
	{
		child1.weights[i] = this->currentGeneration[parentIndex1].weights[i];
		child2.weights[i] = this->currentGeneration[parentIndex2].weights[i];
	}
	*/
}


double generateGaussianNoise(double mu, double sigma)
{
	const float epsilon = std::numeric_limits<double>::min();
	const float twoPi = 2.0*3.14159265358979323846;

	static float z0, z1;
	static bool generate;
	generate = !generate;

	if(!generate) return z1 * sigma + mu;

	float u1, u2;

	do
	{
	   u1 = rand() * (1.0f / RAND_MAX);
	   u2 = rand() * (1.0f / RAND_MAX);
	}while(u1 <= epsilon);

	z0 = sqrt(-2.0 * log(u1)) * cos(twoPi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(twoPi * u2);

	return z0 * sigma + mu;
}
