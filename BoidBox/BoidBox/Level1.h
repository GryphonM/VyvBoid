//------------------------------------------------------------------------------
//
// File Name:	Level.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
struct Object;
struct Level1;

typedef unsigned int LevelIDType;
enum State { Place, Play };

#if 0
struct Level1
{
	std::string name;
	LevelIDType id;

	State state;
};
#endif

Level1* LevelCreate(std::string name = "");
void DeleteLevel(Level1* level);

//LevelIDType LevelGetID(Level* level);
std::string LevelGetName(Level1* level);
void LevelSetName(Level1* level, std::string name);
void LevelSwitchState(Level1* level, State state);

void LevelUpdate(Level1* level, float dt);
void LevelDraw(Level1* level);
