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

class Vector2D;


#if 0
struct SpriteSource
{
	int	rows;
	int	Cols;

	const DGL_Texture* texture;

};
#endif

SpriteSource* CreateSpriteSource();

void FreeSpriteSource(const SpriteSource** spriteSource);

void LoadSpriteSourceTexture(SpriteSource* spriteSource, int Cols, int rows, const char* textureName);

unsigned GetFrameCount(const SpriteSource* spriteSource);

void SpriteSourceGetUV(const SpriteSource* spriteSource, int frameIndex, Vector2D(vec));

void SpriteSourceSetTexture(const SpriteSource* spriteSource);

void SpriteSourceSetUV(const SpriteSource* spriteSource, int frameIndex);

#endif