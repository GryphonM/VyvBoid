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

Vector2D::Vector2D(float x, float y) { vec.x = x; vec.y = y; }
Vector2D::Vector2D(DGL_Vec2* _vec) : vec(*_vec) {}

float Vector2D::X() const { return vec.x; }
float Vector2D::Y() const { return vec.y; }
void Vector2D::X(float x) { vec.x = x; }
void Vector2D::Y(float y) { vec.y = y; }

Vector2D::operator DGL_Vec2*() { return &vec; }

float Vector2D::DotProduct(Vector2D& other)
{
	return (vec.x * other.X()) + (vec.y * other.Y());
}

Vector2D Vector2D::operator+(Vector2D& rhs)
{
	return Vector2D(vec.x + rhs.X(), vec.y + rhs.Y());
}

Vector2D Vector2D::operator+(float rhs)
{
	return Vector2D(vec.x + rhs, vec.y + rhs);
}

Vector2D Vector2D::operator-(Vector2D& rhs)
{
	return Vector2D(vec.x - rhs.X(), vec.y - rhs.Y());
}

Vector2D Vector2D::operator-(float rhs)
{
	return Vector2D(vec.x - rhs, vec.y - rhs);
}

Vector2D Vector2D::operator*(float rhs)
{
	return Vector2D(vec.x * rhs, vec.y * rhs);
}

Vector2D Vector2D::operator*(Vector2D& rhs)
{
	return Vector2D(vec.x * rhs.X(), vec.y * rhs.Y());
}

Vector2D Vector2D::operator/(Vector2D& rhs)
{
	return Vector2D(vec.x / rhs.X(), vec.y / rhs.Y());
}

Vector2D Vector2D::operator/(float rhs)
{
	return Vector2D(vec.x / rhs, vec.y / rhs);
}
