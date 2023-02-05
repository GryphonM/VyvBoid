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
#include "Hunters.h"

struct Level1
{
	std::string name;
	LevelIDType id;

	State state;
	Mesh* testMesh;
	Hunters* hunter;

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
	level->hunter = HunterCreate();

	Sprite* hunterSprite = CreateSprite();
	AddHunterSprite(level->hunter, hunterSprite);
	Transform* hunterTrans = CreateTransform();
	AddHunterTrans(level->hunter, hunterTrans);

	return level;
}

void DeleteLevel(Level1* level)
{
	FreeHunters(&level->hunter);
	freeMesh(&level->testMesh);
	delete level;
}

void LevelInit(Level1* level)
{
	level->testMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Please Work or I Kill Someone");
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
	}
	else if (level->state == Play)
	{
		// Update Play Objects
	}
}

void LevelDraw(Level1* level)
{
	//RenderMesh(level->testMesh,);
	DrawCrosshair(level->hunter);
}
