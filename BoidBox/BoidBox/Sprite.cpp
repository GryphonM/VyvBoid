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
	unsigned int frameIndex;

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
	Transform *transformSprite = CreateTransform();
	DGL_Color meshColor = { 0.0f, 0.0f, 0.0, 0.0f };

	if (sprite->source)
	{
		// Prepare to render a textured sprite
		DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
		// Set texture and texture offsets
		SpriteSourceSetTexture(sprite->source);
		//SpriteSourceSetTextureOffset(sprite->source, sprite->frameIndex);
	}
	else
	{
		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
		DGL_Graphics_SetTexture(NULL);
	}
	// Set position, scale, and rotation for the sprite
	// 
	//DGL_Graphics_SetCB_TransformData(, &scale, rotation);
	// 
	// Set transparency (range 0.0f – 1.0f)
	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	// Set blend color (RGBA, A = “strength” of blend)
	DGL_Graphics_SetCB_TintColor(&meshColor);
	// Render the mesh (list of triangles)
	RenderMesh(sprite->mesh);
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

void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource)
{
	if (sprite->source)
	{
		SpriteSourceFree(&spriteSource);
	}
	sprite->source = spriteSource;
}