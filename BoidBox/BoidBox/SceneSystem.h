//------------------------------------------------------------------------------
//
// File Name:	SceneSystem.h
// Description:	System to handle the switching between scenes
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

#include "BaseSystem.h"
class Scene;

class SceneSystem : public BaseSystem
{
public:
	Engine::ErrorCode Init();
	void Update(float dt);
	void Render();
	Engine::ErrorCode Close();
	void SetScene(Scene* scene, bool debug = false);

	static SceneSystem* GetInstance();
private:
	SceneSystem();
	~SceneSystem();

	SceneSystem(SceneSystem const&) = delete;
	SceneSystem& operator=(SceneSystem const&) = delete;

	void ChangeScene();

	static SceneSystem* instance;

	Scene* activeScene;
	Scene* nextScene;
	bool isRestarting;
	bool inDebug;
};