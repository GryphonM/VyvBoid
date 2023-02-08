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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Math.h"

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
    Mesh* boidMesh;
    Boid* boidsList[BOIDNUMBER];
};


Vector2D Cohesion(Boid* boid, BoidList* list)
{
    float count = 0;
    Vector2D AveragePos = Vector2D(0,0);
    Vector2D CoheasionVector = Vector2D(0, 0);
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
        CoheasionVector = (AveragePos / count) - boid->position;
    }
    return CoheasionVector;
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

                AverageDir += list->boidsList[i]->velocity.Normalized();
                count += 1;
            }
        }
    }
    if (count != 0)
    {
        AverageDir = AverageDir / count;
    }
    Vector2D AlignmentVector = AverageDir - boid->velocity;
    return AlignmentVector;
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

Boid* CreateBoid(BoidList* list, Vector2D posToSpawn)
{
    Boid* newBoid = new Boid;
    newBoid->isDead = false;
    newBoid->position.X(posToSpawn.X());
    newBoid->position.Y(posToSpawn.Y());
    newBoid->velocity.X(0);
    newBoid->velocity.Y(0);
    newBoid->previousVelocity.X(0);
    newBoid->previousVelocity.Y(0);
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
    newBoidList->CohesionWeight = 1;
    newBoidList->AlignmentWeight = 1;
    newBoidList->SeparationWeight = 1;
    newBoidList->AvoidanceWeight = 1;
    newBoidList->PreviousSpeedWeight = 1;
    newBoidList->maxSpeed = 1;
    newBoidList->minSpeed = 1;
    newBoidList->FriendRange = 100;
    newBoidList->SeparateRange = 100;
    newBoidList->AlignmentSmoothVal = .01f;
    newBoidList->boidColor = { 0.5f, 0.25f, 1.0f, 1.0f };
    newBoidList->boidMesh = SquareMesh(.5f, .5f, 0.f, 0.f, "Boid", newBoidList->boidColor);

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        newBoidList->boidsList[i] = NULL;
    }
    return newBoidList;
}

void DestroyBoidList(BoidList* list)
{
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
    Transform* trans = CreateTransform();
    Vector2D scale = Vector2D(10.0f, 10.0f);
    TransformSetScale(trans, scale);
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (list->boidsList[i]->isDead == false)
            {
                TransformSetPosition(trans, list->boidsList[i]->position);
                RenderMesh(list->boidMesh, trans);
            }
        }
    }
    DeleteTransform(trans);
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

