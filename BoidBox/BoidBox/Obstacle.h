//------------------------------------------------------------------------------
//
// File Name:	Obstacle.h
// Author(s):	Michael Howard (michael.howard)
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

class Obstacle
{
public:
	Obstacle(Transform* transform, const BoidList* boidList, int _totalBoids);
	Obstacle(const char* file, Transform* _transform, const BoidList* _boidList, int _totalBoids);
	~Obstacle();
	void Update();
	void Render();
	void Reset();
private:
	Transform* transform;
	Sprite* sprite;
	const BoidList* boidList;
	Mesh* openMesh;
	Mesh* endMesh;
	Sound* diedSound;

	int capturedBoids;
	int boidsCaptured;
	int totalBoids;
	bool soundPlayed;
};
