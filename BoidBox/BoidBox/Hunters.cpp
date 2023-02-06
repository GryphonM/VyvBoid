//------------------------------------------------------------------------------
//
// File Name:	Hunters.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "DGL.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "Hunters.h"
#include "Vector2D.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// i dont know what I'm doing

struct Hunters
{
	// perhaaps unnecessary idk yet
	DGL_Vec2 pos;
	DGL_Vec2 uv;

	// this WAS neces at some point...
	static const DGL_Vec2 scale;

	float radius;
	float width;
	float height;
	float halfWidth;
	float halfHeight;

	// collision stuff 
	float xDistance;
	float yDistance;
	float totalDistance;

	Sprite* sprite;

	Transform* transform1;
	Transform* transform2;
	Transform* transform3;
};

Hunters* HunterCreate(void)
{
	Hunters* hunter = new Hunters;

	if (hunter)
	{
		return hunter;
	}
	else
	{
		return NULL;
	}
}

void FreeHunters(Hunters** hunter)
{
	// rip my boys
	FreeSprite(&(*hunter)->sprite);
	DeleteTransform((*hunter)->transform1);
	DeleteTransform((*hunter)->transform2);
	DeleteTransform((*hunter)->transform3);
	delete *hunter;
}

Hunters* InitCrosshair(Hunters* hunter, float width, float height, float radius)
{
	if (hunter)
	{
		Vector2D scale = Vector2D(100, 100);
		Vector2D trans1 = Vector2D(0, 0);
		Vector2D trans2 = Vector2D(60, -60);
		Vector2D trans3 = Vector2D(-150, 0);

		SpriteSource* source = CreateSpriteSource();
		Sprite* sprite = CreateSprite();
		Mesh* mesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0, "Crosshair");

		LoadSpriteSourceTexture(source, 1, 1, "./Assets/crosshair.png");
		SpriteSetMesh(sprite, mesh);

		AddHunterSprite(hunter, sprite);
		SpriteSetSource(hunter->sprite, source);

		Transform* hunterTrans1 = CreateTransform(trans1);
		TransformSetScale(hunterTrans1, scale);
		AddHunterTrans1(hunter, hunterTrans1);

		Transform* hunterTrans2 = CreateTransform(trans2);
		TransformSetScale(hunterTrans2, scale);
		AddHunterTrans2(hunter, hunterTrans2);

		Transform* hunterTrans3 = CreateTransform(trans3);
		TransformSetScale(hunterTrans3, scale);
		AddHunterTrans3(hunter, hunterTrans3);

		hunter->width = width;
		hunter->height = height;
		hunter->halfWidth = hunter->width / 2.0f;
		hunter->halfHeight = hunter->height / 2.0f;
		hunter->radius = radius;


		//note: array of crosshairs for diff positions would be good 
	}

	return hunter;
}

// im fuckin stupid so like, this is *terrible* and I am sorry
void DrawCrosshair(Hunters* hunter)
{
	if (hunter)
	{
		RenderSprite(hunter->sprite, hunter->transform1);
		RenderSprite(hunter->sprite, hunter->transform2);
		RenderSprite(hunter->sprite, hunter->transform3);
	}
}

void AddHunterSprite(Hunters* hunter, Sprite* sprite)
{
	hunter->sprite = sprite;
}

void AddHunterTrans1(Hunters* hunter, Transform* transform)
{
	hunter->transform1 = transform;
}

void AddHunterTrans2(Hunters* hunter, Transform* transform)
{
	hunter->transform2 = transform;
}

void AddHunterTrans3(Hunters* hunter, Transform* transform)
{
	hunter->transform3 = transform;
}

// gotta love getters and setters 

Sprite* GetHunterSprite(const Hunters* hunter)
{
	if (hunter)
	{
		return hunter->sprite;
	}
	else
	{
		return NULL;
	}
}

Transform* GetHunterTransform1(const Hunters* hunter)
{
	if (hunter)
	{
		return hunter->transform1;
	}
	else
	{
		return NULL;
	}
}

Transform* GetHunterTransform2(const Hunters* hunter)
{
	if (hunter)
	{
		return hunter->transform2;
	}
	else
	{
		return NULL;
	}
}

Transform* GetHunterTransform3(const Hunters* hunter)
{
	if (hunter)
	{
		return hunter->transform3;
	}
	else
	{
		return NULL;
	}
}