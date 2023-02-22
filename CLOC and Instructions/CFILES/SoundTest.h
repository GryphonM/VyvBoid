//------------------------------------------------------------------------------
//
// File Name:	SoundTest.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include <string>
struct Object;
struct SoundTest;

typedef unsigned int LevelIDType;

#if 0
struct SoundTest
{
	std::string name;
	LevelIDType id;

	BoidList* boidList;

	Sound* sound;

	PlaceBlock* place;

	State state;
};
#endif

SoundTest* SoundTestCreate(std::string name = "");
void DeleteLevel(SoundTest* level);
void LevelInit(SoundTest* level);

//LevelIDType LevelGetID(Level* level);
std::string LevelGetName(SoundTest* level);
void LevelSetName(SoundTest* level, std::string name);

void LevelUpdate(SoundTest* level, float dt);
void LevelDraw(SoundTest* level);
