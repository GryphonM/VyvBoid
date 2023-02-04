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

#define NULL 0

#include <string>

struct Transform;
struct Object;
enum State;
//struct Level1;

typedef unsigned int ObjectIDType;

#if 0
struct Object
{
	ObjectIDType id;
	std::string name;

	Transform* transform;
	bool destroyed;

	Level* owner;

	void (*UniqueUpdate)(float);
};
#endif

Object* ObjectCreate(std::string name/*, Level* owner = NULL*/, Transform* transform = NULL);
Object* ObjectClone(Object* obj);
void ObjectDelete(Object* obj);

void ObjectDestroy(Object* obj);
bool IsDestroyed(Object* obj);

Transform* ObjectGetTransform(Object* obj);
void ObjectSetTransform(Object* obj, Transform* transform);
State ObjectGetActiveState(Object* obj);
void ObjectSetActiveState(Object* obj, State activeState);
// Level* ObjectGetOwner(Object* obj);
// void ObjectSetOwner(Object* obj, Level* owner);

void ObjectMove(Object* obj, Vector2D pos);

#endif
