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
	Vector2D topLeft(SquarePos.X() - (SquareScale.X() / 2), SquarePos.Y() - (SquareScale.Y() / 2));
	Vector2D botRight(SquarePos.X() + (SquareScale.X() / 2), SquarePos.Y() + (SquareScale.Y() / 2));

	if (clampPoint.X() > botRight.X())
		clampPoint.X(botRight.X());
	else if (clampPoint.X() < topLeft.X())
		clampPoint.X(topLeft.X());

	if (clampPoint.Y() > topLeft.Y())
		clampPoint.Y(topLeft.Y());
	else if (clampPoint.Y() < botRight.Y())
		clampPoint.Y(botRight.Y());

	return Vector2D::DistanceSquared(clampPoint, CirclePos) < (CircleRadius * CircleRadius);
}
