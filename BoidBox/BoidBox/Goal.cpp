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

Goal::Goal(Transform* _transform, const BoidList* _boidList, int _totalBoids) : transform(_transform), boidList(_boidList), 
																				totalBoids(_totalBoids), capturedBoids(0),
																				openMesh(NULL), endMesh(NULL), sprite(NULL),
																				completeSound(NULL), soundPlayed(false)
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
	DeleteTransform(&transform);
	SoundCleanup(completeSound);
}

void Goal::Update()
{
	capturedBoids += CheckBoidCollisions(boidList, TransformGetPosition(transform), TransformGetScale(transform).X(), KillBoid);
	if (capturedBoids >= totalBoids)
	{
		SpriteSetMesh(sprite, endMesh);
		if (!soundPlayed)
		{
			PlaySound(completeSound);
			soundPlayed = true;
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
