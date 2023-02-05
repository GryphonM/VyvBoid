//------------------------------------------------------------------------------
//
// File Name:	List.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#pragma once

struct Object;
#include <list>

class ObjectList
{
public:
	ObjectList();
	~ObjectList();

	void PushBack(Object* obj);
	void PushFront(Object* obj);
	Object* Back();
	Object* Front();
	Object* PopBack();
	Object* PopFront();
	Object* operator[](int index);
	void Erase(Object* obj);
	void Clear();

	int Size();
	bool IsEmpty();
private:
	std::list<Object*> list;
};

void ObjectListAdd(ObjectList* list, Object* obj);
void ObjectListRemove(ObjectList* list, Object* obj);
int ObjectListSize(ObjectList* list);
