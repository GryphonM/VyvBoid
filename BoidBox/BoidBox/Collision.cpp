//------------------------------------------------------------------------------
//
// File Name:	Collision.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM150 Game Project
// Course:		GAM150
//
//------------------------------------------------------------------------------

#include "Collision.h"
#include "Vector2D.h"

bool CircleCircleCollision(const Vector2D& Circle1Pos, float Circle1Radius, const Vector2D& Circle2Pos, float Circle2Radius)
{
	float dist = Vector2D::DistanceSquared(Circle1Pos, Circle2Pos);
	float radiiSquared = (Circle1Radius + Circle2Radius) * (Circle1Radius + Circle2Radius);

	return dist < radiiSquared;
}
