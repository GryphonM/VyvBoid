//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#ifndef SPRITE_H
#define SPRITE_H

struct Mesh;
struct SpriteSource;
struct Sprite;
struct Transform;


#if 0
struct Sprite
{
	int frameIndex;

	float alpha;

	const SpriteSource* source;

	const Mesh* mesh;
};

#endif

Sprite* CreateSprite(void);

void FreeSprite(Sprite** sprite);

void RenderSprite(const Sprite* sprite, Transform* transform);

float SpriteGetAlpha(const Sprite* sprite);

void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex);

void SpriteSetAlpha(Sprite* sprite, float alpha);

void SpriteSetMesh(Sprite* sprite, const Mesh* mesh);

void SpriteSetSource(Sprite* sprite, const SpriteSource* source);

#endif