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
#include <string>

#ifndef BOIDS_H
#define BOIDS_H

struct BoidList;

struct Boid;

#if 0
//stuct goes here
#endif

void RenderBoids(BoidList* list);
void RunBoids(BoidList* list, float dt);
void AddBoidToList(BoidList* list, Vector2D posToSpawn = Vector2D(), Vector2D initialVelcity = Vector2D(1, 1));
void DestroyBoidList(BoidList* list);
void DestroyAvoids(BoidList* list);
void KillBoid(Boid* boid);
int CheckBoidCollisions(const BoidList* list, Vector2D pos, float scale, void (*handler)(Boid*));
void AddAvoidToList(BoidList* list, Vector2D posToSpawn = Vector2D());
BoidList* CreateBoidlist();
void UpdateBoidlistParamaters(BoidList* list, std::string filename);
void RenderAvoids(BoidList* list);
#endif

