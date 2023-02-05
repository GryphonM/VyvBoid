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

	Transform* transform;
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
	DeleteTransform((*hunter)->transform);
	delete *hunter;
}

Hunters* InitCrosshair(Hunters* hunter, float width, float height, float radius)
{
	if (hunter)
	{
		Vector2D scale = Vector2D(100, 100);
		SpriteSource* source = CreateSpriteSource();
		Sprite* sprite = CreateSprite();
		Mesh* mesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0, "Crosshair");

		LoadSpriteSourceTexture(source, 1, 1, "./Assets/crosshair.png");
		SpriteSetMesh(sprite, mesh);

		AddHunterSprite(hunter, sprite);
		SpriteSetSource(hunter->sprite, source);

		Transform* hunterTrans = CreateTransform();
		TransformSetScale(hunterTrans, scale);
		AddHunterTrans(hunter, hunterTrans);

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
		RenderSprite(hunter->sprite, hunter->transform);
	}
}

void AddHunterSprite(Hunters* hunter, Sprite* sprite)
{
	hunter->sprite = sprite;
}

void AddHunterTrans(Hunters* hunter, Transform* transform)
{
	hunter->transform = transform;
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

Transform* GetHunterTransform(const Hunters* hunter)
{
	if (hunter)
	{
		return hunter->transform;
	}
	else
	{
		return NULL;
	}
}