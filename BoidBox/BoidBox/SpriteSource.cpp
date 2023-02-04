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

//void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v)
//{
//	*u = (1.0f / spriteSource->numCols);
//	*v = (1.0f / spriteSource->numRows);

//	*u = *u * (frameIndex % spriteSource->numCols);
//	*v = *v * (frameIndex / spriteSource->numCols);
//}

void SpriteSourceSetTexture(const SpriteSource* spriteSource)
{
	DGL_Graphics_SetTexture(spriteSource->texture);
}

//void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex)
//{
 // vector stuff needs x and y value
//	Vector2D UV;
//	SpriteSourceGetUV(spriteSource, frameIndex, &UV.X(), &UV.Y());
//	DGL_Graphics_SetCB_TextureOffset(&UV);
//}