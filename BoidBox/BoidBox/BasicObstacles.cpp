//------------------------------------------------------------------------------
//
// File Name:	BasicObstacles.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "Mesh.h"
#include "Transform.h"
#include "Vector2D.h"

struct Obstacles
{
	Transform* transform;

	Mesh* mesh;
};

Obstacles* CreateObstacles(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	Obstacles* obstacles = new Obstacles;
	if (obstacles)
	{
		obstacles->mesh = SquareMesh(xHalfSize, yHalfSize, uSize, vSize, "FirstObstacles");
		obstacles->transform = CreateTransform(Vector2D(-300, -250), Vector2D(50, 100));
		return obstacles;
	}
	else
	{
		return NULL;
	}
}

void DrawObstacles(Obstacles* obstacles)
{
	RenderMesh(obstacles->mesh, obstacles->transform);
}

void DestroyObstacles(Obstacles* obstacles)
{
	if (obstacles)
	{
		if (obstacles->transform)
			DeleteTransform(obstacles->transform);
		if (obstacles->mesh)
			freeMesh(&obstacles->mesh);
		delete obstacles;
		obstacles = NULL;
	}
}
