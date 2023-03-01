//------------------------------------------------------------------------------
//
// File Name:	Hunters.cpp
// Author(s):	Tyler Dean (tyler.dean@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "Boids.h"
#include "DGL.h"
#include "Mesh.h"
#include "Transform.h"
#include "Collision.h"
#include "Hunters.h"
#include "Vector2D.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Stream.h"
#include "Mesh.h"
#include "Math.h"
#include <string>

#define BOIDNUMBER 1000
#define AVOIDNUMBER 50

struct Boid
{
    Vector2D position;
    Vector2D velocity;
    Vector2D previousVelocity;

    float rotation;

    bool isDead;
};

struct Avoid
{
    Vector2D position;
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
    float AvoidRange;
    float AlignmentSmoothVal;
    DGL_Color boidColor;
    DGL_Color avoidColor;
    Sprite* boidSprite;
    Mesh* boidMesh;
    Sprite* avoidSprite;
    Mesh* avoidMesh;
    Boid* boidsList[BOIDNUMBER];
    Avoid* avoidsList[AVOIDNUMBER];
    Transform* trans;
};

/*
Vector2D Cohesion(Boid* boid, BoidList* list)
{
    float count = 0;
    Vector2D AveragePos = Vector2D(0,0);
    Vector2D zeroVector = Vector2D(0, 0);
    for(int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->FriendRange * list->FriendRange) && boid->position != list->boidsList[i]->position)
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
    return zeroVector;
}

Vector2D Separation(Boid* boid, BoidList* list)
{
    Vector2D SeparatePos = Vector2D(0, 0);
    Vector2D zeroVector = Vector2D(0, 0);

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->SeparateRange * list->SeparateRange) && boid->position != list->boidsList[i]->position)
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
            if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->FriendRange * list->FriendRange) && boid->position != list->boidsList[i]->position)
            {
                AverageDir = AverageDir + list->boidsList[i]->velocity.Normalized();
                count += 1;
            }
        }
    }
    if (count != 0)
    {
        AverageDir = AverageDir / count;
    }
    return (AverageDir - boid->velocity);
}

Vector2D Avoidance(Boid* boid, BoidList* list)
{
    Vector2D AvoidancePos = Vector2D(0, 0);
    Vector2D zeroVector = Vector2D(0, 0);

    for (int i = 0; i < AVOIDNUMBER; i++)
    {
        if (list->avoidsList[i] != NULL)
        {
            if (Vector2D::DistanceSquared(list->avoidsList[i]->position, boid->position) < (list->AvoidRange * list->AvoidRange) && boid->position != list->avoidsList[i]->position)
            {
                //this feels wierd but its what referance said to do
                AvoidancePos += (boid->position - list->avoidsList[i]->position) / (boid->position - list->avoidsList[i]->position).Magnitude();
            }
        }
    }
    return AvoidancePos;
}

void SetDirectionOfBoid(Vector2D Cohesion, Vector2D Alignment, Vector2D Separation, Vector2D Avoidance, Boid* boid, BoidList* list, float dt)
{
    Vector2D BoidVelocity = (boid->previousVelocity * list->PreviousSpeedWeight) + (Cohesion * list->CohesionWeight) + (Alignment * list->AlignmentWeight) + (Separation * list->SeparationWeight) + (Avoidance * list->AvoidanceWeight);
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
    boid->previousVelocity = LerpedVelocity;
    boid->velocity = LerpedVelocity;
    //float degToRot = Mathf.Atan2(rb.velocity.y, rb.velocity.x);
    //degToRot = degToRot * Mathf.Rad2Deg - 90;
    //boid.transform.eulerAngles = new Vector3(0, 0, degToRot);
    boid->position += boid->velocity * dt;

}
*/
Vector2D CalculateDirection(Boid* boid, BoidList* list)
{
    Vector2D CohesionVector = Vector2D(0, 0);
    Vector2D AlignmentVector = Vector2D(0, 0);
    Vector2D AvoidanceVector = Vector2D(0, 0);
    Vector2D SeparateVector = Vector2D(0, 0);

    Vector2D CohesionAveragePos = Vector2D(0, 0);

    Vector2D SeparatePos = Vector2D(0, 0);

    float count = 0;
    Vector2D AverageDir = Vector2D(0, 0);

    Vector2D AvoidancePos = Vector2D(0, 0);
    Vector2D zeroVector = Vector2D(0, 0);

    for (int i = 0; i < AVOIDNUMBER; i++)
    {
        if (list->avoidsList[i] != NULL)
        {
            //avoidance
            if (Vector2D::DistanceSquared(list->avoidsList[i]->position, boid->position) < (list->AvoidRange * list->AvoidRange) && boid->position != list->avoidsList[i]->position)
            {
                //this feels wierd but its what referance said to do
                AvoidancePos += (boid->position - list->avoidsList[i]->position) / (boid->position - list->avoidsList[i]->position).Magnitude();
            }          
        }
    }
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] != NULL)
        {
            if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->FriendRange * list->FriendRange) && boid->position != list->boidsList[i]->position)
            {
                //alignment
                AverageDir = AverageDir + list->boidsList[i]->velocity.Normalized();

                //coheason
                CohesionAveragePos += list->boidsList[i]->position;

                //update count for both alignment and coheason
                count += 1;

                //separate
                if (Vector2D::DistanceSquared(list->boidsList[i]->position, boid->position) < (list->SeparateRange * list->SeparateRange) && boid->position != list->boidsList[i]->position)
                {
                    //this feels wierd but its what referance said to do
                    SeparatePos += (boid->position - list->boidsList[i]->position) / (boid->position - list->boidsList[i]->position).Magnitude();
                }
            }
        }
    }
    if (count != 0)
    {
        CohesionVector = ((CohesionAveragePos / count) - boid->position);
        AverageDir = AverageDir / count;

    }
    AlignmentVector = (AverageDir - boid->velocity);
    AvoidanceVector = AvoidancePos;
    SeparateVector = SeparatePos;
    Vector2D BoidVelocity = (boid->previousVelocity * list->PreviousSpeedWeight) + (CohesionVector * list->CohesionWeight) + (AlignmentVector * list->AlignmentWeight) + (SeparateVector * list->SeparationWeight) + (AvoidanceVector * list->AvoidanceWeight);
    return BoidVelocity;
}

