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
	Vector2D botLeft = squarePos - (scale2 / 2.0f);
	Vector2D topRight = squarePos + (scale2 / 2.0f);
	bool retVal = (point.X() < topRight.X() && point.X() > botLeft.X() &&
		point.Y() < topRight.Y() && point.Y() > botLeft.Y());
	return retVal;
}

bool CircleRectCollision(const Vector2D& CirclePos, float CircleRadius, const Vector2D& SquarePos, const Vector2D& SquareScale)
{
	Vector2D clampPoint = CirclePos;
	Vector2D botLeft = SquarePos - (SquareScale / 2);
	Vector2D topRight = SquarePos + (SquareScale / 2);

	if (clampPoint.x > topRight.x)
		clampPoint.x = topRight.x;
	else if (clampPoint.x < botLeft.x)
		clampPoint.x = botLeft.x;

	if (clampPoint.y > topRight.y)
		clampPoint.y = topRight.y;
	else if (clampPoint.y < botLeft.y)
		clampPoint.y = topRight.y;

	return Vector2D::DistanceSquared(clampPoint, CirclePos) < (CircleRadius * CircleRadius);
}
