//------------------------------------------------------------------------------
//
// File Name:	Collision.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM150 Game Project
// Course:		GAM150
//
//------------------------------------------------------------------------------

#pragma once
class Vector2D;

bool CircleCircleCollision(const Vector2D& Circle1Pos, float Circle1Radius, const Vector2D& Circle2Pos, float Circle2Radius);
bool PointSquareCollision(const Vector2D& point, const Vector2D& squarePos, const Vector2D& scale2);
