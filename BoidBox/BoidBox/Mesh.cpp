//------------------------------------------------------------------------------
//
// File Name:	Mesh.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
//#include "stdafx.h"
#include "DGL.h"
#include "Mesh.h"
#include <stdlib.h>

typedef struct Mesh mesh;

typedef struct Mesh
{
	char name[32];

	DGL_Mesh* source;

	DGL_DrawMode drawMode;
};

mesh* SquareMesh(float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	// dont ask why it doesnt work lmao

	Mesh* mesh = new Mesh;

	if (mesh)
	{
		DGL_Graphics_StartMesh();

		// sorry shilling
		DGL_Graphics_AddTriangle(&(DGL_Vec2) { -xHalfSize, -yHalfSize }, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { 0.0f, 0.0f },
			& (DGL_Vec2) { xHalfSize, yHalfSize }, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { uSize, vSize },
			& (DGL_Vec2) { xHalfSize, -yHalfSize }, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { uSize, 0.0f });

		DGL_Graphics_AddTriangle(&(DGL_Vec2) { -xHalfSize, -yHalfSize }, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { 0.0f, 0.0f },
			& (DGL_Vec2) { -xHalfSize, yHalfSize}, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { 0.0f, vSize }, 
			& (DGL_Vec2) { xHalfSize, yHalfSize }, & (DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, & (DGL_Vec2) { uSize, vSize });

		mesh->source = DGL_Graphics_EndMesh();

		//strcpy_s(mesh->name, _countof(mesh->name), name);

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
