//------------------------------------------------------------------------------
//
// File Name:	BaseSystem.h
// Description:	A base class for other systems to inherit from
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include "Engine.h"

class BaseSystem
{
public:
	BaseSystem(const char *_name = "");
	BaseSystem(BaseSystem const&) = delete;
	BaseSystem& operator=(BaseSystem const&) = delete;

	virtual Engine::ErrorCode Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual Engine::ErrorCode Close() = 0;

	virtual ~BaseSystem() = default;
private:
	const char* name;
};