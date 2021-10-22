#pragma once
#include <vector>
#include "Vector2.h"
#include "SDL.h"

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

	Vector2 Position = Vector2(0, 0);
	float Health = 100;
	double radius = 20;

	//SDL
	SDL_Rect Rect;
	
	//grid
	int collisionCellX, collisionCellY;
	int collisionMatrix = 0;
	int collisionCellIndex;
	bool IsActive = false;
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