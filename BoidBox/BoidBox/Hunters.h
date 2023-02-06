//------------------------------------------------------------------------------
//
// File Name:	Hunters.h
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "DGL.h"

#include "Mesh.h"
#include "Sprite.h"
#include "Transform.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// tf does this do
#ifndef HUNTERS_H
#define HUNTERS_H

struct Hunters;

#if 0
struct Hunters
{
	DGL_Vec2 pos;
	DGL_Vec2 uv;

	const DGL_Texture* texture;

	static const DGL_Vec2 scale;

	float radius;
	float width;
	float height;
	float halfWidth;
	float halfHeight;
	float xDistance;
	float yDistance;
	float totalDistance;

	Sprite* sprite;

	Transform* transform;
};
#endif

// coll will need player/boids

Hunters* HunterCreate(void);

void FreeHunters(Hunters** hunter);

Hunters* InitCrosshair(Hunters* hunter, float width = 2.0f, float height = 4.0f, float radius = 30.0f);

void AddHunterSprite(Hunters* hunter, Sprite* sprite);

void AddHunterTrans1(Hunters* hunter, Transform* transform);
void AddHunterTrans2(Hunters* hunter, Transform* transform);
void AddHunterTrans3(Hunters* hunter, Transform* transform);

Sprite* GetHunterSprite(const Hunters* hunter);
Transform* GetHunterTransform1(const Hunters* hunter);
Transform* GetHunterTransform2(const Hunters* hunter);
Transform* GetHunterTransform3(const Hunters* hunter);

void DrawCrosshair(Hunters* hunter);

#endif