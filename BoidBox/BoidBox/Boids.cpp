//------------------------------------------------------------------------------
//
// File Name:	Hunters.cpp
// Author(s):	Tyler Dean (tyler.dean@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "DGL.h"
#include "Mesh.h"
#include "Transform.h"
#include "Hunters.h"
#include "Vector2D.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Math.h"
#include <string>

#define BOIDNUMBER 40

struct Boid
{
    Vector2D position;
    Vector2D velocity;
    Vector2D previousVelocity;

    float rotation;

    bool isDead;
};

struct BoidList
{
    float CohesionWeight;
    float AlignmentWeight;
    float SeparationWeight;
    float AvoidanceWeight;
    float PreviousSpeedWeight;
    float maxSpeed;
    float minSpeed;
    float FriendRange;
    float SeparateRange;
    float AlignmentSmoothVal;
    DGL_Color boidColor;
    Sprite* boidSprite;
    Boid* boidsList[BOIDNUMBER];
    Transform* trans;
};


Vector2D Cohesion(Boid* boid, BoidList* list)
{
    float count = 0;
    Vector2D AveragePos = Vector2D(0,0);
    Vector2D zeroVector = Vector2D(0, 0);
    for(int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->FriendRange * list->FriendRange) && boid->position != list->boidsList[i]->position && list->boidsList[i]->position != zeroVector)
            {
                AveragePos += list->boidsList[i]->position;
                count += 1;
            }
        }
    }
    if (count != 0)
    {
        return ((AveragePos / count) - boid->position);
    }
    return Vector2D(0, 0);
}

Vector2D Separation(Boid* boid, BoidList* list)
{
    Vector2D SeparatePos = Vector2D(0, 0);
    Vector2D zeroVector = Vector2D(0, 0);

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->SeparateRange * list->SeparateRange) && boid->position != list->boidsList[i]->position && list->boidsList[i]->position != zeroVector)
            {
                //this feels wierd but its what referance said to do
                SeparatePos += (boid->position - list->boidsList[i]->position) / (boid->position - list->boidsList[i]->position).Magnitude();
            }
        }
    }
    return SeparatePos;
}

Vector2D Alignment(Boid* boid, BoidList* list)
{
    float count = 0;
    Vector2D AverageDir = Vector2D(0, 0);
    Vector2D zeroVector = Vector2D(0, 0);

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->FriendRange * list->FriendRange) && boid->position != list->boidsList[i]->position && list->boidsList[i]->position != zeroVector)
            {
                Vector2D normalVec = AverageDir + list->boidsList[i]->velocity.Normalized();
               // AverageDir;
                count += 1;
            }
        }
    }
    if (count != 0)
    {
        AverageDir = AverageDir / count;
    }
    return AverageDir - boid->velocity;
}

void SetDirectionOfBoid(Vector2D Cohesion, Vector2D Alignment, Vector2D Separation, Boid* boid, BoidList* list, float dt)
{
 
    Vector2D BoidVelocity = (boid->previousVelocity * list->PreviousSpeedWeight) + (Cohesion * list->CohesionWeight) + (Alignment * list->AlignmentWeight) + (Separation * list->SeparationWeight);
    float speed = boid->velocity.Magnitude();
    Vector2D LerpedVelocity = Lerp(boid->velocity.Normalized(), BoidVelocity, list->AlignmentSmoothVal) * speed;
    float lerpMag = LerpedVelocity.Magnitude();
    if (lerpMag > list->maxSpeed)
    {
        LerpedVelocity = (LerpedVelocity / lerpMag) * list->maxSpeed;
    }
    if (lerpMag < list->minSpeed && lerpMag != 0)
    {
        LerpedVelocity = (LerpedVelocity / lerpMag) * list->minSpeed;
    }
    boid->velocity = LerpedVelocity;
    //float degToRot = Mathf.Atan2(rb.velocity.y, rb.velocity.x);
    //degToRot = degToRot * Mathf.Rad2Deg - 90;
    //boid.transform.eulerAngles = new Vector3(0, 0, degToRot);
    boid->previousVelocity = LerpedVelocity;
    boid->position += boid->velocity * dt;
    
}

