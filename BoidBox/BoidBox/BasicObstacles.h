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

typedef struct Gas Gas;

typedef struct Tower Tower;

#if 0
typedef struct Obstacles
{
	Tower* tower;

	Gas* gas;

	const char* conatainerName;
};

typedef struct Tower
{
	Transform* transform;

	Mesh* mesh;

	Sprite* sprite;
};

typedef struct Gas
{
	Transform* transform;

	Mesh* mesh;

	Sprite* sprite;
};

#endif

Obstacles* CreateObstacles(const char* name);
Tower* CreateTower(const char* name);
Gas* CreateGas(const char* name);

void UpdateGasPosition(Gas* gas, float min, float max, float dt);
void DrawTower(Tower* tower);
void DrawGas(Gas* gas);
void DrawObstacles(Obstacles* obstacles);
void AddTower(Obstacles* obstacles, Tower* tower);
void AddGas(Obstacles* obstacles, Gas* gas);
void DeleteTower(Tower** tower);
void DeleteGas(Gas** gas);
void DestroyObstacles(Obstacles** obstacles);
#endif