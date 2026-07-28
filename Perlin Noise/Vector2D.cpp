#include "Vector2D.h"

Vector2D::Vector2D() : x(0.0f), y(0.0f) { }

Vector2D::Vector2D(float _x, float _y) : x(_x), y(_y) { }

float Vector2D::length()
{
	return std::sqrtf(x * x + y * y);
}

void Vector2D::normalize()
{
	float len = length();
	if (len == 0.0f) throw std::logic_error("cannot normalize null vector");
	x /= len;
	y /= len;
}

void Vector2D::scale(float scalar)
{
	x *= scalar;
	y *= scalar;
}

float Vector2D::get_x() const
{
	return x;
}

void Vector2D::set_x(float _x)
{
	x = _x;
}

float Vector2D::get_y() const
{
	return y;
}

void Vector2D::set_y(float _y)
{
	y = _y;
}

Vector2D& Vector2D::operator*=(float scalar)
{
	this->scale(scalar);
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	this->set_x(this->get_x() + vec.get_x());
	this->set_y(this->get_y() + vec.get_y());
	return *this;
}

Vector2D operator*(const Vector2D& vec, float scalar)
{
	Vector2D ans = vec;
	ans *= scalar;
	return ans;
}

Vector2D operator*(float scalar, const Vector2D& vec)
{
	return vec * scalar;
}

Vector2D operator+(const Vector2D& vec_1, const Vector2D& vec_2)
{
	Vector2D ans = vec_1;
	ans += vec_2;
	return ans;
}

float operator*(const Vector2D& vec_1, const Vector2D& vec_2)
{
	return vec_1.get_x() * vec_2.get_x() + vec_1.get_y() * vec_2.get_y();
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
	os << "( " << vec.get_x() << "; " << vec.get_y() << " )";
	return os;
}
