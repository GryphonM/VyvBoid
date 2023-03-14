//------------------------------------------------------------------------------
//
// File Name:	TayLeeDebug.h
// Description:	Public interface for TayLee's Debug scene
// Author(s):	TayLee Young (taylee.young)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include <vector>
#include "TayLeeDebug.h"
#include "PlatformSystem.h"
#include "Hunters.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Scene.h"
#include "SceneSystem.h"

struct TayLeeDebug
{
	Scene base;

	// Other Fings
	//Mesh* testMesh;
	Sprite* OpenSprite;
	Sprite* titleSprite;
	Hunters* hunter1;
	Hunters* hunter2;
	Hunters* hunter3;
	Hunters* hunter4;

	Mesh* squareMesh;
	SpriteSource* source;
	Transform* pos;

	TayLeeDebug(Scene _base) : base(_base), OpenSprite(NULL)
	{
		OpenSprite = CreateSprite();
		FreeSprite(&OpenSprite);
	}
};

Engine::ErrorCode TayLeeLoad(void);
Engine::ErrorCode TayLeeInit(void);
void TayLeeUpdate(float dt);
void TayLeeRender(void);
Engine::ErrorCode TayLeeExit(void);
Engine::ErrorCode TayLeeUnload(void);

TayLeeDebug instance(Scene("TayLee Debug Scene", TayLeeLoad, TayLeeInit, TayLeeUpdate, TayLeeRender, TayLeeExit, TayLeeUnload));
Scene* TayLeeGetInstance() { return &instance.base; }


Engine::ErrorCode TayLeeLoad(void)
{
	instance.squareMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Square Mesh", { 0.0f, 0.0f, 0.0f, 0.0f });
	instance.pos = CreateTransform(Vector2D(), Vector2D(960, 561));
	instance.source = CreateSpriteSource();
	instance.source = CreateSpriteSource();
	LoadSpriteSourceTexture(instance.source, 1, 1, "./Assets/desktopBackgroundBLANK.png");
	instance.titleSprite = CreateSprite();
	SpriteSetMesh(instance.titleSprite, instance.squareMesh);
	SpriteSetSource(instance.titleSprite, instance.source);

	//instance.testMesh = NULL;
	//instance.hunter1 = HunterCreate();
	//instance.hunter2 = HunterCreate();
	//instance.hunter3 = HunterCreate();
	instance.hunter4 = HunterCreate();
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeInit(void)
{
	SpriteSetFrame(instance.titleSprite, 0);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

	//InitCrosshair(instance.hunter1, 2.0, 4.0, 30.0, {0, -300});
	//InitCrosshair(instance.hunter2, 2.0, 4.0, 30.0, {-300, 300});
	//InitCrosshair(instance.hunter3, 2.0, 4.0, 30.0, {300, 300});
	InitCrosshair(instance.hunter4, 2.0, 4.0, 30.0, {0, 100});
	return Engine::NothingBad;
}

void TayLeeUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes() || CheckRestart())
		return;
}

void TayLeeRender(void)
{
	RenderSprite(instance.titleSprite, instance.pos);

	//RenderMesh(instance.testMesh);
	//DrawCrosshair(instance.hunter1);
	//DrawCrosshair(instance.hunter2);
	//DrawCrosshair(instance.hunter3);
	DrawCrosshair(instance.hunter4);
}

Engine::ErrorCode TayLeeExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode TayLeeUnload(void)
{
	FreeSprite(&instance.titleSprite);
	freeMesh(&instance.squareMesh);
	DeleteTransform(&instance.pos);

	//FreeHunters(&instance.hunter1);
	//FreeHunters(&instance.hunter2);
	//FreeHunters(&instance.hunter3);
	FreeHunters(&instance.hunter4);
	//freeMesh(&instance.testMesh);
	return Engine::NothingBad;
}