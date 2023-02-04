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

struct SpriteSource
{
	int	numRows;
	int	numCols;

	const DGL_Texture* texture;
};


SpriteSource* SpriteSourceCreate()
{
	SpriteSource* spriteSource = new SpriteSource;

	if (spriteSource)
	{
		return (spriteSource);
	}
	else
	{
		return NULL;
	}
}

void SpriteSourceFree(const SpriteSource** spriteSource)
{
	delete* spriteSource;
	*spriteSource = NULL;
}

void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName)
{
	spriteSource->texture = DGL_Graphics_LoadTexture(textureName);
	spriteSource->numCols = numCols;
	spriteSource->numRows = numRows;
}

unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource)
{
	int frameCount;

	if (spriteSource)
	{
		frameCount = (spriteSource->numCols * spriteSource->numRows);
		return frameCount;
	}
	else
	{
		return 0;
	}
}

void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, Vector2D(vec))
{
	// hopefully the math checks, funky vector jazz 

	vec.X((1.0f / spriteSource->numCols) * (frameIndex % spriteSource->numCols));
	vec.Y((1.0f / spriteSource->numRows) * (frameIndex / spriteSource->numCols));
}

void SpriteSourceSetTexture(const SpriteSource* spriteSource)
{
	DGL_Graphics_SetTexture(spriteSource->texture);
}

void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex)
{
	Vector2D(UV);
	SpriteSourceGetUV(spriteSource, frameIndex, UV);
	DGL_Graphics_SetCB_TextureOffset(UV);
}