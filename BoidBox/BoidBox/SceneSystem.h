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
	void RestartCurrentScene();

	static SceneSystem* GetInstance();
private:
	SceneSystem();
	~SceneSystem();

	SceneSystem(SceneSystem const&) = delete;
	SceneSystem& operator=(SceneSystem const&) = delete;

	void ChangeScene();
	friend bool CheckRestartGame();

	static SceneSystem* instance;

	Scene* (*DefaultSceneInstance)();

	Scene* activeScene;
	Scene* nextScene;
	bool isRestarting;
	bool inDebug;
};

// Checks if any of the Debug Scenes have been triggered to change to
// Returns true if they are, false if not
bool CheckDebugScenes();

// Checks if any of the Game Scenes have been triggered to change to
// Returns true if they are, false if not
bool CheckGameScenes();

// Checks if the game has been triggered to completely restart
// Returns true if yes, false if not
bool CheckRestartGame();
