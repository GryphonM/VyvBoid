//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "DGL.h"
#include "Vector2D.h"
#include "SpriteSource.h"

struct SpriteSource
{
	int	rows;
	int	Cols;

	DGL_Texture* texture;
};


SpriteSource* CreateSpriteSource()
{
	SpriteSource* source = new SpriteSource;

	if (source)
	{
		source->Cols = 1;
		source->rows = 1;
		source->texture = NULL;
		return (source);
	}
	else
	{
		return NULL;
	}
}

void FreeSpriteSource(SpriteSource** source)
{
	if (source && *source)
	{
		DGL_Graphics_FreeTexture(&(*source)->texture);
		delete* source;
		*source = NULL;
	}
}

void LoadSpriteSourceTexture(SpriteSource* source, int Cols, int rows, const char* texture)
{
	source->texture = DGL_Graphics_LoadTexture(texture);
	source->Cols = Cols;
	source->rows = rows;
}

unsigned GetFrameCount(const SpriteSource* source)
{
	int frameCount;

	if (source)
	{
		frameCount = (source->Cols * source->rows);
		return frameCount;
	}
	else
	{
		return 0;
	}
}

void SpriteSourceGetUV(const SpriteSource* source, int frameIndex, Vector2D(vec))
{
	// mmm hopefully this math checks out otherwise im gonna lose my mind lmao
	vec.X((1.0f / source->Cols) * (frameIndex % source->Cols));
	vec.Y((1.0f / source->rows) * (frameIndex / source->Cols));
}

void SpriteSourceSetTexture(const SpriteSource* source)
{
	DGL_Graphics_SetTexture(source->texture);
}

void SpriteSourceSetUV(const SpriteSource* source, int frameIndex)
{
	Vector2D(UV);
	SpriteSourceGetUV(source, frameIndex, UV);
	DGL_Graphics_SetCB_TextureOffset(UV);
}