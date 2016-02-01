#include "RandomGenerator.h"

using namespace std;

static bool isSeeded = false;
static uint32_t seed = 0;


void RandomGen::explicitSeed(uint32_t seed)
{
	isSeeded = true;
	::seed = seed;
}

RandomGen & RandomGen::getInstance()
{
	static RandomGen gen(isSeeded ? seed : random_device()());
	return gen;
}

double RandomGen::gaussian(double mean, double deviation)
{
	normal_distribution<double> dist(mean, deviation);
	return dist(eng);
}

double RandomGen::uniformDouble(double low, double high)
{
	uniform_real_distribution<double> dist(low, high);
	return dist(eng);
}

RandomGen::RandomGen(std::uint32_t seed): eng(seed)
{
}
