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
};


class GeneticAlgorithm
{
public:
	GeneticAlgorithm(size_t chromosomeSize);

	GeneticAlgorithm(const GeneticAlgorithm& other) = delete;
	GeneticAlgorithm& operator = (const GeneticAlgorithm& other) = delete;

	~GeneticAlgorithm(){};

	std::vector<Chromosome>& GetGeneration()const;
	void NextGenetarion();

private:
	std::vector<Chromosome> currentGeneration;
};

#endif
