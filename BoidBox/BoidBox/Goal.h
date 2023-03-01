//------------------------------------------------------------------------------
//
// File Name:	Goal.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:		GAM150 Game Project
// Course:		GAM150
//
//------------------------------------------------------------------------------

#pragma once

struct Transform;
struct Sprite;
struct BoidList;
struct Mesh;
struct Sound;

class Goal
{
public:
	Goal(Transform* transform, const BoidList* boidList, int _totalBoids);
	~Goal();
	void Update();
	void Render();
	void Reset();
private:
	Transform* transform;
	Sprite* sprite;
	const BoidList* boidList;
	Mesh* openMesh;
	Mesh* endMesh;
	Sound* completeSound;

	int capturedBoids;
	int totalBoids;
	bool soundPlayed;
};
