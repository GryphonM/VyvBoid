//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "Sprite.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Vector2D.h"
#include "Transform.h"
#include "SpriteSource.h"
#include "DGL.h"

struct Sprite
{
	int frameIndex;

	float alpha;

	const SpriteSource* source;

	const Mesh* mesh;
};

Sprite* CreateSprite(void)
{
	Sprite* sprite = new Sprite;

	if (sprite)
	{
		return (sprite);
	}
	else
	{
		return NULL;
	}
}

void FreeSprite(Sprite** sprite)
{
	delete* sprite;
	sprite = NULL;
}

void RenderSprite(const Sprite* sprite, Transform* transform)
{ 
	DGL_Color meshColor = { 0.0f, 0.0f, 0.0, 0.0f };

	// props to anyone who DOESNT rip this from 230 tbh

	if (sprite->source)
	{
		DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
		SpriteSourceSetTexture(sprite->source);
		SpriteSourceSetUV(sprite->source, sprite->frameIndex);
	}
	else
	{
		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
		DGL_Graphics_SetTexture(NULL);
	}

	DGL_Graphics_SetCB_TransformData(TransformGetPosition(transform), TransformGetScale(transform), TransformGetRotation(transform));
	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&meshColor);
	RenderMesh(sprite->mesh, transform);
}

float SpriteGetAlpha(const Sprite* sprite)
{
	if (sprite)
	{
		return (sprite->alpha);
	}
	else
	{
		return 0.0f;
	}
}

void SpriteSetAlpha(Sprite* sprite, float alpha)
{
	if (sprite)
	{
		if (alpha == min(alpha, 0))
		{
			alpha = 0;
		}
		if (alpha == max(alpha, 1))
		{
			alpha = 1;
		}

		sprite->alpha = alpha;
	}
}

void SpriteSetMesh(Sprite* sprite, const Mesh* mesh)
{
	sprite->mesh = mesh;
}

void SpriteSetSource(Sprite* sprite, const SpriteSource* Source)
{
	if (sprite->source)
	{
		FreeSpriteSource(&Source);
	}
	sprite->source = Source;
}