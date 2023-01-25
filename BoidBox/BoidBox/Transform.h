//------------------------------------------------------------------------------
//
// File Name:	Transform.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
struct Transform;

#if 0
struct Transform
{
	Vector2D position;
	Vector2D scale;
	float rotation;
};
#endif

Transform* CreateTransform(Vector2D position = Vector2D(0, 0), Vector2D scale = Vector2D(1.0f, 1.0f), float rotation = 0.0f);
void DeleteTransform(Transform* transform);

Vector2D TransformGetPosition(Transform* transform);
Vector2D TransformGetScale(Transform* transform);
Vector2D TransformGetRotation(Transform* transform);

Vector2D TransformSetPosition(Transform* transform, Vector2D& position);
Vector2D TransformSetScale(Transform* transform, Vector2D& scale);
Vector2D TransformSetRotation(Transform* transform, float rotation);

#endif