//------------------------------------------------------------------------------
//
// File Name:	ActionList.cpp
// Author(s):	TayLee Young (taylee.young@digipen.edu)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "ActionList.h"
#include "Math.h"
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

    DGL_Vec2 startPos;
    DGL_Vec2 endPos;
    DGL_Color startColor;
    DGL_Color endColor;
    float startVal;
    float endVal;
};


void initActionList(ActionList* action)
{
	memset(action, 0, sizeof(ActionList) * ACTIONLIST_SIZE);
}

void updateActionList(ActionList* action, float dt)
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
void initAction(ActionList* action, int object, float useTime, float delay, ActionTypes type)
{
    action->isInUse = true;
    action->currentType = type;
    action->currentTime = -delay;
    action->useTime = useTime;
    action->currentObject = object;
}

void destroyAction(ActionList* action, int object, float duration, float delay)
{
    ActionList* actionlist = FindOpenAction(action);
    if (!actionlist)
    {
        return;
    }

    initAction(actionlist, object, duration, delay, DestroyAction);
}