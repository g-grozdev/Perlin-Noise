#pragma once
#include "Vector3D.h"

class Noise3D
{
	static Vector3D vectors[512];
	int seed;
	const float gain;
	int bottom_corner[3];
	int top_corner[3];
	int vectors_ind[8];
	float dot_products[8];
	Vector3D current;
	bool get_called;

	float pow(float base, int exp);
	bool check_cache(float x, float y, float z);
	void calculate_vectors();
	void get_coordinates(int ind);
	unsigned int hash(unsigned int x);

	float smooth_step(float x);
	float lerp(float a, float b, float x);

	float min(float a, float b);
	float max(float a, float b);

public:
	Noise3D(int _seed);

	float get(float x, float y, float z);
	void set_seed(int _seed);
};

