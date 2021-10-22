#include "Bullets.h"
#include <iostream>
#include <list>
using namespace std;

void Bullets::SpawnBullets(Vector2 pos, Vector2 dir, BulletData* bulletData, CollisionLayers layer, int arrayLength)
{
	for (int i = 0; i < arrayLength; i++)
	{
		if (!bulletData[i].IsActive)
		{
			bulletData[i].layer = layer;
			bulletData[i].currentlifeTime = 0;
			bulletData[i].IsActive = true;
			bulletData[i].Position = pos;
			bulletData[i].Velocity = dir.Normalized();
			return;
		}
	}
}

void Bullets::UpdateBullets(BulletData* bulletData, double deltaTime, int arrayLength)
{	
	int alivebullets = 0;

	for (int i = 0; i < arrayLength; i++)
	{
		if (!bulletData[i].IsActive)
		{
			continue;
		}

		alivebullets++;

		bulletData[i].Position = bulletData[i].Position + bulletData[i].Velocity * (deltaTime * bulletData[i].speed);
		bulletData[i].currentlifeTime += deltaTime;

		if (bulletData[i].currentlifeTime > bulletData[i].lifeTime)
		{
			bulletData[i].IsActive = false;
		}
	}	

	//cout << "arrayLength = " << arrayLength << endl;

	if (alivebullets > 0)
	{
		//cout << "alivebullets = " << alivebullets << endl;
	}

	
}

void Bullets::RenderBullets(SDL_Renderer* renderer, BulletData bulletData[], int arrayLength)
{
	//cout << "Render bullets" << endl;

	for (int i = 0; i < arrayLength; i++)
	{
		if (!bulletData[i].IsActive)
		{
			continue;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		bulletData[i].Rect.h = (int)bulletData[i].RectSize.y;
		bulletData[i].Rect.w = (int)bulletData[i].RectSize.x;

		bulletData[i].Rect.x = round(bulletData[i].Position.x);
		bulletData[i].Rect.y = round(bulletData[i].Position.y);

		SDL_RenderFillRect(renderer, &bulletData[i].Rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	//if (data.texture == nullptr)
	//	data.texture = RenderingUtilities::LoadTexture("Ressources/HomingRocket.png", renderer);

	//SDL_RenderCopyEx(renderer, data.texture, NULL, &data.EnemyRect, 0, NULL, SDL_FLIP_NONE);
}
