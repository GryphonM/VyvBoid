//------------------------------------------------------------------------------
//
// File Name:	Scene.cpp
// Description:	Contains code to handle things to do with individual scenes
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "Scene.h"

Scene::Scene(const char * _name, ErrorVoid load, ErrorVoid init, VoidFloat update, VoidVoid render, ErrorVoid exit, ErrorVoid unload)
	: name(_name), Load(load), Init(init), Update(update), Render(render), Exit(exit), Unload(unload)
{ }

