//------------------------------------------------------------------------------
//
// File Name:	Object.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAm 150
//
//------------------------------------------------------------------------------

#include "Object.h"
#include "Transform.h"

struct Object
{
	Transform* transform;
	bool destroyed;
};

Object* ObjectCreate(Transform* transform)
{
	Object *obj = new Object;
	obj->transform = transform;
	obj->destroyed = false;
	return obj;
}

Object* ObjectClone(Object* obj)
{
	Object* obj = new Object;
	obj->transform = CloneTransform(obj->transform);
	obj->destroyed = false;
	return obj;
}

void ObjectDelete(Object* obj)
{
	DeleteTransform(obj->transform);
	delete obj;
}


void ObjectDestroy(Object* obj)
{
	obj->destroyed = true;
}

bool IsDestroyed(Object* obj)
{
	return obj->destroyed;
}
