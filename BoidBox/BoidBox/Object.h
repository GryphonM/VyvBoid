//------------------------------------------------------------------------------
//
// File Name:	Object.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#ifndef OBJECT_H
#define OBJECT_H

//struct Transform;
struct Object;

#if 0
struct Object
{
	Transform* transform;
	bool destroyed;
};
#endif

Object* ObjectCreate(Transform* transform);
Object* ObjectClone(Object* obj);
void ObjectDelete(Object* obj);

void ObjectDestroy(Object* obj);
bool IsDestroyed(Object* obj);

#endif
