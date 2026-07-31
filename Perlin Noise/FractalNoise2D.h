#pragma once
#include <vector>
#include "Noise2D.h"

class FractalNoise2D
{
	int seed;
	int octaves_count;
	float frequency_factor;
	float amplitude_factor;
	std::vector<Noise2D> layers;
	std::vector<float> frequencies;
	std::vector<float> amplitudes;
	float total_amplitude;

	int hash(int x);
	float pow(float base, int exp);
	float normalizing_smooth_step(float x);

public:
	FractalNoise2D(int _seed);
	FractalNoise2D(int _seed, int _octaves, float _freq, float _amplitude);

	float get(float x, float y);
	void set_seed(int _seed);
};

