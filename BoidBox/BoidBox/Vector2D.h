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
	float X();
	float Y();
	void X(const float newVal);
	void Y(const float newVal);
	
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