//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Transform.h"

struct Transform
{
	Vector2D position;
	Vector2D scale;
	float rotation;
};

Transform* CreateTransform(Vector2D position, Vector2D scale, float rotation)
{
	Transform* transform = new Transform;
	transform->position = position;
	transform->scale = scale;
	transform->rotation = rotation;
	return transform;
}

void DeleteTransform(Transform* transform) { delete transform; }

Vector2D TransformGetPosition(Transform* transform) { return transform->position; }
Vector2D TransformGetScale(Transform* transform) { return transform->scale; }
Vector2D TransformGetRotation(Transform* transform) { return transform->rotation; }

void TransformSetPosition(Transform* transform, Vector2D& position) { transform->position = position; }
void TransformSetScale(Transform* transform, Vector2D& scale) { transform->scale = scale; }
void TransformSetRotation(Transform* transform, float rotation) { transform->rotation = rotation; }

