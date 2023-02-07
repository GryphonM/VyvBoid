//------------------------------------------------------------------------------
//
// File Name:	Vector2D.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "DGL.h"

class Vector2D
{
public:
	Vector2D(float x = 0.0f, float y = 0.0f);
	Vector2D(DGL_Vec2* vec);
	Vector2D(DGL_Vec2 vec);
	float X() const;
	float Y() const;
	void X(const float newVal);
	void Y(const float newVal);

	operator DGL_Vec2*();
	
	float DotProduct(Vector2D& rhs) const;
	static float DistanceSquared(Vector2D const& lhs, Vector2D const& rhs);
	static float Distance(Vector2D const& lhs, Vector2D const& rhs);
	float MagnitudeSquared() const;
	float Magnitude() const;
	Vector2D Normalized() const;

	Vector2D operator+(Vector2D& rhs) const;
	Vector2D& operator+=(Vector2D& rhs);
	Vector2D operator+(float rhs) const;
	Vector2D& operator+=(float rhs);
	Vector2D operator-(Vector2D& rhs) const;
	Vector2D& operator-=(Vector2D& rhs);
	Vector2D operator-(float rhs) const;
	Vector2D& operator-=(float rhs);
	Vector2D operator*(Vector2D& rhs) const;
	Vector2D& operator*=(Vector2D& rhs);
	Vector2D operator*(float rhs) const;
	Vector2D& operator*=(float rhs);
	Vector2D operator/(Vector2D& rhs) const;
	Vector2D& operator/=(Vector2D& rhs);
	Vector2D operator/(float rhs) const;
	Vector2D& operator/=(float rhs);
private:
	DGL_Vec2 vec;
};

#endif