#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Data.h"


struct EnemyData : GameObject, Gun
{
public:	
	EnemyData() {
	SetCollisionMatrix(std::vector<CollisionLayers>{ bulletLayer, playerLayer });
	}
	double DeltaTime	= 0;
	double MoveSpeed	= 100;
	Vector2 Velocity	= Vector2(0, 0);
	Vector2 RectSize	= Vector2(40, 40);

	SDL_Texture* texture;

	virtual void OnCollision() override{
		Health -= 10;

		if (Health < 0)
		{
			IsActive = false;
		}
	}
};

class Enemy
{
public:
	//Enemy();
	static EnemyData UpdatePosition(EnemyData enemyData, Vector2 target, int poolSize);
	static void UpdatePosition(EnemyData* enemyData, Vector2 target, double deltaTime, int poolSize);
	//static void UpdatePosition(EnemyData* data);
	static void Render(SDL_Renderer* renderer, EnemyData data[], int arrayLength);
};

