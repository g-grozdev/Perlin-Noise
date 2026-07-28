#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>

class Vector3D
{
	float x;
	float y;
	float z;

public:
	Vector3D();
	Vector3D(float _x, float _y, float _z);

	float length();
	void normalize();
	void scale(float scalar);

	float get_x() const;
	void set_x(float _x);
	float get_y() const;
	void set_y(float _y);
	float get_z() const;
	void set_z(float _z);

	friend Vector3D operator*(const Vector3D& vec, float scalar);
	friend Vector3D operator*(float scalar, const Vector3D& vec);
	Vector3D& operator*=(float scalar);

	friend Vector3D operator+(const Vector3D& vec_1, const Vector3D& vec_2);
	Vector3D& operator+=(const Vector3D& vec);
	friend float operator*(const Vector3D& vec_1, const Vector3D& vec_2);

	friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec);
};

