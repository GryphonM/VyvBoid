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
#include "Object.h"
#include "PlaceBlock.h"

#define OFFSCREEN (1000.0f, 1000.0f)

struct PlaceBlock
{
	int BlocksPlaced;
	int maxBlocks;
	float rotation;
	Vector2D offScreen;

	Mesh* mesh;
	
	Object** object;
};

PlaceBlock* CreatePlaceBlocks(int max_blocks, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{ 
	PlaceBlock* place = new PlaceBlock;

	if (place)
	{
		place->BlocksPlaced = 0;
		place->maxBlocks = 0;
		place->offScreen = (Vector2D)OFFSCREEN;
		place->mesh = SquareMesh(xHalfSize, yHalfSize, uSize, vSize, name);
		place->object = new Object* [max_blocks];
		
		if (place->object && place->mesh)
		{
			for (int i = 0; i < max_blocks; i++)
			{
				place->object[i] = NULL;
			}
			return place;
		}
		return NULL;
	}
	
	return NULL;
}

void UpdatePlaceBlocks(PlaceBlock* place)
{
	if (place)
	{	
		Vector2D mish = Vector2D(DGL_Input_GetMousePosition());
		mish = DGL_Camera_ScreenCoordToWorld(mish);
		Transform* transform;
		if (DGL_Input_KeyTriggered(VK_LBUTTON) && place->BlocksPlaced < place->maxBlocks)
		{
			place->object[place->BlocksPlaced] = ObjectCreate("Blocks"+place->BlocksPlaced++, transform = CreateTransform(mish));
		}

		if (DGL_Input_KeyTriggered(VK_RBUTTON) )
		{
			for (int i = 0; i < place->BlocksPlaced; i++)
			{
				Vector2D position = TransformGetPosition(ObjectGetTransform(place->object[i]));

				if ((mish.X() <= position.X() + 10.0f) && (mish.X() >= position.X() - 10.0f)
					&& (mish.Y() <= position.Y() + 25.0f) && (mish.Y() >= position.Y() - 25.0f))
				{
					ObjectMove(place->object[i], place->offScreen);
					place->BlocksPlaced--;
					break;
				}
			}
		}
	}
}

void DrawPlacedBlocks(PlaceBlock* place)
{
	for (int k = 0; k < place->BlocksPlaced; k++)
	{
		RenderMesh(place->mesh, ObjectGetTransform(place->object[k]));
	}
}

void DestroyPlaceBlocks(PlaceBlock* place)
{
	freeMesh(&place->mesh);
	for (int i = 0; i < place->maxBlocks; i++)
		ObjectDelete(place->object[i]);
	delete place;
	place = NULL;
}