#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#define POPULATION_SIZE 50

#include <vector>
#include <cstdlib>


struct Chromosome
{
	std::vector<float> weights;
	float fitness;

	Chromosome(){fitness = 0.f;};

	bool operator < (const Chromosome& other) const;
};


class GeneticAlgorithm
{
public:
	GeneticAlgorithm(size_t chromosomeSize);

	GeneticAlgorithm(const GeneticAlgorithm& other) = delete;
	GeneticAlgorithm& operator = (const GeneticAlgorithm& other) = delete;

	~GeneticAlgorithm(){};

	std::vector<Chromosome> GetGeneration() const;
	void SetChromosomeFitness(size_t chromosomeIndex, float fitness);
	void NextGenetarion();

private:
	size_t Select() const;
	void Mutate(size_t index);
	void Crossover(size_t parentIndex1, size_t parentIndex2, Chromosome& child1, Chromosome& child2)const;

	std::vector<Chromosome> currentGeneration;

	size_t chromosomeSize;
};

double generateGaussianNoise(double mu, double sigma);

#endif
