//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.h
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#ifndef SPRITESOURCE_H
#define SPRITESOURCE_H

struct DGL_Texture;
struct SpriteSource;


#if 0
struct SpriteSource
{
	int	numRows;
	int	numCols;

	const DGL_Texture* texture;

};
#endif

SpriteSource* SpriteSourceCreate();

void SpriteSourceFree(const SpriteSource** spriteSource);

void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName);

unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource);

void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, Vector2D(vec));

void SpriteSourceSetTexture(const SpriteSource* spriteSource);

void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex);

#endif