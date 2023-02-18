//------------------------------------------------------------------------------
//
// File Name:	OpenScene.cpp
// Description:	Contains code for the scene that opens on startup
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "OpenScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Engine.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Mesh.h"

struct OpenScene
{
	Scene base;

	// Other Fings
	Sprite* OpenSprite;

	// Constructor (Actually used this time)
	OpenScene(Scene _base) : base(_base), OpenSprite(NULL)
	{
		OpenSprite = CreateSprite();
		FreeSprite(&OpenSprite);
	}
};

Engine::ErrorCode OpenSceneLoad(void);
Engine::ErrorCode OpenSceneInit(void);
void OpenSceneUpdate(float dt);
void OpenSceneRender(void);
Engine::ErrorCode OpenSceneExit(void);
Engine::ErrorCode OpenSceneUnload(void);

Mesh* squareMesh;
SpriteSource* source;
Transform* pos;
OpenScene instance(Scene("Open Scene", OpenSceneLoad, OpenSceneInit, OpenSceneUpdate, OpenSceneRender, OpenSceneExit, OpenSceneUnload));

Scene* OpenSceneGetInstance() { return &(instance.base); }

Engine::ErrorCode OpenSceneLoad(void)
{
	squareMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Square Mesh", { 0.0f, 0.0f, 0.0f, 0.0f });
	pos = CreateTransform(Vector2D(), Vector2D(200.0, 200.0f));	source = CreateSpriteSource();
	source = CreateSpriteSource();
	LoadSpriteSourceTexture(source, 1, 1, "./Assets/containmentbreached.png");
	instance.OpenSprite = CreateSprite();
	SpriteSetMesh(instance.OpenSprite, squareMesh);
	SpriteSetSource(instance.OpenSprite, source);
	return Engine::NothingBad;
}

Engine::ErrorCode OpenSceneInit(void)
{
	SpriteSetFrame(instance.OpenSprite, 0);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	return Engine::NothingBad;
}

void OpenSceneUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestartGame())
		return;
	// Other Things on Open
}

void OpenSceneRender(void)
{
	RenderSprite(instance.OpenSprite, pos);
}

Engine::ErrorCode OpenSceneExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode OpenSceneUnload(void)
{
	FreeSprite(&instance.OpenSprite);
	freeMesh(&squareMesh);
	DeleteTransform(&pos);
	return Engine::NothingBad;
}
