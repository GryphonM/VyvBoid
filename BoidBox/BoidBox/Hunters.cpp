//------------------------------------------------------------------------------
//
// File Name:	Hunters.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "DGL.h"
#include "Hunters.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Hunters
{
	DGL_Vec2 pos;
	DGL_Vec2 uv;

	static const DGL_Vec2 scaleColored;

	float radius;
	float width;
	float height;
	float halfWidth;
	float halfHeight;
	float xDistance;
	float yDistance;
	float totalDistance;
};

// hooo boy