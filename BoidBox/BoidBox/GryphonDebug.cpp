//------------------------------------------------------------------------------
//
// File Name:	GryphonDebug.cpp
// Description:	Contains the code to run Gryphon's Debug scene
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "GryphonDebug.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Mesh.h"
#include "Sprite.h"

struct GryphonDebug
{
	Scene base;

	// Other Fings
	Sprite* sprite;
	Transform* pos;
	float maxY;
	float minY;
	float speed;
	bool movingUp;

	GryphonDebug(Scene _base) : base(_base), sprite(NULL), pos(NULL), maxY(150.0f), minY(-150.0f), speed(50.0f), movingUp(false)
	{
		sprite = CreateSprite();
		FreeSprite(&sprite);
	}
};

Engine::ErrorCode GryphonLoad(void);
Engine::ErrorCode GryphonInit(void);
void GryphonUpdate(float dt);
void GryphonRender(void);
Engine::ErrorCode GryphonExit(void);
Engine::ErrorCode GryphonUnload(void);

GryphonDebug instance(Scene("Gryphon Debug Scene", GryphonLoad, GryphonInit, GryphonUpdate, GryphonRender, GryphonExit, GryphonUnload));
Scene* GryphonGetInstance() { return &instance.base; }
Mesh* mesh;

Engine::ErrorCode GryphonLoad(void)
{
	mesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Square", { 0.80f, 0.11f, 0.72f, 1.0f });
	instance.sprite = CreateSprite();
	instance.pos = CreateTransform(Vector2D(), Vector2D(50.0f, 50.0f));
	return Engine::NothingBad;
}

Engine::ErrorCode GryphonInit(void)
{
	Vector2D pos(0, 0);
	instance.movingUp = false;
	TransformSetPosition(instance.pos, pos);
	SpriteSetMesh(instance.sprite, mesh);
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTexture(NULL);
	return Engine::NothingBad;
}

void GryphonUpdate(float dt)
{
	if (CheckDebugScenes() || CheckGameScenes())
		return;

	Vector2D pos = TransformGetPosition(instance.pos);
	if (instance.movingUp)
	{
		pos.Y(pos.Y() + (instance.speed * dt));
		if (pos.Y() >= instance.maxY)
			instance.movingUp = false;
	}
	else
	{
		pos.Y(pos.Y() - (instance.speed * dt));
		if (pos.Y() <= instance.minY)
			instance.movingUp = true;
	}
	TransformSetPosition(instance.pos, pos);
}

void GryphonRender(void)
{
	DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
	RenderSprite(instance.sprite, instance.pos);
}

Engine::ErrorCode GryphonExit(void)
{
	return Engine::NothingBad;
}

Engine::ErrorCode GryphonUnload(void)
{
	freeMesh(&mesh);
	FreeSprite(&instance.sprite);
	DeleteTransform(&instance.pos);
	return Engine::NothingBad;
}