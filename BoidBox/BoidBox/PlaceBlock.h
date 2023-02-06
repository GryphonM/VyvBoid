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

PlaceBlock* CreatePlaceBlocks(int max_blocks, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name);
void UpdatePlaceBlocks(PlaceBlock* place);
int GetNumberOfPlacedBlocks(PlaceBlock* place);
//Vector2D* GetPlacedBlocksTransform(PlaceBlock* place, int location);
void DrawPlacedBlocks(PlaceBlock* place);
void DestroyPlaceBlocks(PlaceBlock** place);

#endif