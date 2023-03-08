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
class Scene;

class Goal
{
public:
	Goal(Transform* transform, const BoidList* boidList, int _totalBoids);
	Goal(Transform* transform, Scene* nextScene, const BoidList* boidList, int _totalBoids);
	~Goal();
	void Update(float dt);
	void Render();
	void Reset();
private:
	Transform* transform;
	Sprite* sprite;
	const BoidList* boidList;
	Mesh* openMesh;
	Mesh* endMesh;
	Sound* completeSound;
	Scene* nextScene;

	int capturedBoids;
	int totalBoids;
	float soundTime;
	bool soundPlayed;
};
