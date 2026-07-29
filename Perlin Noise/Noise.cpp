#include "Noise.h"

int Noise::pow(int base, int exp)
{
	int res = 1;
	for (int i = 0; i < exp; i++) 
	{
		res *= base;
	}
	return res;
}

float Noise::pow(float base, int exp)
{
	float res = 1.0f;
	for (int i = 0; i < exp; i++)
	{
		res *= base;
	}
	return res;
}

bool Noise::check_cache(const std::vector<float>& coords)
{
	bool res = true;
	int val = 0;
	for (int i = 0; i < size; i++) 
	{
		val = (int)std::floor(coords[i]);
		if (bottom_corner[i] != val) res = false;
		bottom_corner[i] = val;
		top_corner[i] = val + 1;
	}
	return res;
}

void Noise::calculate_vectors()
{
	for (int i = 0; i < num_vectors; i++) 
	{
		get_coordinates(i);
		vectors[i].normalize();
	}
}

void Noise::get_coordinates(int ind)
{
	unsigned int val = seed;
	int mask = 1;
	for (int i = 0; i < size; i++) 
	{
		if ((mask & ind) == mask) 
		{
			val ^= hash(top_corner[i]);
		}
		else 
		{
			val ^= hash(bottom_corner[i]);
		}
		mask <<= 1;
	}
	val ^= hash(val);

	for (int i = 0; i < size; i++) 
	{
		vectors[ind][i] = (val / 4294967295.0f) * 2.0f - 1.0f;
		val = hash(val);
	}
}

unsigned int Noise::hash(unsigned int x)
{
	x ^= 0x7feb352d;
	x ^= (x >> 15);
	x *= 0x846ca68b;
	x ^= (x >> 13);
	x ^= 0x92a6f463;
	x ^= (x >> 17);
	x *= 0xa87be915;
	return x;
}

void Noise::set_seed(int _seed)
{
	seed = _seed;
}

float Noise::smooth_step(float x)
{
	return 6 * pow(x, 5) - 15 * pow(x, 4) + 10 * pow(x, 3);
}

float Noise::lerp(float a, float b, float x)
{
	x = smooth_step(x);
	return a * (1 - x) + b * x;
}

float Noise::min(float a, float b)
{
	return a < b ? a : b;
}

float Noise::max(float a, float b)
{
	return a > b ? a : b;
}

Noise::Noise(size_t _size, int _seed) : seed(_seed), size(_size), gain(std::log(size)/std::log(1.75f)), num_vectors(pow(2, _size)), bottom_corner(std::vector<int>(_size)), 
top_corner(std::vector<int>(_size)), vectors(std::vector<NVector>(num_vectors, NVector(_size))), dot_products(std::vector<float>(num_vectors, 0)), current(_size), 
get_called(false)
{
	if (_size == 0) throw std::invalid_argument("vector size cannot be less than 0");
	if (size == 1) gain = 2.0f;
}

float Noise::get(const std::vector<float>& coords)
{
	if (coords.size() != size) throw std::invalid_argument("size of argument does not match size of noise");

	if (get_called) 
	{
		if (!check_cache(coords)) 
		{
			calculate_vectors();
		}
	}
	else 
	{
		check_cache(coords);
		calculate_vectors();
	}

	for (int i = 0; i < num_vectors; i++) 
	{
		int mask = 1;
		for (int j = 0; j < size; j++) 
		{
			if ((mask & i) == mask) 
			{
				current[j] = coords[j] - top_corner[j];
			}
			else 
			{
				current[j] = coords[j] - bottom_corner[j];
			}
			mask <<= 1;
		}
		dot_products[i] = current * vectors[i];
	}
	
	int temp_num_vectors = num_vectors;
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < temp_num_vectors; j += 2) 
		{
			dot_products[j / 2] = lerp(dot_products[j], dot_products[j + 1], coords[i] - bottom_corner[i]);
		}

		temp_num_vectors >>= 1;
	}

	get_called = true;
	return max(-1.0, min(dot_products[0] * gain, 1.0f));
}
