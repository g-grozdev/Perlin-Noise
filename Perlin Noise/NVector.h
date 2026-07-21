#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <stdexcept>

class NVector
{
	const size_t size;
	std::vector<float> coords;

public:
	NVector(const size_t& _size);
	NVector(std::initializer_list<float> init);

	float length();
	void normalize();

	float& operator[](const size_t& ind);
	const float& operator[](const size_t& ind) const;

	friend NVector operator+(const NVector& vec_1, const NVector& vec_2);
	friend float operator*(const NVector& vec_1, const NVector& vec_2);

	friend std::ostream& operator<<(std::ostream& os, const NVector& vec);
};

