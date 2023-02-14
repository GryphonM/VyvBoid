//------------------------------------------------------------------------------
//
// File Name:	MichaelDebug.cpp
// Description:	Contains the code for Michael's Debug Scene
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "MichaelDebug.h"
#include "Scene.h"
#include "Mesh.h"

struct MichaelDebug
{
	Scene base;

	// Other Fings

	MichaelDebug(Scene _base) : base(_base)
	{
	}
};

Engine::ErrorCode MichaelLoad(void);
Engine::ErrorCode MichaelInit(void);
void MichaelUpdate(float dt);
void MichaelRender(void);
Engine::ErrorCode MichaelExit(void);
Engine::ErrorCode MichaelUnload(void);

MichaelDebug instance(Scene("Michael Debug Scene", MichaelLoad, MichaelInit, MichaelUpdate, MichaelRender, MichaelExit, MichaelUnload));
Scene* MichaelGetInstance() { return &instance.base; }


Engine::ErrorCode MichaelLoad(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode MichaelInit(void)
{
	return Engine::NothingBad;
}

void MichaelUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes())
		return;
}

void MichaelRender(void)
{
}

Engine::ErrorCode MichaelExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode MichaelUnload(void)
{
	return Engine::NothingBad;
}
