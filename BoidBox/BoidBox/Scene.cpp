//------------------------------------------------------------------------------
//
// File Name:	Scene.cpp
// Description:	Contains code to handle things to do with individual scenes
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "SceneSystem.h"
#include "Scene.h"
#include "DGL.h"

#include "OpenScene.h"
#include "GryphonDebug.h"
#include "TylerDebug.h"
#include "MichaelDebug.h"
#include "TayLeeDebug.h"

Scene::Scene(const char * _name, ErrorVoid load, ErrorVoid init, VoidFloat update, VoidVoid render, ErrorVoid exit, ErrorVoid unload)
	: name(_name), Load(load), Init(init), Update(update), Render(render), Exit(exit), Unload(unload)
{ }

bool CheckDebugScenes()
{
	if (DGL_Input_KeyTriggered('I'))
		SceneSystem::GetInstance()->SetScene(GryphonGetInstance(), true);
	else if (DGL_Input_KeyTriggered('L'))
		SceneSystem::GetInstance()->SetScene(MichaelGetInstance(), true);
	else if (DGL_Input_KeyTriggered('Q'))
		SceneSystem::GetInstance()->SetScene(TayLeeGetInstance(), true);
	else if (DGL_Input_KeyTriggered('H'))
		SceneSystem::GetInstance()->SetScene(TylerGetInstance(), true);
	else
		return false;
	return true;
}

bool CheckGameScenes()
{
	if (DGL_Input_KeyTriggered('0'))
		SceneSystem::GetInstance()->SetScene(OpenSceneGetInstance());
	else
		return false;
	return true;
}