void UpdateBoid(Boid* boid, BoidList* list, float dt)
{
    Vector2D CohesionVector = Cohesion(boid, list);
    Vector2D SeparationVector = Separation(boid, list);
    Vector2D AlignmentVector = Alignment(boid, list);
    SetDirectionOfBoid(CohesionVector, AlignmentVector, SeparationVector, boid, list, dt);
}

Boid* CreateBoid(BoidList* list, Vector2D posToSpawn = *new Vector2D)
{
    Boid* newBoid = new Boid;
    newBoid->isDead = false;
    newBoid->position.X(posToSpawn.X());
    newBoid->position.Y(posToSpawn.Y());
    newBoid->velocity.X(list->maxSpeed);
    newBoid->velocity.Y(list->maxSpeed);
    newBoid->previousVelocity.X(1);
    newBoid->previousVelocity.Y(1);
    newBoid->rotation = 0;
    return newBoid;
}

void DestroyBoids(BoidList* list)
{
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            delete list->boidsList[i];
            list->boidsList[i] = NULL;
        }
    }
}

BoidList* CreateBoidlist()
{
    BoidList* newBoidList = new BoidList;

    newBoidList->trans = CreateTransform(Vector2D(0,0), Vector2D(10, 10));
    newBoidList->CohesionWeight = 1;
    newBoidList->AlignmentWeight = 3;
    newBoidList->SeparationWeight = 3;
    newBoidList->AvoidanceWeight = 1;
    newBoidList->PreviousSpeedWeight = 1;
    newBoidList->maxSpeed = 30;
    newBoidList->minSpeed = 30;
    newBoidList->FriendRange = 250;
    newBoidList->SeparateRange = 150;
    newBoidList->AlignmentSmoothVal = .01f;
    newBoidList->boidColor = { 0.5f, 0.25f, 1.0f, 1.0f };
    newBoidList->boidSprite = CreateSprite();
    SpriteSetMesh(newBoidList->boidSprite, SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "AHHHHH", { 0.99f, 0.73f, .01f, 1.0f }));

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        newBoidList->boidsList[i] = NULL;
    }
    return newBoidList;
}

void UpdateBoidlistParamaters(BoidList* list, std::string filename = "\n")
{
    if (filename != "\n")
    {
    }
}

void DestroyBoidList(BoidList* list)
{   
    FreeSprite(&list->boidSprite);
    DeleteTransform(&list->trans);
    DestroyBoids(list);
    delete list;
}

void CheckBoidCollisions(BoidList* list)
{
    return;
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (list->boidsList[i]->isDead == false)
            {
                //check colls here
            }
        }
    }
}

void RenderBoids(BoidList* list)
{
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (list->boidsList[i]->isDead == false)
            {
                TransformSetPosition(list->trans, list->boidsList[i]->position);
                RenderSprite(list->boidSprite, list->trans);
            }
        }
    }
}

void RunBoids(BoidList* list, float dt)
{
    CheckBoidCollisions(list);
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (list->boidsList[i]->isDead == false)
            {
                UpdateBoid(list->boidsList[i], list, dt);
            }
        }
    }
}

void AddBoidToList(BoidList* list, Vector2D posToSpawn = Vector2D())
{
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] == NULL)
        {
            list->boidsList[i] = CreateBoid(list, posToSpawn);
            return;
        }
    }
}

/*

Vector2D Avoidance(Boid* boid)
{
    Vector2D AvoidanceVector = {0,0};
    for (int i = 0; i < objectsToAvoid.Length; i++)
    {
        if (Vector2.Distance(objectsToAvoid[i].gameObject.transform.position, boid.transform.position) < AvoidRange && boid.transform.position != objectsToAvoid[i].gameObject.transform.position)
        {
            AvoidanceVector += (boid.transform.position - objectsToAvoid[i].gameObject.transform.position) / (boid.transform.position - objectsToAvoid[i].gameObject.transform.position).magnitude;
        }
    }
    return AvoidanceVector;
}
*/

