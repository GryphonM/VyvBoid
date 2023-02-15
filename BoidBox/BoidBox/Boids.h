//------------------------------------------------------------------------------
//
// File Name:	Hunters.h
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "DGL.h"

#include "Mesh.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BOIDS_H
#define BOIDS_H

struct BoidList;

struct Boid;

#if 0
//stuct goes here
#endif


#endif
void RenderBoids(BoidList* list);
void RunBoids(BoidList* list, float dt);
void AddBoidToList(BoidList* list, Vector2D posToSpawn = Vector2D());
void DestroyBoidList(BoidList* list);
BoidList* CreateBoidlist(std::string filename = "\n");
void UpdateBoidlistParamaters(BoidList* list, std::string filename = "\n");