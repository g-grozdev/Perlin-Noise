#include "FractalNoise2D.h"

int FractalNoise2D::hash(int x)
{
	x ^= 0x1ff39523;
	x ^= (x >> 15);
	x *= 0xa4fae63f;
	x ^= (x >> 13);
	x ^= 0xa7a6c475;
	x ^= (x >> 17);
	x *= 0xfc3b1d15;
	return x;
}

float FractalNoise2D::pow(float base, int exp)
{
    float res = 1.0f;
    for (int i = 0; i < exp; i++) 
    {
        res *= base;
    }
    return res;
}

float FractalNoise2D::normalizing_smooth_step(float x)
{
	return 2 * (3 * pow(0.5f * x + 0.5f, 2) - 2 * pow(0.5f * x + 0.5f, 3) - 0.5f);
}

FractalNoise2D::FractalNoise2D(int _seed) : seed(_seed), octaves_count(3), frequency_factor(2.0f), amplitude_factor(0.5f), layers(std::vector<Noise2D>(3, Noise2D(_seed))),
frequencies({ 1.0f, 2.0f, 4.0f }), amplitudes({ 1.0f, 0.5f, 0.25f }), total_amplitude(1.75f)
{
	int temp_seed = seed;
	for (int i = 0; i < octaves_count; i++)
	{
		layers[i].set_seed(temp_seed);
		temp_seed = hash(temp_seed);
	}
}

FractalNoise2D::FractalNoise2D(int _seed, int _octaves, float _freq, float _amplitude) : seed(_seed), octaves_count(_octaves), frequency_factor(_freq),
amplitude_factor(_amplitude), layers(std::vector<Noise2D>(octaves_count, Noise2D(_seed))), frequencies(std::vector<float>(_octaves, 1.0f)),
amplitudes(std::vector<float>(_octaves, 1.0f)), total_amplitude(1.0f)
{
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

float FractalNoise2D::get(float x, float y)
{
	float res = 0.0f;
	float temp_x = x;
	float temp_y = y;
	for (int i = 0; i < octaves_count; i++)
	{
		temp_x = x * frequencies[i];
		temp_y = y * frequencies[i];

		res += layers[i].get(temp_x, temp_y) * amplitudes[i];
	}
	return normalizing_smooth_step(res /= total_amplitude);
}

void FractalNoise2D::set_seed(int _seed)
{
	seed = _seed;
	int temp_seed = seed;
	for (int i = 0; i < octaves_count; i++)
	{
		layers[i].set_seed(temp_seed);
		temp_seed = hash(temp_seed);
	}
}
