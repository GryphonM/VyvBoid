//------------------------------------------------------------------------------
//
// File Name:	Level.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include <vector>
#include "Level1.h"
#include "PlaceBlock.h"
#include "Object.h"
#include "Mesh.h"
#include "Hunters.h"
#include "BasicObstacles.h"

struct Level1
{
	std::string name;
	LevelIDType id;

	State state;
	Mesh* testMesh;
	Hunters* hunter;
	PlaceBlock* place;
	Obstacles* obstacles;

	// Here to shut up warning about uninitialized variable
	// Use LevelCreate instead
	Level1() : name(), id(0), testMesh(NULL), state(Place) {}
};

Level1* LevelCreate(std::string name)
{
	Level1* level = new Level1;
	level->name = name;
	level->state = Place;
	level->testMesh = NULL;
	level->obstacles = CreateObstacles(5.0f, 10.0f, 1.0f, 1.0f, "obstacles");
	level->hunter = HunterCreate();
	level->place = CreatePlaceBlocks(5, .5f, .5f, 1.0f, 1.0f, "blocks");
	return level;
}

void DeleteLevel(Level1* level)
{
	DestroyObstacles(&level->obstacles);
	DestroyPlaceBlocks(&level->place);
	FreeHunters(&level->hunter);
	freeMesh(&level->testMesh);
	delete level;
}

void LevelInit(Level1* level)
{
	DGL_Color color = { 1.0f, 0.0f, 0.0f, 1.0f };
	level->testMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Please Work or I Kill Someone", color);
	// Put your funky level init things here
	InitCrosshair(level->hunter);
}

std::string LevelGetName(Level1* level) { return level->name; }
void LevelSetName(Level1* level, std::string name) { level->name = name; }
void LevelSwitchState(Level1* level, State state) { level->state = state; }

void LevelUpdate(Level1* level, float dt)
{
	if (level->state == Place)
	{
		// Update Place Objects
		UpdatePlaceBlocks(level->place);
	}
	else if (level->state == Play)
	{
		// Update Play Objects
	}
}

void LevelDraw(Level1* level)
{
	DrawObstacles(level->obstacles);
	DrawPlacedBlocks(level->place);
	RenderMesh(level->testMesh);
	DrawCrosshair(level->hunter);
}
