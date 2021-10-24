#pragma once
#include <vector>
#include "Vector2.h"
#include "SDL.h"
using namespace std;

static enum CollisionLayers
{
	playerLayer = 1,
	bulletLayer = 2,
	enemyLayer = 4,
};

struct GameObject {	
	//Layer
	CollisionLayers layer;
	void SetCollisionMatrix(std::vector<CollisionLayers> layers);
	virtual void OnCollision();

	static GameObject* ConverToGameObject(GameObject* object) {
		//GameObject* gameObject;
		//gameObject = object;

		return object;
	}

	Vector2 ScreenSize = Vector2(0, 0);
	Vector2 Position = Vector2(0, 0);
	float Health = 100;
	double radius = 10;

	//SDL
	SDL_Rect Rect;
	
	//grid
	int collisionCellX, collisionCellY;
	//int collisionMatrix = 0;
	int collisionCellIndex;
	bool IsActive = false;

	bool print = false;
};

struct Gun
{
	//Gun
	double fireRatePerSec = 5;
	double fireDelay = 1 / fireRatePerSec;
	double currentFireTime = 0;
};



/*
struct 
{
	//grid
	int collisionCellX, collisionCellY;
	int collisionMatrix = 0;
	int collisionCellIndex;
	
};*/