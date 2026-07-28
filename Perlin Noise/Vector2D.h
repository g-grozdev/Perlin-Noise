#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>

class Vector2D
{
	float x;
	float y;

public:
	Vector2D();
	Vector2D(float _x, float _y);

	float length();
	void normalize();
	void scale(float scalar);

	float get_x() const;
	void set_x(float _x);
	float get_y() const;
	void set_y(float _y);

	friend Vector2D operator*(const Vector2D& vec, float scalar);
	friend Vector2D operator*(float scalar, const Vector2D& vec);
	Vector2D& operator*=(float scalar);

	friend Vector2D operator+(const Vector2D& vec_1, const Vector2D& vec_2);
	Vector2D& operator+=(const Vector2D& vec);
	friend float operator*(const Vector2D& vec_1, const Vector2D& vec_2);

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
};

