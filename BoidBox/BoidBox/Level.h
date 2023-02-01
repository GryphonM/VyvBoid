//------------------------------------------------------------------------------
//
// File Name:	Level.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include <vector>
#include <string>
struct Object;
struct Level;

typedef unsigned int LevelIDType;

#if 0
struct Level
{
	std::string name;
	LevelIDType id;

	std::vector<Object*> objects;
	int objectCount;
};
#endif

Level* LevelCreate(std::string name = "");
void DeleteLevel(Level* level);

LevelIDType GetID(Level* level);
std::string GetName(Level* level);
void SetName(Level* level, std::string name);
