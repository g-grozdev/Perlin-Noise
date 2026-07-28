#include "Vector3D.h"

Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f) { }

Vector3D::Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

float Vector3D::length()
{
	return std::sqrtf(x * x + y * y + z * z);
}

void Vector3D::normalize()
{
	float len = length();
	if (len == 0.0f) throw std::logic_error("cannot normalize null vector");
	x /= len;
	y /= len;
	z /= len;
}

void Vector3D::scale(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

float Vector3D::get_x() const
{
	return x;
}

void Vector3D::set_x(float _x)
{
	x = _x;
}

float Vector3D::get_y() const
{
	return y;
}

void Vector3D::set_y(float _y)
{
	y = _y;
}

float Vector3D::get_z() const
{
	return z;
}

void Vector3D::set_z(float _z)
{
	z = _z;
}

Vector3D& Vector3D::operator*=(float scalar)
{
	this->scale(scalar);
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& vec)
{
	this->set_x(this->get_x() + vec.get_x());
	this->set_y(this->get_y() + vec.get_y());
	this->set_z(this->get_z() + vec.get_z());
	return *this;
}

Vector3D operator*(const Vector3D& vec, float scalar)
{
	Vector3D ans = vec;
	ans *= scalar;
	return ans;
}

Vector3D operator*(float scalar, const Vector3D& vec)
{
	return vec * scalar;
}

Vector3D operator+(const Vector3D& vec_1, const Vector3D& vec_2)
{
	Vector3D ans = vec_1;
	ans += vec_2;
	return ans;
}

float operator*(const Vector3D& vec_1, const Vector3D& vec_2)
{
	return vec_1.get_x() * vec_2.get_x() + vec_1.get_y() * vec_2.get_y() + vec_1.get_z() * vec_2.get_z();
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
	os << "( " << vec.get_x() << "; " << vec.get_y() << "; " << vec.get_z() << " )";
	return os;
}
