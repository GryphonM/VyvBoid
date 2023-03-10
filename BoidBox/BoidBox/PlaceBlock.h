//------------------------------------------------------------------------------
//
// File Name:	PlaceBlock.h
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#ifndef PLACEBLOCK_H
#define PLACEBLOCK_H

typedef struct PlaceBlock PlaceBlock;
typedef struct Sound Sound;
typedef struct BoidList BoidList;
#if 0
typedef struct PlaceBlock
{
	int BlocksPlaced;
	int maxBlocks;
	Vector2D offScreen;

	Mesh* mesh;
	Object** object;
	ObjectList* objectList;
};
#endif

PlaceBlock* CreatePlaceBlocks(const char* file, const char* name, BoidList* boids, int max_blocks = 10);
PlaceBlock* CreatePlaceBlocks(const char* name, BoidList* boids, int max_blocks = 10);
void UpdatePlaceBlocks(PlaceBlock* place, Sound* sound);
int GetNumberOfPlacedBlocks(PlaceBlock* place);
//Vector2D* GetPlacedBlocksTransform(PlaceBlock* place, int location);
bool SetPlaceSound(PlaceBlock* place, const char* query);
void DrawPlacedBlocks(PlaceBlock* place);
void DestroyPlaceBlocks(PlaceBlock** place);
void DeleteBoidBlock(BoidList* list);

#endif