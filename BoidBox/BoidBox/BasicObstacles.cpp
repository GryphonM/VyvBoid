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
#include "DGL.h"

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
		obstacles->transform = CreateTransform(Vector2D(-300, -250), Vector2D(25, 40));
		return obstacles;
	}
	else
	{
		return NULL;
	}
}

/*Vector2D GetObstaclePosition(Obstacles* obstacle)
{
	if (obstacle)
	{
		Vector2D position = TransformGetPosition(obstacle->transform);
		return position;
	}
	else
		return Vector2D(0, 0);
}*/

void DrawObstacles(Obstacles* obstacles)
{
	DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
	RenderMesh(obstacles->mesh, obstacles->transform);
}

void DestroyObstacles(Obstacles** obstacles)
{
	if (obstacles)
	{
		if ((*obstacles)->transform)
			DeleteTransform((*obstacles)->transform);
		if ((*obstacles)->mesh)
			freeMesh(&(*obstacles)->mesh);
		delete *obstacles;
		*obstacles = NULL;
	}
}
