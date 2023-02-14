//------------------------------------------------------------------------------
//
// File Name:	Mesh.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "DGL.h"
#include "Vector2D.h"
#include "Mesh.h"
#include "Transform.h"
#include <stdlib.h>

struct Mesh
{
	char meshName[32];

	DGL_Mesh* source;

	DGL_DrawMode drawMode;
};

Mesh* SquareMesh(float halfX, float halfY, float UOffset, float VOffset, const char* meshName, DGL_Color color)
{
	//DGL_Color color = { 1.0, 0.0, 1.0, 1.0 };
	Mesh* mesh = new Mesh;

	if (mesh)
	{
		// thank you gryph!! I forgor this part lol
		mesh->drawMode = DGL_DM_TRIANGLELIST;
		strcpy(mesh->meshName, meshName);

		DGL_Graphics_StartMesh();

		DGL_Graphics_AddTriangle(Vector2D(-halfX, -halfY), &color, Vector2D(0.0f, 0.0f),
			Vector2D(halfX, halfY), &color, Vector2D(UOffset, VOffset),
			Vector2D(halfX, -halfY), &color, Vector2D(UOffset, 0.0f));

		DGL_Graphics_AddTriangle(Vector2D(-halfX, -halfY), &color, Vector2D(0.0f, 0.0f),
			Vector2D(-halfX, halfY), &color, Vector2D(0.0f, VOffset),
			Vector2D(halfX, halfY), &color, Vector2D(UOffset, VOffset));

		mesh->source = DGL_Graphics_EndMesh();

		return (mesh);
	}
	else
	{
		return NULL;
	}
}
void RenderMesh(const Mesh* mesh, const Transform* transform)
{
	DGL_Graphics_SetCB_TransformData(TransformGetPosition(transform), TransformGetScale(transform), TransformGetRotation(transform));
	DGL_Graphics_DrawMesh(mesh->source, mesh->drawMode);
}

void RenderMesh(const Mesh* mesh)
{
	DGL_Graphics_DrawMesh(mesh->source, mesh->drawMode);
}

void freeMesh(Mesh** mesh)
{
	if (mesh && *mesh)
	{
		DGL_Graphics_FreeMesh(&((*mesh)->source));
		delete* mesh;
		*mesh = NULL;
	}
}
