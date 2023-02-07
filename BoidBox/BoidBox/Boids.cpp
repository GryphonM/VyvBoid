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

#define BOIDNUMBER 40
struct BoidList
{
    float CohesionWeight = 1;
    float AlignmentWeight = 1;
    float SeparationWeight = 1;
    float FollowWeight = .5f;
    float AvoidanceWeight = 1;
    float PreviousSpeedWeight = 1;
    float maxSpeed = 15;
    float minSpeed = 5;
    float FriendRange = 5;
    float SeparateRange = 5;
    float AvoidRange = 5;
    float AlignmentSmoothVal = .01f;
    Boid boidsList[BOIDNUMBER];
};

struct Boid
{
	Vector2D position;
    Vector2D velocity;
    Vector2D previousVelocity;

	float rotation;

    bool isDead;
};

Vector2D Cohesion(Boid* boid, BoidList* list)
{
    int count = 0;
    Vector2D AveragePos = { 0, 0 };
    Vector2D CoheasionVector = {0,0};
    Vector2D zeroVector = {0,0};
    for(int i = 0; i < BOIDNUMBER; i++)
    {
        if (Vector2D::DistanceSquared(list->boidsList[i].position, boid->position) < (list->FriendRange * list->FriendRange) && boid->position != list->boidsList[i].position && list->boidsList[i].position != zeroVector)
        {
            AveragePos += list->boidsList[i].position;
            count += 1;
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
    Vector2D SeparatePos = {0,0};
    Vector2D zeroVector = { 0,0 };

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (Vector2D::DistanceSquared(list->boidsList[i].position, boid->position) < (list->SeparateRange * list->SeparateRange) && boid->position != list->boidsList[i].position && list->boidsList[i].position != zeroVector)
        {
            SeparatePos += (boid->position - list->boidsList[i].position) / (boid->position - list->boidsList[i].position).magnitude;
        }
    }
    return SeparatePos;
}

Vector2D Alignment(Boid* boid, BoidList* list)
{
    int count = 0;
    Vector2D AverageDir = {0,0};
    Vector2D zeroVector = { 0,0 };

    for (int i = 0; i < BOIDNUMBER; i++)
    {
        if (Vector2D::DistanceSquared(list->boidsList[i].position, boid->position) < (list->FriendRange * list->FriendRange) && boid->position != list->boidsList[i].position && list->boidsList[i].position != zeroVector)
        {

            AverageDir += list->boidsList[i].velocity.normalized;
            count += 1;
        }
    }
    if (count != 0)
    {
        AverageDir = AverageDir / count;
    }
    Vector2D AlignmentVector = AverageDir - boid->velocity;
    return AlignmentVector;
}

void SetDirectionOfBoid(Vector2D Cohesion, Vector2D Alignment, Vector2D Separation, Boid* boid, BoidList* list)
{
 
    Vector2D BoidVelocity = (boid->previousVelocity * list->PreviousSpeedWeight) + (Cohesion * list->CohesionWeight) + (Alignment * list->AlignmentWeight) + (Separation * list->SeparationWeight);
    float speed = boid->velocity.magnitude;
    Vector2D LerpedVelocity = PUT LERP HERE WHEN GRYPHON MAKES IT(rb.velocity.normalized, BoidVelocity, AlignmentSmoothVal) * speed;
    if (LerpedVelocity.magnitude > list->maxSpeed)
    {
        LerpedVelocity = (LerpedVelocity / LerpedVelocity.magnitude) * list->maxSpeed;
    }
    if (LerpedVelocity.magnitude < list->minSpeed && LerpedVelocity.magnitude != 0)
    {
        LerpedVelocity = (LerpedVelocity / LerpedVelocity.magnitude) * list->minSpeed;
    }
    boid->velocity = LerpedVelocity;
    //float degToRot = Mathf.Atan2(rb.velocity.y, rb.velocity.x);
    //degToRot = degToRot * Mathf.Rad2Deg - 90;
    //boid.transform.eulerAngles = new Vector3(0, 0, degToRot);
    boid->previousVelocity = LerpedVelocity;
}

void UpdateBoid(Boid* boid, BoidList* list)
{
    boid->velocity * 150;
    Vector2D CohesionVector = Cohesion(boid, list);
    Vector2D SeparationVector = Separation(boid, list);
    Vector2D AlignmentVector = Alignment(boid, list);
    SetDirectionOfBoid(CohesionVector, AlignmentVector, SeparationVector, boid, list);
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

