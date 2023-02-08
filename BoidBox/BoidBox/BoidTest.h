//------------------------------------------------------------------------------
//
// File Name:	BoidTest.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
struct Object;
struct TestLevel;

typedef unsigned int LevelIDType;

#if 0
struct Level1
{
	std::string name;
	LevelIDType id;

	State state;
};
#endif

TestLevel* TestLevelCreate(std::string name = "");
void DeleteLevel(TestLevel* level);
void LevelInit(TestLevel* level);

//LevelIDType LevelGetID(Level* level);
std::string LevelGetName(TestLevel* level);
void LevelSetName(TestLevel* level, std::string name);

void LevelUpdate(TestLevel* level, float dt);
void LevelDraw(TestLevel* level);
