//------------------------------------------------------------------------------
//
// File Name:	Mesh.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

//
// HEY DONT USE THIS FILE RN THANKS SORRY
//

//#include "stdafx.h"
#include "DGL.h"
#include "Vector2D.h"
#include "Mesh.h"
#include <stdlib.h>

struct Mesh
{
	char name[32];

	DGL_Mesh* source;

	DGL_DrawMode drawMode;
};

Mesh* SquareMesh(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	// dont ask why it doesnt work lmao

	DGL_Color meshColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	Mesh* mesh = new Mesh;

	if (mesh)
	{
		DGL_Graphics_StartMesh();

		// sorry shilling
		DGL_Graphics_AddTriangle(Vector2D(-xHalfSize, -yHalfSize), &meshColor, Vector2D(0.0f, 0.0f),
			Vector2D(xHalfSize, yHalfSize), &meshColor, Vector2D(uSize, vSize),
			Vector2D(xHalfSize, -yHalfSize), &meshColor, Vector2D(uSize, 0.0f));

		DGL_Graphics_AddTriangle(Vector2D(-xHalfSize, -yHalfSize), &meshColor, Vector2D(0.0f, 0.0f),
			Vector2D(-xHalfSize, yHalfSize), &meshColor, Vector2D(0.0f, vSize),
			Vector2D(xHalfSize, yHalfSize), &meshColor, Vector2D(uSize, vSize));

		mesh->source = DGL_Graphics_EndMesh();

		return (mesh);
	}
	else
	{
		return NULL;
	}
}
void RenderMesh(const mesh* mesh)
{
	DGL_Graphics_DrawMesh(mesh->source, mesh->drawMode);
}
void freeMesh(mesh** mesh)
{
	DGL_Graphics_FreeMesh(&((*mesh)->source));
	delete mesh;
	mesh = NULL;
}
