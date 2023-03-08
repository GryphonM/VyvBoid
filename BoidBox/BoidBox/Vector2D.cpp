//------------------------------------------------------------------------------
//
// File Name:	Vector2D.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Vector2D.h"
#include <string>
#include <cmath>

Vector2D::Vector2D(float _x, float _y) 
{
	x = _x;
	y = _y;
	vec.x = x; 
	vec.y = y; 
}
Vector2D::Vector2D(DGL_Vec2* _vec) : vec(*_vec) \
{
	x = vec.x;
	y = vec.y;
}
Vector2D::Vector2D(DGL_Vec2 _vec) : vec(_vec) 
{
	x = vec.x;
	y = vec.y;
}
Vector2D& Vector2D::operator=(const Vector2D& rhs) 
{
	x = rhs.x;
	y = rhs.y;
	return *this; 
}

float Vector2D::X() const { return x; }
float Vector2D::Y() const { return y; }
float& Vector2D::X() { return x; }
float& Vector2D::Y() { return y; }
void Vector2D::X(float _x) { x = _x; }
void Vector2D::Y(float _y) { y = _y; }

Vector2D::operator DGL_Vec2*() 
{
	vec.x = x;
	vec.y = y;
	return &vec;
}

float Vector2D::DotProduct(Vector2D& other) const 
{ 
	return (x * other.x) + (y * other.y); 
}

float Vector2D::DistanceSquared(Vector2D const& lhs, Vector2D const& rhs)
{
	float diffX = rhs.x - lhs.x;
	float diffY = rhs.y - lhs.y;
	return abs((diffX * diffX) + (diffY * diffY));
}

float Vector2D::Distance(Vector2D const& lhs, Vector2D const& rhs) { 
	return sqrt(DistanceSquared(lhs, rhs)); 
}

float Vector2D::MagnitudeSquared() const { 
	return abs((x * x) + (y * y));
}
float Vector2D::Magnitude() const { 
	return sqrt(MagnitudeSquared()); 
}
Vector2D Vector2D::Normalized() const 
{ 
	if (x == 0 && y == 0)
		return Vector2D();
	return *this / Magnitude(); 
}

bool Vector2D::operator==(const Vector2D& rhs) const { 
	return x == rhs.x && y == rhs.y; 
}
bool Vector2D::operator!=(const Vector2D& rhs) const { 
	return !(*this == rhs); 
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const { 
	return Vector2D(x + rhs.x, y + rhs.y); 
}
Vector2D& Vector2D::operator+=(const Vector2D& rhs) 
{ 
	x += rhs.x; 
	y += rhs.y; 
	return *this; 
}
Vector2D Vector2D::operator+(float rhs) const { 
	return Vector2D(x + rhs, y + rhs); 
}
Vector2D& Vector2D::operator+=(float rhs) 
{ 
	x += rhs; 
	y += rhs; 
	return *this; 
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const { 
	return Vector2D(x - rhs.x, y - rhs.y); 
}
Vector2D& Vector2D::operator-=(const Vector2D& rhs) 
{ 
	x -= rhs.x; 
	y -= rhs.y; 
	return *this; 
}
Vector2D Vector2D::operator-(float rhs) const { 
	return Vector2D(x - rhs, y - rhs); 
}
Vector2D& Vector2D::operator-=(float rhs) 
{ 
	x -= rhs; 
	y -= rhs; 
	return *this; 
}

Vector2D Vector2D::operator*(const Vector2D& rhs) const { 
	return Vector2D(x * rhs.x, y * rhs.y); 
}
Vector2D& Vector2D::operator*=(const Vector2D& rhs) 
{ 
	x *= rhs.x; 
	y *= rhs.y; 
	return *this; 
}
Vector2D Vector2D::operator*(float rhs) const { 
	return Vector2D(x * rhs, y * rhs); 
}
Vector2D& Vector2D::operator*=(float rhs) 
{ 
	x *= rhs; 
	y *= rhs; 
	return *this; 
}

Vector2D Vector2D::operator/(const Vector2D& rhs) const { 
	return Vector2D(x / rhs.x, y / rhs.y); 
}
Vector2D& Vector2D::operator/=(const Vector2D& rhs) 
{ 
	x /= rhs.x; 
	y /= rhs.y; 
	return *this; 
}
Vector2D Vector2D::operator/(float rhs) const { 
	return Vector2D(x / rhs, y / rhs); 
}
Vector2D& Vector2D::operator/=(float rhs) 
{ 
	x /= rhs; 
	y /= rhs; 
	return *this; 
}
