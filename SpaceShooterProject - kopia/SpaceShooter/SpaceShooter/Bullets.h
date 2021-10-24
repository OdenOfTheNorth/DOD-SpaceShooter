#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "Data.h"

struct BulletData : GameObject
{
public:
	BulletData() {
		SetCollisionMatrix(std::vector<CollisionLayers>{ enemyLayer });
	}
	//Vector2 pos;
	Vector2 Velocity;
	Vector2 RectSize = Vector2(20,20);
	
	double speed = 300;
	double lifeTime = 7;
	double currentlifeTime = 0;
	//SDL_Rect BulletRect;
	//SDL_Texture* texture;
};

class Bullets
{
public:	
	static void SpawnBullets(Vector2 pos, Vector2 dir, BulletData* bulletData, CollisionLayers layer, int arrayLength);
	static void UpdateBullets(BulletData* bulletData, double deltaTime, int arrayLength);
	static void RenderBullets(SDL_Renderer* renderer, BulletData bulletData[], int arrayLength);
};

