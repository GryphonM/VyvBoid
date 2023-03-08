//------------------------------------------------------------------------------
//
// File Name:	Goal.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM150 Game Project
// Course:		GAM150
//
//------------------------------------------------------------------------------

#include "Goal.h"
#include "Transform.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Boids.h"
#include "SoundSystem.h"
#include "SceneSystem.h"

Goal::Goal(Transform* _transform, Scene* scene, 
			const BoidList* _boidList, int _totalBoids) :	transform(_transform), nextScene(scene),
															boidList(_boidList), totalBoids(_totalBoids), capturedBoids(0),
															openMesh(NULL), endMesh(NULL), sprite(NULL),
															completeSound(NULL), soundPlayed(false), soundTime(1.5f)
{
	if (_transform && _boidList)
	{
		sprite = CreateSprite();
		openMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Goal", { 0.043f, 0.9f, 0.059f, 1.0f });
		endMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Complete", { 1.0f, 0.0f, 0.0f, 1.0f });
		SpriteSetMesh(sprite, openMesh);
		SpriteSource* texture = CreateSpriteSource();
		LoadSpriteSourceTexture(texture, 1, 1, "./Assets/Circle.png");
		SpriteSetSource(sprite, texture);
		completeSound = SoundCreate("LevelComplete", "./Assets/bikeBell.mp3");
	}
}

Goal::~Goal()
{
	FreeSprite(&sprite);
	freeMesh(&openMesh);
	freeMesh(&endMesh);
	DeleteTransform(&transform);
	SoundCleanup(completeSound);
}

void Goal::Update(float dt)
{
	capturedBoids += CheckBoidCollisions(boidList, TransformGetPosition(transform), TransformGetScale(transform).x/2, KillBoid);
	if (capturedBoids >= totalBoids - 2)
	{
		SpriteSetMesh(sprite, endMesh);
		if (!soundPlayed)
		{
			PlaySound(completeSound);
			soundPlayed = true;
		}
		else
		{
			soundTime -= dt;
			if (soundTime <= 0)
				SceneSystem::GetInstance()->SetScene(nextScene);
		}
	}
}

void Goal::Render()
{
	RenderSprite(sprite, transform);
}

void Goal::Reset()
{
	capturedBoids = 0;
}
