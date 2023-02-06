//------------------------------------------------------------------------------
//
// File Name:	PlaceBlock.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "DGL.h"
#include "Transform.h"
#include "Mesh.h"
#include "Vector2D.h"
#include "List.h"
#include "Object.h"
#include "PlaceBlock.h"

#define OFFSCREEN (1000.0f, 1000.0f)

struct PlaceBlock
{
	int BlocksPlaced;
	int maxBlocks;
	Vector2D offScreen;

	Mesh* mesh;
	Object** object;
	ObjectList* objectList;
};

PlaceBlock* CreatePlaceBlocks(int max_blocks, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{ 
	PlaceBlock* place = new PlaceBlock;

	if (place)
	{
		place->BlocksPlaced = 0;
		place->maxBlocks = max_blocks;
		place->offScreen = (Vector2D)OFFSCREEN;
		place->mesh = SquareMesh(xHalfSize, yHalfSize, uSize, vSize, name);
		place->objectList = new ObjectList;
		place->object = new Object * [max_blocks];
		if (place->objectList && place->mesh && place->object)
		{
			for (int i = 0; i < max_blocks; i++)
				place->object[i] = NULL;
			return place;
		}
		return NULL;
	}
	
	return NULL;
}

void UpdatePlaceBlocks(PlaceBlock* place)
{
	// set to 0 to place
	int test = 0;
	if (place && test != 1)
	{	
		Vector2D mish = Vector2D(DGL_Input_GetMousePosition());
		mish = DGL_Camera_ScreenCoordToWorld(mish);
		if (DGL_Input_KeyTriggered(VK_LBUTTON) && place->BlocksPlaced < place->maxBlocks)
		{
			place->objectList->PushFront(place->object[place->BlocksPlaced] = ObjectCreate("Block" + place->BlocksPlaced, CreateTransform(mish, Vector2D(30.0f, 30.0f))));
			place->BlocksPlaced++;
		}

		if (DGL_Input_KeyTriggered(VK_RBUTTON) )
		{
			for (int i = 0; i < place->objectList->Size(); i++)
			{
				Vector2D position = TransformGetPosition(ObjectGetTransform(place->object[i]));
				if ((mish.X() <= position.X() + 10.0f) && (mish.X() >= position.X() - 10.0f)
					&& (mish.Y() <= position.Y() + 25.0f) && (mish.Y() >= position.Y() - 25.0f))
				{
					ObjectListRemove(place->objectList, place->object[i]);
					place->BlocksPlaced--;
					break;
				}
			}
		}
	}
}
// in theory could be used for printing stuff for UI
int GetNumberOfPlacedBlocks(PlaceBlock* place)
{
	if (place)
	{
		return place->BlocksPlaced;
	}
	else
	{
		return NULL;
	}
}

/*Vector2D* GetPlacedBlocksTransform(PlaceBlock* place, int location)
{
	if (place)
	{
		Vector2D position = TransformGetPosition(ObjectGetTransform(place->object[location]));
		return &position;
	}
	else
		return NULL;
}*/

void DrawPlacedBlocks(PlaceBlock* place)
{
	DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
	for (int k = 0; k < place->BlocksPlaced; k++)
	{
		RenderMesh(place->mesh, ObjectGetTransform(place->object[k]));
	}
}

void DestroyPlaceBlocks(PlaceBlock** place)
{
	if (place)
	{
		freeMesh(&((*place)->mesh));
		(*place)->objectList->Clear();
		delete (*place)->objectList;
		delete *place;
		*place = NULL;
	}
	else
		return;
}