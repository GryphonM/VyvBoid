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
#include "BoidTest.h"
#include "Object.h"
#include "Mesh.h"

struct TestLevel
{
	std::string name;
	LevelIDType id;

	Mesh* testMesh;

	// Here to shut up warning about uninitialized variable
	// Use LevelCreate instead
	TestLevel() : name(), id(0), testMesh(NULL) {}
};

TestLevel* TestLevelCreate(std::string name)
{
	TestLevel* level = new TestLevel;
	level->name = name;
	level->testMesh = NULL;
	return level;
}

void DeleteLevel(TestLevel* level)
{
	freeMesh(&level->testMesh);
	delete level;
}

void LevelInit(TestLevel* level)
{
	level->testMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Please Work or I Kill Someone");
	// Put your funky level init things here
}

std::string LevelGetName(TestLevel* level) { return level->name; }
void LevelSetName(TestLevel* level, std::string name) { level->name = name; }

void LevelUpdate(TestLevel* level, float dt)
{
	// Put funky level things here
}

void LevelDraw(TestLevel* level)
{
	// Put draw calls here
}
