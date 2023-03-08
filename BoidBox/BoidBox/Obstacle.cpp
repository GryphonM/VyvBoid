//------------------------------------------------------------------------------
//
// File Name:	Obstacle.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM150 Game Project
// Course:		GAM150
//
//------------------------------------------------------------------------------

#include "Obstacle.h"
#include "Transform.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Boids.h"
#include "SoundSystem.h"

Obstacle::Obstacle(Transform* _transform, const BoidList* _boidList, int _totalBoids) : transform(_transform), boidList(_boidList),
																						totalBoids(_totalBoids), capturedBoids(0),
																						openMesh(NULL), endMesh(NULL), sprite(NULL),
																						diedSound(NULL), soundPlayed(false), boidsCaptured(0)
{
	if (_transform && _boidList)
	{
		sprite = CreateSprite();
		openMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Obstacle", { 0.80f, 0.20f, 0.30f, 1.0f });
		endMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Complete", { 1.0f, 0.0f, 0.0f, 1.0f });
		SpriteSetMesh(sprite, openMesh);
		//SpriteSource* texture = CreateSpriteSource();
		//LoadSpriteSourceTexture(texture, 1, 1, "./Assets/Circle.png");
		//SpriteSetSource(sprite, texture);
		diedSound = SoundCreate("BugEscaped", "./Assets/escaped.mp3");
	}
}

Obstacle::~Obstacle()
{
	FreeSprite(&sprite);
	freeMesh(&openMesh);
	freeMesh(&endMesh);
	DeleteTransform(&transform);
	SoundCleanup(diedSound);
}

void Obstacle::Update()
{
	capturedBoids += CheckBoidCollisions(boidList, TransformGetPosition(transform), TransformGetScale(transform), KillBoid);
	if (boidsCaptured < capturedBoids)
	{
		boidsCaptured = capturedBoids;
		PlaySound(diedSound);
	}
}

void Obstacle::Render()
{
	RenderSprite(sprite, transform);
}

void Obstacle::Reset()
{
	capturedBoids = 0;
	boidsCaptured = 0;
}
