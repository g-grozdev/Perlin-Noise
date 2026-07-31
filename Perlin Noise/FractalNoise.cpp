#include "FractalNoise.h"

int FractalNoise::hash(int x)
{
	x ^= 0xafe3352f;
	x ^= (x >> 15);
	x *= 0xa4fce63d;
	x ^= (x >> 13);
	x ^= 0xa2a6b477;
	x ^= (x >> 17);
	x *= 0xac7b1d19;
	return x;
}

float FractalNoise::pow(float base, int exp)
{
	float res = 1.0f;
	for (int i = 0; i < exp; i++) 
	{
		res *= base;
	}
	return res;
}

float FractalNoise::normalizing_smooth_step(float x)
{
	return 2 * (3 * pow(0.5f * x + 0.5f, 2) - 2 * pow(0.5f * x + 0.5f, 3) - 0.5f);
}

FractalNoise::FractalNoise(size_t _size, int _seed) : seed(_seed), size(_size), octaves_count(3), frequency_factor(2.0f), amplitude_factor(0.5f),
layers(std::vector<Noise>(3, Noise(_size, _seed))), frequencies({1.0f, 2.0f, 4.0f}), amplitudes({1.0f, 0.5f, 0.25f}), total_amplitude(1.75f) 
{
	if (_size == 0) throw std::invalid_argument("cannot have size of 0");

	int temp_seed = seed;
	for (int i = 0; i < octaves_count; i++) 
	{
		layers[i].set_seed(temp_seed);
		temp_seed = hash(temp_seed);
	}
}

FractalNoise::FractalNoise(size_t _size, int _seed, int _octaves, float _freq, float _amplitude) : seed(_seed), size(_size), octaves_count(_octaves), 
frequency_factor(_freq), amplitude_factor(_amplitude), layers(std::vector<Noise>(octaves_count, Noise(_size, _seed))), frequencies(std::vector<float>(_octaves, 1.0f)),
amplitudes(std::vector<float>(_octaves, 1.0f)), total_amplitude(1.0f) 
{
	if (_size == 0) throw std::invalid_argument("cannot have size of 0");
	if (_octaves == 0) throw std::invalid_argument("cannot have 0 octaves");
	if (_freq == 0.0f) throw std::invalid_argument("cannot have frequency of 0.0");
	if (_amplitude == 0.0f) throw std::invalid_argument("cannot have amplitude of 0.0");

	int temp_seed = seed;
	float curr_frequency = 1.0f;
	float curr_amplitude = 1.0f;
	float composite_amplitude = 0.0f;
	for (int i = 0; i < octaves_count; i++)
	{
		layers[i].set_seed(temp_seed);
		temp_seed = hash(temp_seed);

		frequencies[i] = curr_frequency;
		amplitudes[i] = curr_amplitude;

		composite_amplitude += curr_amplitude;
		
		curr_frequency *= frequency_factor;
		curr_amplitude *= amplitude_factor;
	}

	total_amplitude = composite_amplitude;
}

float FractalNoise::get(const std::vector<float>& coords)
{
	if (coords.size() != size) throw std::invalid_argument("size of argument does not match size of noise");
	
	float res = 0.0f;
	std::vector<float> temp_coords = coords;
	for (int i = 0; i < octaves_count; i++) 
	{
		temp_coords = coords;
		for (int j = 0; j < size; j++) 
		{
			temp_coords[j] *= frequencies[i];
		}
		res += layers[i].get(temp_coords) * amplitudes[i];
	}
	return normalizing_smooth_step(res /= total_amplitude);
}

void FractalNoise::set_seed(int _seed)
{
	seed = _seed;
	int temp_seed = seed;
	for (int i = 0; i < octaves_count; i++) 
	{
		layers[i].set_seed(temp_seed);
		temp_seed = hash(temp_seed);
	}
}
