//------------------------------------------------------------------------------
//
// File Name:	BasicObstacles.h
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#ifndef BASICOBSTACLES_H
#define BASICOBSTACLES_H

typedef struct Obstacles Obstacles;

#if 0
typedef struct Obstacles
{
	Transform* transform;

	Mesh* mesh;

};
#endif

Obstacles* CreateObstacles(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name);
void DrawObstacles(Obstacles* obstacles);
void DestroyObstacles(Obstacles** obstacles);
#endif