void SetDirectionOfBoid(Vector2D BoidVelocity, Boid* boid, BoidList* list, float dt)
{
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
    boid->previousVelocity = LerpedVelocity;
    boid->velocity = LerpedVelocity;
    //float degToRot = Mathf.Atan2(rb.velocity.y, rb.velocity.x);
    //degToRot = degToRot * Mathf.Rad2Deg - 90;
    //boid.transform.eulerAngles = new Vector3(0, 0, degToRot);
    boid->position += boid->velocity * dt;
    
}

void UpdateBoid(Boid* boid, BoidList* list, float dt)
{
    Vector2D DirectionVector = CalculateDirection(boid, list);
    SetDirectionOfBoid(DirectionVector, boid, list, dt);
}

Boid* CreateBoid(BoidList* list, Vector2D posToSpawn)
{
    Boid* newBoid = new Boid;
    newBoid->isDead = false;
    newBoid->position.X(posToSpawn.X());
    newBoid->position.Y(posToSpawn.Y());
    newBoid->velocity.X(50);
    newBoid->velocity.Y(100);
    newBoid->previousVelocity.X(100);
    newBoid->previousVelocity.Y(100);
    newBoid->rotation = 0;
    return newBoid;
}

Avoid* CreateAvoid(BoidList* list, Vector2D posToSpawn)
{
    Avoid* newAvoid = new Avoid;
    newAvoid->position = posToSpawn;
    return newAvoid;
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

void DestroyAvoids(BoidList* list)
{
    for (int i = 0; i < AVOIDNUMBER; i++)
    {
        if (list->avoidsList[i] != NULL)
        {
            delete list->avoidsList[i];
            list->avoidsList[i] = NULL;
        }
    }
}
BoidList* CreateBoidlist()
{
    BoidList* newBoidList = new BoidList;

    newBoidList->trans = CreateTransform(Vector2D(0,0), Vector2D(10, 10));
    newBoidList->boidSprite = CreateSprite();
    newBoidList->avoidSprite = CreateSprite();

    newBoidList->boidMesh = SquareMesh(1.0f, 0.0f, 0.82f, 1.0f, "avoidMesh", newBoidList->avoidColor);
    SpriteSetMesh(newBoidList->avoidSprite, newBoidList->boidMesh);

    newBoidList->avoidMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "boidMesh", newBoidList->boidColor);
    SpriteSetMesh(newBoidList->boidSprite, newBoidList->avoidMesh);

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        newBoidList->boidsList[i] = NULL;
    }
    for (int i = 0; i < AVOIDNUMBER; i++)
    {
        newBoidList->avoidsList[i] = NULL;
    }

    return newBoidList;
}

void DestroyBoidList(BoidList* list)
{   
    FreeSprite(&list->boidSprite);
    freeMesh(&list->boidMesh);
    FreeSprite(&list->avoidSprite);
    freeMesh(&list->avoidMesh);
    DeleteTransform(&list->trans);
    DestroyBoids(list);
    DestroyAvoids(list);
    delete list;
}

