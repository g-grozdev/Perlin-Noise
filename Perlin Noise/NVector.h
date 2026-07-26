#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <stdexcept>

class NVector
{
	size_t size;
	std::vector<float> coords;

public:
	NVector();
	NVector(size_t _size);
	NVector(std::initializer_list<float> init);
	NVector(const std::vector<float>& init);

	size_t get_size();

	float length();
	void normalize();
	void scale(float scalar);

	float& operator[](size_t ind);
	const float& operator[](size_t ind) const;

	friend NVector operator*(const NVector& vec, float scalar);
	friend NVector operator*(float scalar, const NVector& vec);
	NVector& operator*=(float scalar);

	friend NVector operator+(const NVector& vec_1, const NVector& vec_2);
	NVector& operator+=(const NVector& vec);
	friend float operator*(const NVector& vec_1, const NVector& vec_2);

	friend std::ostream& operator<<(std::ostream& os, const NVector& vec);
};

