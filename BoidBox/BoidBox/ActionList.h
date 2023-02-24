//------------------------------------------------------------------------------
//
// File Name:	ActionList.h
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#pragma once

#include "DGL.h"
#define ACTIONLIST_SIZE 1024


#ifndef ACTIONLIST_H
#define ACTIONLIST_H

struct ActionList;

#if 0

struct ActionList
{
    ActionTypes currentType;
    bool isInUse;
    float useTime;
    float currentTime;
    int currentObject;

    DGL_Vec2 startPos;
    DGL_Vec2 endPos;
    DGL_Color startColor;
    DGL_Color endColor;
    float startVal;
    float endVal;
};

typedef enum
{
    NoAction = 0,
    MoveAction,
    RotateAction,
    ScaleAction,
    ColorAction,
    FadeAction,
    DestroyAction

} ActionTypes;
#endif

void initActionList(ActionList* action);
void updateActionList(ActionList* action, float dt);

ActionList* FindOpenAction(ActionList* action);
//void initAction(ActionList* action, int object, float useTime, float delay, ActionTypes type);
void destroyAction(ActionList* action, int object, float duration, float delay);
#endif