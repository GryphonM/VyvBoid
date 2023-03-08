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

bool PointSquareCollision(const Vector2D& point, const Vector2D& squarePos, const Vector2D& scale2)
{
	Vector2D topRight = squarePos + (scale2 / 2.0f);
	bool retVal = (point.X() < topRight.X() && point.X() > -topRight.X() &&
		point.Y() < topRight.Y() && point.Y() > -topRight.Y());
	return retVal;
}