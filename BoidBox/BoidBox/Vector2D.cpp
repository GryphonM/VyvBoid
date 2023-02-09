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

Vector2D::Vector2D(float x, float y) 
{ 
	vec.x = x; 
	vec.y = y; 
}
Vector2D::Vector2D(DGL_Vec2* _vec) : vec(*_vec) {}
Vector2D::Vector2D(DGL_Vec2 _vec) : vec(_vec) {}
Vector2D& Vector2D::operator=(const Vector2D& rhs) 
{ 
	vec.x = rhs.vec.x; 
	vec.y = rhs.vec.y; 
	return *this; 
}

float Vector2D::X() const { return vec.x; }
float Vector2D::Y() const { return vec.y; }
void Vector2D::X(float x) { vec.x = x; }
void Vector2D::Y(float y) { vec.y = y; }

Vector2D::operator DGL_Vec2*() { return &vec; }

float Vector2D::DotProduct(Vector2D& other) const { 
	return (vec.x * other.X()) + (vec.y * other.Y()); 
}

float Vector2D::DistanceSquared(Vector2D const& lhs, Vector2D const& rhs)
{
	float diffX = rhs.vec.x - lhs.vec.x;
	float diffY = rhs.vec.y - lhs.vec.y;
	return (diffX * diffX) + (diffY * diffY);
}

float Vector2D::Distance(Vector2D const& lhs, Vector2D const& rhs) { 
	return sqrt(DistanceSquared(lhs, rhs)); 
}

float Vector2D::MagnitudeSquared() const { 
	return (vec.x * vec.x) + (vec.y * vec.y); 
}
float Vector2D::Magnitude() const { 
	return sqrt(MagnitudeSquared()); 
}
Vector2D Vector2D::Normalized() const 
{ 
	if (vec.x == 0 && vec.y == 0)
		return Vector2D();
	return *this / Magnitude(); 
}

bool Vector2D::operator==(const Vector2D& rhs) const { 
	return vec.x == rhs.vec.x && vec.y == rhs.vec.y; 
}
bool Vector2D::operator!=(const Vector2D& rhs) const { 
	return !(*this == rhs); 
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const { 
	return Vector2D(vec.x + rhs.vec.x, vec.y + rhs.vec.y); 
}
Vector2D& Vector2D::operator+=(const Vector2D& rhs) 
{ 
	vec.x += rhs.vec.x; 
	vec.y += rhs.vec.y; 
	return *this; 
}
Vector2D Vector2D::operator+(float rhs) const { 
	return Vector2D(vec.x + rhs, vec.y + rhs); 
}
Vector2D& Vector2D::operator+=(float rhs) 
{ 
	vec.x += rhs; 
	vec.y += rhs; 
	return *this; 
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const { 
	return Vector2D(vec.x - rhs.vec.x, vec.y - rhs.vec.y); 
}
Vector2D& Vector2D::operator-=(const Vector2D& rhs) 
{ 
	vec.x -= rhs.vec.x; 
	vec.y -= rhs.vec.y; 
	return *this; 
}
Vector2D Vector2D::operator-(float rhs) const { 
	return Vector2D(vec.x - rhs, vec.y - rhs); 
}
Vector2D& Vector2D::operator-=(float rhs) 
{ 
	vec.x -= rhs; 
	vec.y -= rhs; 
	return *this; 
}

Vector2D Vector2D::operator*(const Vector2D& rhs) const { 
	return Vector2D(vec.x * rhs.vec.x, vec.y * rhs.vec.y); 
}
Vector2D& Vector2D::operator*=(const Vector2D& rhs) 
{ 
	vec.x *= rhs.vec.x; 
	vec.y *= rhs.vec.y; 
	return *this; 
}
Vector2D Vector2D::operator*(float rhs) const { 
	return Vector2D(vec.x * rhs, vec.y * rhs); 
}
Vector2D& Vector2D::operator*=(float rhs) 
{ 
	vec.x *= rhs; 
	vec.y *= rhs; 
	return *this; 
}

Vector2D Vector2D::operator/(const Vector2D& rhs) const { 
	return Vector2D(vec.x / rhs.vec.x, vec.y / rhs.vec.y); 
}
Vector2D& Vector2D::operator/=(const Vector2D& rhs) 
{ 
	vec.x /= rhs.vec.x; 
	vec.y /= rhs.vec.y; 
	return *this; 
}
Vector2D Vector2D::operator/(float rhs) const { 
	return Vector2D(vec.x / rhs, vec.y / rhs); 
}
Vector2D& Vector2D::operator/=(float rhs) 
{ 
	vec.x /= rhs; 
	vec.y /= rhs; 
	return *this; 
}
