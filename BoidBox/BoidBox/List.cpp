//------------------------------------------------------------------------------
//
// File Name:	List.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------

#include "List.h"
#include "Object.h"

ObjectList::ObjectList() : list() {}
ObjectList::~ObjectList()
{
	Clear();
}

void ObjectList::PushBack(Object* obj) { list.push_back(obj); }
void ObjectList::PushFront(Object* obj) { list.push_front(obj); }
Object* ObjectList::Back() { return list.back(); }
Object* ObjectList::Front() { return list.front(); }
Object* ObjectList::PopBack() { Object* back = list.back(); list.pop_back(); return back; }
Object* ObjectList::PopFront() { Object* front = list.front(); list.pop_front(); return front; }
void ObjectList::Erase(Object* obj) { list.erase(std::find(list.begin(), list.end(), obj)); }
void ObjectList::Clear()
{
	int size = Size();
	for (int i = 0; i < size; ++i)
		ObjectDestroy(PopBack());
}
Object* ObjectList::operator[](int index)
{
	if (index > list.size() || index < 0)
		return NULL;
	auto it = list.begin();
	for (int i = 0; i < index; ++i)
		++it;
	return *it;
}

int ObjectList::Size() { return static_cast<int>(list.size()); }
bool ObjectList::IsEmpty() { return list.empty(); }


void ObjectListAdd(ObjectList* list, Object* obj) { list->PushFront(obj); }
void ObjectListRemove(ObjectList* list, Object* obj) { list->Erase(obj); }
int ObjectListAdd(ObjectList* list) { list->Size(); }
