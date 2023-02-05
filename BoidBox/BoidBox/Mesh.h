//------------------------------------------------------------------------------
//
// File Name:	Mesh.h
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

#include "DGL.h"
#include "Transform.h"

typedef struct Mesh mesh;

#if 0
typedef struct Mesh
{
	char meshName[32];

	const DGL_Mesh* source;
};
#endif

mesh* SquareMesh(float halfX, float halfY, float UOffset, float VOffset, const char* meshName);
void RenderMesh(const mesh* mesh, const Transform* transform);
void freeMesh(mesh** mesh);

#endif