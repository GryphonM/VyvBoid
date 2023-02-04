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
#include "Level1.h"
#include <vector>

//------------------------------------------------------------------------------
// Private Class, Struct, and Function Definitions
//------------------------------------------------------------------------------

ObjectIDType GenerateID();

struct Object
{
	ObjectIDType id;
	std::string name;

	Transform* transform;
	bool destroyed;

	State activeState;

	// Level* owner;

	// Here to shut up compiler warnings
	// Use ObjectCreate instead
	Object() : id(0), name(), transform(NULL), destroyed(false), activeState(Play)/*, owner(NULL)*/ {}
};

//------------------------------------------------------------------------------
// Private Variables
//------------------------------------------------------------------------------
std::vector<ObjectIDType> idCollection;

//------------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------------

Object* ObjectCreate(std::string name/*, Level* owner*/, Transform* transform/*, State activeState*/)
{
	Object *obj = new Object;
	// ObjectSetOwner(obj, owner);
	ObjectSetTransform(obj, transform);

	ObjectIDType id = GenerateID();

	obj->destroyed = false;
	return obj;
}

Object* ObjectClone(Object* _obj)
{
	Object* obj = new Object;
	obj->transform = CloneTransform(_obj->transform);
	// obj->owner = _obj->owner;
	obj->destroyed = false;
	return obj;
}

void ObjectDelete(Object* obj)
{
	DeleteTransform(obj->transform);
	// obj->owner = NULL;
	delete obj;
	obj = NULL;
}


void ObjectDestroy(Object* obj) { obj->destroyed = true; }
bool IsDestroyed(Object* obj) { return obj->destroyed; }

Transform* ObjectGetTransform(Object* obj) { return obj->transform; }
void ObjectSetTransform(Object* obj, Transform* transform) { obj->transform = transform; }

State ObjectGetActiveState(Object* obj) { return obj->activeState; }
void ObjectSetActiveState(Object* obj, State activeState) { obj->activeState = activeState; }

//Level* ObjectGetOwner(Object* obj) { return obj->owner; }
//void ObjectSetOwner(Object* obj, Level* owner) { obj->owner = owner; }

void ObjectMove(Object* obj, Vector2D pos) { TransformSetPosition(obj->transform, pos); }

//------------------------------------------------------------------------------
// Private Functions
//------------------------------------------------------------------------------
ObjectIDType GenerateID()
{
	ObjectIDType id = static_cast<ObjectIDType>(idCollection.size());
	idCollection.push_back(id);
	return id;
}
