#pragma once
#include "Vector2D.h"

class Noise2D
{
	static Vector2D vectors[256];
	int seed;
	const float gain;
	int bottom_corner[2];
	int top_corner[2];
	int vectors_ind[4];
	float dot_products[4];
	Vector2D current;
	bool get_called;

	float pow(float base, int exp);
	bool check_cache(float x, float y);
	void calculate_vectors();
	void get_coordinates(int ind);
	unsigned int hash(unsigned int x);

	float smooth_step(float x);
	float lerp(float a, float b, float x);

	float min(float a, float b);
	float max(float a, float b);

public:
	Noise2D(int _seed);

	float get(float x, float y);
	void set_seed(int _seed);
};

