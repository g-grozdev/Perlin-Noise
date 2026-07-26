#include "NVector.h"

NVector::NVector(size_t _size) : size(_size), coords(std::vector<float>(1, 0.0f)) 
{
	if (_size == 0) throw std::invalid_argument("vector size cannot be less than 0");

	coords = std::vector<float>(_size, 0.0f);
}

NVector::NVector(std::initializer_list<float> init) : size(init.size())
{
	if (init.size() == 0) throw std::invalid_argument("vector size cannot be less than 0");

	coords = std::vector<float>(init.begin(), init.end());
}

NVector::NVector(const std::vector<float>& vec) : size(vec.size())
{
	if (vec.size() == 0) throw std::invalid_argument("vector size cannot be less than 0");

	coords = vec;
}

size_t NVector::get_size()
{
	return size;
}

float NVector::length()
{
	float res = 0.0f;
	for (int i = 0; i < size; i++) 
	{
		res += coords[i] * coords[i];
	}

	return std::sqrtf(res);
}

void NVector::normalize()
{
	float norm = length();

	if (norm == 0.0) throw std::logic_error("cannot normalize null vector");

	for (int i = 0; i < size; i++) 
	{
		coords[i] /= norm;
	}
}

void NVector::scale(float scalar)
{
	for (int i = 0; i < size; i++)
	{
		coords[i] *= scalar;
	}
}

float& NVector::operator[](size_t ind)
{
	if (ind >= size) throw std::out_of_range("index is out of range");

	return coords[ind];
}

const float& NVector::operator[](size_t ind) const
{
	if (ind >= size) throw std::out_of_range("index is out of range");

	return coords[ind];
}

NVector operator*(const NVector& vec, float scalar)
{
	NVector res = vec;
	res *= scalar;

	return res;
}

NVector operator*(float scalar, const NVector& vec)
{
	return vec * scalar;
}

NVector& NVector::operator*=(float scalar)
{
	(*this).scale(scalar);
	return *this;
}

NVector operator+(const NVector& vec_1, const NVector& vec_2)
{
	if (vec_1.size != vec_2.size) throw std::logic_error("cannot add two vectors of different sizes");

	NVector res = vec_1;

	res += vec_2;

	return res;
}

NVector& NVector::operator+=(const NVector& vec)
{
	if (vec.size != size) throw std::logic_error("cannot add two vectors of different sizes");

	for (int i = 0; i < size; i++)
	{
		coords[i] += vec[i];
	}

	return *this;
}

float operator*(const NVector& vec_1, const NVector& vec_2)
{
	if (vec_1.size != vec_2.size) throw std::logic_error("cannot multiply two vectors of different sizes");

	float res = 0.0f;
	for (int i = 0; i < vec_1.size; i++) 
	{
		res += vec_1[i] * vec_2[i];
	}

	return res;
}

std::ostream& operator<<(std::ostream& os, const NVector& vec)
{
	for (int i = 0; i < vec.size; i++) 
	{
		os << vec[i] << ' ';
	}
	return os;
}
