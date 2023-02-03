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
#include "Object.h"
#include "Mesh.h"

struct Level1
{
	std::string name;
	LevelIDType id;

	State state;
	Mesh* testMesh;

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
	return level;
}

void DeleteLevel(Level1* level)
{
	freeMesh(&level->testMesh);
	delete level;
}

void LevelInit(Level1* level)
{
	level->testMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Please Work or I Kill Someone");
	// Put your funky level init things here
}

std::string LevelGetName(Level1* level) { return level->name; }
void LevelSetName(Level1* level, std::string name) { level->name = name; }
void LevelSwitchState(Level1* level, State state) { level->state = state; }

void LevelUpdate(Level1* level, float dt)
{
	if (level->state == Place)
	{
		// Update Place Objects
	}
	else if (level->state == Play)
	{
		// Update Play Objects
	}
}

void LevelDraw(Level1* level)
{
	RenderMesh(level->testMesh);
}
