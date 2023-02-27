//------------------------------------------------------------------------------
//
// File Name:	BasicObstacles.cpp
// Author(s):	Michael Howard (michael.howard)
// Project:		GAM 150 Game Project
// Course:		GAM 150
//
//------------------------------------------------------------------------------
#include "Mesh.h"
#include "Math.h"
#include "Sprite.h"
#include "Transform.h"
#include "Vector2D.h"
#include "DGL.h"


struct Tower
{
	Transform* transform;

	Mesh* mesh;

	Sprite* sprite;

	const char* containerName;
};

struct Gas
{
	Transform* transform;

	Mesh* mesh;

	Sprite* sprite;

	bool MovingLeft;
	bool MovingUp;

	float speed;
/*	float minY;
	float minX;
	float maxY;
	float maxX;*/
};

struct Obstacles
{
	Tower* tower;

	Gas* gas;
};

Obstacles* CreateObstacles(const char* name)
{
	Obstacles* obstacles = new Obstacles;
	if (obstacles)
		return obstacles;
	else
		return NULL;
		
}

Tower* CreateTower(const char* name)
{
	Tower* tower = new Tower;
	DGL_Color color = { 0.0f, 1.0f, 0.0f, 1.0f };
	if (tower)
	{
		tower->sprite = CreateSprite();
		tower->mesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Tower", color);
		SpriteSetMesh(tower->sprite, tower->mesh);
		tower->transform = CreateTransform(Vector2D(-300, -250), Vector2D(25, 40));
		return tower;
	}
	else
	{
		return NULL;
	}
}

Gas* CreateGas(const char* name)
{
	Gas* gas = new Gas;
	DGL_Color color = { 0.0f, 1.0f, 0.0f, 1.0f };
	if (gas)
	{
		gas->MovingLeft = false;
		gas->speed = 50.0f;
		gas->sprite = CreateSprite();
		gas->mesh = SquareMesh(0.5f, 0.5f, 1.0f, 1.0f, "Tower", color);
		SpriteSetMesh(gas->sprite, gas->mesh);
		gas->transform = CreateTransform(Vector2D(0, 250), Vector2D(40, 25));
		return gas;
	}
	else
	{
		return NULL;
	}
}

/*Vector2D GetObstaclePosition(Tower* tower)
{
	if (tower)
	{
		Vector2D position = TransformGetPosition(tower->transform);
		return position;
	}
	else
		return Vector2D(0, 0);
}*/

void UpdateGasPosition(Gas* gas, float min, float max, float dt)
{
	Vector2D pos = TransformGetPosition(gas->transform);
	if (gas->MovingLeft = false)
	{
		pos.X(pos.X() + (gas->speed * dt));
		if (pos.X() >= max)
			gas->MovingLeft = true;
	}
	else
	{
		pos.X(pos.X() - (gas->speed * dt));
		if (pos.X() <= min)
			gas->MovingLeft = false;
	}
	TransformSetPosition(gas->transform, pos);
}

void AddTower(Obstacles* obstacles, Tower* tower)
{
	obstacles->tower = tower;
}

void AddGas(Obstacles* obstacles, Gas* gas)
{
	obstacles->gas = gas;
}

void DrawTower(Tower* tower)
{
	if (tower && tower->mesh && tower->transform)
	{
		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
		RenderSprite(tower->sprite, tower->transform);
	}
}

void DrawGas(Gas* gas)
{
	if (gas && gas->mesh && gas->transform)
	{
		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
		RenderSprite(gas->sprite, gas->transform);
	}
}

void DrawObstacles(Obstacles* obstacles)
{
	if (obstacles)
	{
		DrawTower(obstacles->tower);
		DrawGas(obstacles->gas);
	}
}

void DeleteTower(Tower** tower)
{
	DeleteTransform((&(*tower)->transform));
	FreeSprite((&(*tower)->sprite));
	freeMesh((&(*tower)->mesh));
	delete *tower;
	*tower = NULL;

}

void DeleteGas(Gas** gas)
{
	DeleteTransform((&(*gas)->transform));
	FreeSprite((&(*gas)->sprite));
	freeMesh((&(*gas)->mesh));
	delete* gas;
	*gas = NULL;
}

void DestroyObstacles(Obstacles** obstacles)
{
	if (*obstacles)
	{
		if ((*obstacles)->gas)
		{
			DeleteGas((&(*obstacles)->gas));
		}
		if ((*obstacles)->tower)
		{
			DeleteTower((&(*obstacles)->tower));
		}
		delete *obstacles;
		*obstacles = NULL;
	}
}
