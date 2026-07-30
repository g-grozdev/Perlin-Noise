#pragma once
#include "Noise.h"

class FractalNoise
{
	int seed;
	size_t size;
	int octaves_count;
	float frequency_factor;
	float amplitude_factor;
	std::vector<Noise> layers;
	std::vector<float> frequencies;
	std::vector<float> amplitudes;
	float total_amplitude;

	int hash(int x);
	float pow(float base, int exp);
	float normalizing_smooth_step(float x);

public:
	FractalNoise(size_t _size, int _seed);
	FractalNoise(size_t _size, int _seed, int _octaves, float _freq, float _scale);

	float get(const std::vector<float>& coords);
	void set_seed(int _seed);
};

