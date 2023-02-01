//------------------------------------------------------------------------------
//
// File Name:	Level.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Level.h"
#include "Object.h"

struct Level
{
	std::string name;
	//LevelIDType id;

	std::vector<Object*> objects;
	int objectCount;
};

Level* LevelCreate(std::string name)
{
	Level* level = new Level;
	level->name = name;
	level->objectCount = 0;
	return level;
}

void DeleteLevel(Level* level)
{
	for (int i = 0; i < level->objectCount; ++i)
		ObjectDelete(level->objects[i]);

	delete level;
}
