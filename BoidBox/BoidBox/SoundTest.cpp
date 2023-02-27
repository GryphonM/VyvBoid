//------------------------------------------------------------------------------
//
// File Name:	SoundTest.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include <vector>
#include "Level1.h"
#include "SoundTest.h"
#include "Object.h"
#include "Mesh.h"
#include "Boids.h"
#include "SoundSystem.h"
#include "PlaceBlock.h"

struct SoundTest
{
	std::string name;
	LevelIDType id;

	Sound* placeSound;
	Sound* jumpScare;

	PlaceBlock* place;
	// Here to shut up warning about uninitialized variable
	// Use LevelCreate instead
	SoundTest() : name(), id(0) {}
};

SoundTest* SoundTestCreate(std::string name)
{
	SoundTest* level = new SoundTest;
	level->name = name;
	level->placeSound = SoundCreate("test", "./Assets/place.mp3");
	level->jumpScare = SoundCreate("scare", "./Assets/cloaker.ogg");
	return level;
}

void DeleteLevel(SoundTest* level)
{
	DestroyPlaceBlocks(&level->place);
	SoundCleanup(level->placeSound);
	SoundCleanup(level->jumpScare);
	delete level;
}

void LevelInit(SoundTest* level)
{
	// Put your funky level init things here
	level->place = CreatePlaceBlocks("block");
}

std::string LevelGetName(SoundTest* level) { return level->name; }
void LevelSetName(SoundTest* level, std::string name) { level->name = name; }

void LevelUpdate(SoundTest* level, float dt)
{
	UpdatePlaceBlocks(level->place, level->placeSound);
	if (DGL_Input_KeyTriggered('C'))
	{
		PlaySound(level->jumpScare);
	}

}

void LevelDraw(SoundTest* level)
{
	DrawPlacedBlocks(level->place);
}
