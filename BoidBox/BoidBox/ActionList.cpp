//------------------------------------------------------------------------------
//
// File Name:	ActionList.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "ActionList.h"
#include "Vector2D.h"
#include "DGL.h"
#include "Math.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

struct ActionList
{
    ActionTypes currentType;
    bool isInUse;
    float useTime;
    float currentTime;
    int currentObject;

    Vector2D startPos;
    Vector2D endPos;
    DGL_Color startColor;
    DGL_Color endColor;
    float startVal;
    float endVal;
};

///////////////////////////////////////////////////////////////////////

// these could prolly go to math.h

float AddSine(float percent)
{
    return (float)sin(percent * M_PI * 0.5f);
}

float AddSqrt(float percent)
{
    return sqrtf(percent);
}

///////////////////////////////////////////////////////////////////////

void MoveUpdate(Vector2D* objectPos, Vector2D start, Vector2D end, float percent)
{
    percent = AddSine(percent);

    // interp
    objectPos->X(start.X() * (end.X() - start.X()) * percent);
    objectPos->Y(start.Y() * (end.Y() - start.Y()) * percent);
}

void RotateUpdate(float* objectRotation, float start, float end, float percent)
{
    percent = AddSine(percent);
    *objectRotation = start + (end - start) * percent;
}

void ScaleUpdate(float* objectScale, float start, float end, float percent)
{
    *objectScale = start + (end - start) * percent;
}

// color update requires object stuff with color attached

void FadeUpdate(float* objectAlpha, float start, float end, float percent)
{
    *objectAlpha = start + (end - start) * percent;
}

void InitActionList(ActionList* action)
{
	memset(action, 0, sizeof(ActionList) * ACTIONLIST_SIZE);
}

void UpdateActionList(ActionList* action, float dt)
{
	for (int i = 0; i < ACTIONLIST_SIZE; ++i)
	{
		if (!action[i].isInUse)
			continue;

		ActionList* actionList = action + i;

		//game object
		//
		// if (!object)
		// {
		//   actionList->isInUse = false;
		// }
		//

        actionList->currentTime += dt;
        
        // if less than zero
        float timePassed = actionList->currentTime / actionList->useTime;
        if (timePassed > 1.0f)
        {
            timePassed = 1.0f;
        }

        switch (actionList->currentType)
        {
        case MoveAction:
            break;
        case RotateAction:
            break;
        case ScaleAction:
            break;
        case ColorAction:
            break;
        case FadeAction:
            break;
        case DestroyAction:
            if (timePassed >= 1.0f)
            {
                //destroy object
            }
            break;
        default:
            break;
        }

        if (actionList->currentTime >= actionList->useTime)
        {
            actionList->isInUse = false;
        }
	}
}

ActionList* FindOpenAction(ActionList* action)
{
    for (int i = 0; i < ACTIONLIST_SIZE; ++i)
    {
        if (!action[i].isInUse)
        {
            return action + i;
        }
    }
    
    return NULL;
}

//delay is bad time but i havent decided what yet lol
void InitAction(ActionList* action, int object, float useTime, float delay, ActionTypes type)
{
    action->isInUse = true;
    action->currentType = type;
    action->currentTime = -delay;
    action->useTime = useTime;
    action->currentObject = object;
}

void AddDeleteAction(ActionList* action, int object, float duration, float delay)
{
    ActionList* actionlist = FindOpenAction(action);
    if (!actionlist)
    {
        return;
    }

    InitAction(actionlist, object, duration, delay, DestroyAction);
}

void AddMoveAction(ActionList* action, int object, Vector2D startPos, Vector2D endPos, float time, float delay)
{
    ActionList* actionlist = FindOpenAction(action);
    if (!actionlist)
    {
        return;
    }
    InitAction(actionlist, object, time, delay, MoveAction);
    actionlist->startPos = startPos;
    actionlist->endPos = endPos;
}

void AddRotateAction(ActionList* action, int object, float start, float end, float time, float delay)
{
    ActionList* actionlist = FindOpenAction(action);
    if (!actionlist)
    {
        return;
    }
    InitAction(actionlist, object, time, delay, RotateAction);
    actionlist->startVal = start;
    actionlist->endVal = end;
}

void AddScaleAction(ActionList* action, int object, float start, float end, float time, float delay)
{
    ActionList* actionlist = FindOpenAction(action);
    if (!actionlist)
    {
        return;
    }
    InitAction(actionlist, object, time, delay, ScaleAction);
    actionlist->startVal = start;
    actionlist->endVal = end;
}

void AddColorAction(ActionList* action, int object, DGL_Color startingColor, DGL_Color endingColor, float time, float delay)
{
    ActionList* actionlist = FindOpenAction(action);
    if (!actionlist)
    {
        return;
    }
    InitAction(actionlist, object, time, delay, ColorAction);
    actionlist->startColor = startingColor;
    actionlist->endColor = endingColor;
}

void AddFadeAction(ActionList* action, int object, float start, float end, float time, float delay)
{
    ActionList* actionlist = FindOpenAction(action);
    if (!actionlist)
    {
        return;
    }
    InitAction(actionlist, object, time, delay, FadeAction);
    actionlist->startVal = start;
    actionlist->endVal = end;
}