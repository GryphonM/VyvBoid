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
#include "Boids.h"

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
	
	int avoidCounter;

	ObjectList objectList;

	BoidList* boids;

	bool sound;
};

PlaceBlock* CreatePlaceBlocks(const char* name, BoidList* boids, const char* file, int max_blocks)
{ 
	PlaceBlock* place = new PlaceBlock;

	if (place)
	{
		place->boids = boids;
		place->avoidCounter = 0;
		place->sound = false;
		place->BlocksPlaced = 0;
		place->maxBlocks = max_blocks;
		place->offScreen = (Vector2D)OFFSCREEN;
		place->source = NULL;
		place->sprite = NULL;
		if (file == "none")
		{
			place->color = { 1.0f, 0.1f, 0.1f, 1.0f };
			place->sprite = CreateSprite();
			place->mesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, name, place->color);
			SpriteSetMesh(place->sprite, place->mesh);
			if (place->mesh)
			{
				return place;
			}
		}
		else
		{
			place->color = { 1.0f, 0.0f, 1.0f, 1.0f };
			place->mesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, name, place->color);
			if (place->mesh)
			{
				place->sprite = CreateSprite();
				place->source = CreateSpriteSource();
				if (place->sprite && place->source)
				{
					LoadSpriteSourceTexture(place->source, 1, 1, file);
					SpriteSetMesh(place->sprite, place->mesh);
					SpriteSetSource(place->sprite, place->source);
					return place;
				}
			}
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
			Transform* transform = CreateTransform(mish, Vector2D(10, 10));
			place->objectList.PushFront(ObjectCreate("Block" + place->BlocksPlaced, transform));
			AddAvoidToList(place->boids, TransformGetPosition(transform));
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
				if ((mish.X() <= (position.X() + (scale.X() / 2.0f)))
				&& (mish.X() >= (position.X() - (scale.X() / 2.0f)))
				&& (mish.Y() <= (position.Y() + (scale.Y() / 2.0f)))
				&& (mish.Y() >= (position.Y() - (scale.Y() / 2.0f))))
				{
					int pos = FindAvoid(place->boids, position);
					ObjectListRemove(&place->objectList, place->objectList[i]);
					DeleteAvoidBlock(place->boids, pos);
					place->BlocksPlaced--;
					if (sound)
					{
						ChangeVolume(sound, 10000.0f);
						PlaySound(sound);
					}
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
		if (place->mesh)
		{
			DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
			for (int k = 0; k < place->BlocksPlaced; k++)
			{
				RenderSprite(place->sprite, ObjectGetTransform(place->objectList[k]));
			}
		}
	}
}

void DestroyPlaceBlocks(PlaceBlock** place)
{
	if (place)
	{
		DestroyAvoids((*place)->boids);
		if ((*place)->sprite)
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
