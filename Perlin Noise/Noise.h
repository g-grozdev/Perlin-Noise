#pragma once
#include "NVector.h"

class Noise
{
	int seed;
	size_t size;
	float gain;
	int num_vectors;
	std::vector<int> bottom_corner;
	std::vector<int> top_corner;
	std::vector<NVector> vectors;
	std::vector<float> dot_products;
	NVector current;
	bool get_called;

	int pow(int base, int exp);
	float pow(float base, int exp);
	bool check_cache(const std::vector<float>& coords);
	void calculate_vectors();
	void get_coordinates(int ind);

	float smooth_step(float x);
	float lerp(float a, float b, float x);

	float min(float a, float b);
	float max(float a, float b);

public:
	Noise(size_t _size, int seed);

	float get(const std::vector<float>& coords);
	unsigned int hash(unsigned int x);

	void set_seed(int _seed);
};

