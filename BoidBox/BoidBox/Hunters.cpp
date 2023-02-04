//------------------------------------------------------------------------------
//
// File Name:	Hunters.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "DGL.h"
#include "Mesh.h"
#include "Transform.h"
#include "Hunters.h"
#include "Vector2D.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Hunters
{
	// perhaaps unnecessary idk yet
	//DGL_Vec2 pos;
	//DGL_Vec2 uv;

	//const DGL_Texture* texture;

	//static const DGL_Vec2 scale;

	float radius;
	float width;
	float height;
	float halfWidth;
	float halfHeight;

	// collision stuff 
	//float xDistance;
	//float yDistance;
	//float totalDistance;
};

Hunters* InitCrosshair(const Mesh* mesh, Hunters* hunter, float width, float height, float radius)
{
	DGL_Texture* crosshairTexture = DGL_Graphics_LoadTexture("./Assets/crosshair.png");
	if (mesh)
	{

		hunter->width = width;
		hunter->height = height;
		hunter->halfWidth = hunter->width / 2.0f;
		hunter->halfWidth = hunter->width / 2.0f;
		hunter->radius = radius;

		DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
        DGL_Graphics_SetTexture(crosshairTexture);

		//array of crosshairs for diff positions
	}

	return hunter;
}

void DrawCrosshair(const Mesh* mesh, const Transform* transform)
{
	RenderMesh(mesh, transform);
}