void KillBoid(Boid* boid)
{
    if (boid)
        boid->isDead = true;
}

int CheckBoidCollisions(const BoidList* list, Vector2D pos, float scale, void (*handler)(Boid*))
{
    int count = 0;
    for (int i = 0; i < BOIDNUMBER; ++i)
    {
        if (list->boidsList[i])
        {
            if (!list->boidsList[i]->isDead)
            {
                if (CircleCircleCollision(list->boidsList[i]->position, TransformGetScale(list->trans).X()/2, pos, scale))
                {
                    handler(list->boidsList[i]);
                    ++count;
                }
            }
        }
    }
    return count;
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

void RenderAvoids(BoidList* list)
{
    for (int i = 0; i < AVOIDNUMBER; i++)
    {
        if (list->avoidsList[i] != NULL)
        {
            TransformSetPosition(list->trans, list->avoidsList[i]->position);
            RenderSprite(list->avoidSprite, list->trans);
        }
    }
}

void RunBoids(BoidList* list, float dt)
{
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

void AddBoidToList(BoidList* list, Vector2D posToSpawn, Vector2D initialVelocity)
{
    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (list->boidsList[i] == NULL)
        {
            list->boidsList[i] = CreateBoid(list, posToSpawn);
            list->boidsList[i]->velocity = initialVelocity;
            return;
        }
    }
}

void AddAvoidToList(BoidList* list, Vector2D posToSpawn)
{
    for (int i = 0; i < AVOIDNUMBER; i++)
    {
        if (list->avoidsList[i] == NULL)
        {
            list->avoidsList[i] = CreateAvoid(list, posToSpawn);
            return;
        }
    }
}

void UpdateBoidlistParamaters(BoidList* list, std::string filename)
{
    if (list && filename != "")
    {
        TextStream stream(filename);
        while (!stream.EndOfFile())
        {
            std::string tokenWord = stream.ReadWord();
            if (tokenWord == "CohesionWeight")
            {
                list->CohesionWeight = stream.ReadFloat();
            }
            else if (tokenWord == "AlignmentWeight")
            {
                list->AlignmentWeight = stream.ReadFloat();
            }
            else if (tokenWord == "SeparationWeight")
            {
                list->SeparationWeight = stream.ReadFloat();
            }
            else if (tokenWord == "AvoidanceWeight")
            {
                list->AvoidanceWeight = stream.ReadFloat();
            }
            else if (tokenWord == "PreviousSpeedWeight")
            {
                list->PreviousSpeedWeight = stream.ReadFloat();
            }
            else if (tokenWord == "maxSpeed")
            {
                list->maxSpeed = stream.ReadFloat();
            }
            else if (tokenWord == "minSpeed")
            {
                list->minSpeed = stream.ReadFloat();
            }
            else if (tokenWord == "FriendRange")
            {
                list->FriendRange = stream.ReadFloat();
            }
            else if (tokenWord == "SeparateRange")
            {
                list->SeparateRange = stream.ReadFloat();
            }
            else if (tokenWord == "AvoidRange")
            {
                list->AvoidRange = stream.ReadFloat();
            }
            else if (tokenWord == "AlignmentSmoothVal")
            {
                list->AlignmentSmoothVal = stream.ReadFloat();
            }
            else if (tokenWord == "boidColor")
            {
                DGL_Color newBoidColor = {stream.ReadFloat(), stream.ReadFloat(), stream.ReadFloat(), stream.ReadFloat()};
                list->boidColor = newBoidColor;
                if (list->boidMesh)
                    freeMesh(&list->boidMesh);
                list->boidMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "boidMesh", list->boidColor);
                SpriteSetMesh(list->boidSprite, list->boidMesh);
            }
            else if (tokenWord == "avoidColor")
            {
                DGL_Color newBoidColor = { stream.ReadFloat(), stream.ReadFloat(), stream.ReadFloat(), stream.ReadFloat() };
                list->avoidColor = newBoidColor;
                if (list->avoidMesh)
                    freeMesh(&list->avoidMesh);
                list->avoidMesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "avoidMesh", list->avoidColor);
                SpriteSetMesh(list->avoidSprite, list->avoidMesh);
            }
        }
    }
}

void DeleteAvoidBlock(BoidList* boids, int i)
{
    delete boids->avoidsList[i];
    boids->avoidsList[i] = NULL;
}

int FindAvoid(BoidList* boid, Vector2D pos)
{
    for (int i = 0; i < AVOIDNUMBER; i++)
    {
        if (boid->avoidsList[i] != NULL)
            if (pos == boid->avoidsList[i]->position)
                return i;
    }
    return NULL;
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

