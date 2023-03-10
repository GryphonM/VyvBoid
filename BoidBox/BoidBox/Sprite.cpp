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

#define _USE_MATH_DEFINES
#include <math.h>

struct Sprite
{
	int frameIndex;

	float alpha;

	SpriteSource* source;

	const Mesh* mesh;

	const char* text;
};

Sprite* CreateSprite(void)
{
	Sprite* sprite = new Sprite;

	if (sprite)
	{
		sprite->source = NULL;
		sprite->mesh = NULL;
		sprite->alpha = 1;
		sprite->frameIndex = 0;
		sprite->text = NULL;
		return (sprite);
	}
	else
	{
		return NULL;
	}
}

void FreeSprite(Sprite** sprite)
{
	if (sprite && *sprite)
	{
		FreeSpriteSource(&((*sprite)->source));
		delete* sprite;
		*sprite = NULL;
	}
}

void RenderSprite(const Sprite* sprite, Transform* transform)
{ 
	// props to anyone who DOESNT rip this from 230 tbh
	float angle = TransformGetRotation(transform);
	angle = (angle * (float)M_PI / 180.0f);
	TransformSetRotation(transform, angle);

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

	DGL_Graphics_SetCB_Alpha(sprite->alpha);

	if (sprite->text == NULL)
	{
		DGL_Graphics_SetCB_TransformData(TransformGetPosition(transform), TransformGetScale(transform), angle);
		RenderMesh(sprite->mesh);
	}
	else
	{
		const char* spritePtr = sprite->text;
		int i = 0;

		while (spritePtr[i] != 0)
		{
			int frameIndex = spritePtr[i] - ' ';
			SpriteSourceSetUV(sprite->source, frameIndex);
			DGL_Graphics_SetCB_TransformData(TransformGetPosition(transform), TransformGetScale(transform), angle);
			RenderMesh(sprite->mesh);
			i++;
		}
	}
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

void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex)
{
	if (frameIndex >= 0 && frameIndex <= GetFrameCount(sprite->source))
	{
		sprite->frameIndex = frameIndex;
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

void SpriteSetSource(Sprite* sprite, SpriteSource* source)
{
	sprite->source = source;
}

void SpriteSetText(Sprite* sprite, const char* text)
{
	if (text != NULL)
	{
		sprite->text = text;
	}
	else
	{
		sprite->text = 0;
	}
}