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
#include "SpriteSource.h"
#include "Sprite.h"
#include "SoundSystem.h"

#define OFFSCREEN (1000.0f, 1000.0f)

struct PlaceBlock
{
	int BlocksPlaced;
	int maxBlocks;
	Vector2D offScreen;
	
	Vector2D offset;

	DGL_Color color;

	Sprite* sprite;
	SpriteSource* source;

	Mesh* mesh;
	ObjectList objectList;

	bool sound;
};

PlaceBlock* CreatePlaceBlocks(int max_blocks, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name, const char* file)
{ 
	PlaceBlock* place = new PlaceBlock;
	place->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (place)
	{
		place->offset = (xHalfSize, yHalfSize);
		place->sound = false;
		place->BlocksPlaced = 0;
		place->maxBlocks = max_blocks;
		place->offScreen = (Vector2D)OFFSCREEN;
		place->mesh = SquareMesh(xHalfSize, yHalfSize, uSize, vSize, name, place->color);
		place->source = NULL;
		place->sprite = NULL;
		if (file != "none")
		{
			place->sprite = CreateSprite();
			place->source = CreateSpriteSource();
			if (place->sprite && place->source)
			{
				LoadSpriteSourceTexture(place->source, 1, 1, file);
				SpriteSetMesh(place->sprite, place->mesh);
				SpriteSetSource(place->sprite, place->source);
			}
		}
		if (place->mesh)
		{
			return place;
		}
		return NULL;
	}
	
	return NULL;
}

void UpdatePlaceBlocks(PlaceBlock* place, Sound* sound)
{
	// set to 0 to place
	int test = 0;
	if (place && test != 1)
	{	
		Vector2D mish = Vector2D(DGL_Input_GetMousePosition());
		mish = DGL_Camera_ScreenCoordToWorld(mish);
		if (DGL_Input_KeyTriggered(VK_LBUTTON) && place->BlocksPlaced < place->maxBlocks)
		{
			place->objectList.PushFront(ObjectCreate("Block" + place->BlocksPlaced, CreateTransform(mish, Vector2D(30.0f, 30.0f))));
			place->BlocksPlaced++;
			if (sound)
			{
				PlaySound(sound);
			}
		}

		if (DGL_Input_KeyTriggered(VK_RBUTTON) )
		{
			for (int i = 0; i < place->objectList.Size(); i++)
			{
				Transform* transform = ObjectGetTransform(place->objectList[i]);
				Vector2D position = TransformGetPosition(transform);
				Vector2D scale = TransformGetScale(transform);
				if ((mish.X() <= (position.X() + (sqrtf(scale.Y()) * 2.2f)))
				&& (mish.X() >= (position.X() - (sqrtf(scale.Y()) * 2.2f)))
				&& (mish.Y() <= (position.Y() + (sqrtf(scale.X()) * 2.2f)))
				&& (mish.Y() >= (position.Y() - (sqrtf(scale.X()) * 2.2f))))
				{
					place->color = { 0.0, 0.5, 0.5, 1.0 };
					ObjectListRemove(&place->objectList, place->objectList[i]);
					place->BlocksPlaced--;
					if (sound)
						PlaySound(sound);
					break;
				}
			}
		}
		ObjectListClean(&place->objectList);
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

bool SetPlaceSound(PlaceBlock* place, const char *query)
{
	if (query == "yes")
		return true;
	else
		return false;
}

//Vector2D GetPlacedBlocksTransform(PlaceBlock* place, int location)
//{
//	if (place)
//	{
//		Transform* transform = ObjectGetTransform(place->objectList[location]);
//		Vector2D position =  TransformGetPosition(transform);
//		return position;
//	}
//	return OFFSCREEN;
//}

void DrawPlacedBlocks(PlaceBlock* place)
{
	if (place->source && place->sprite)
	{
		DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
		
		for (int k = 0; k < place->BlocksPlaced; k++)
		{
			RenderSprite(place->sprite, ObjectGetTransform(place->objectList[k]));
		}
	}
	else
	{
		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
		for (int k = 0; k < place->BlocksPlaced; k++)
		{
			RenderMesh(place->mesh, ObjectGetTransform(place->objectList[k]));
		}
	}
}

void DestroyPlaceBlocks(PlaceBlock** place)
{
	if (place)
	{
		if ((*place)->source && (*place)->sprite)
		{
			FreeSprite(&((*place)->sprite));
		}
		freeMesh(&((*place)->mesh));
		delete *place;
		*place = NULL;
	}
	else
		return;
}