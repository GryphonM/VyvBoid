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
	float X() const;
	float Y() const;
	void X(const float newVal);
	void Y(const float newVal);

	operator DGL_Vec2*();
	
	float DotProduct(Vector2D& rhs);

	Vector2D operator+(Vector2D& rhs);
	Vector2D operator+(float rhs);
	Vector2D operator-(Vector2D& rhs);
	Vector2D operator-(float rhs);
	Vector2D operator*(float rhs);
	Vector2D operator*(Vector2D& rhs);
	Vector2D operator/(Vector2D& rhs);
	Vector2D operator/(float rhs);
private:
	DGL_Vec2 vec;
};

#endif