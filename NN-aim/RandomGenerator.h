#pragma once

#include <random>
#include <cstdint>


class RandomGen {
	std::default_random_engine eng;

public:
	/// should be called before first call to getInstance()!
	static void explicitSeed(std::uint32_t seed);

	static RandomGen & getInstance();

	double gaussian(double mean, double deviation);
	double uniformDouble(double low = 0., double high = 1.);
	int intInRange(int min, int max);


	RandomGen(const RandomGen &) = delete;
	RandomGen & operator=(const RandomGen &) = delete;

private:
	RandomGen(std::uint32_t seed);
};