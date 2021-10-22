#include "Enemy.h"
#include "RenderingUtilities.h"
#include <list>
#include <iostream>
#include "Vector2.h"
#include <vector>
/*
Enemy::Enemy() {

}
*/
EnemyData Enemy::UpdatePosition(EnemyData enemyData, Vector2 target, int poolSize)
{
	float angle;

	if (!enemyData.IsActive)
	{
		return enemyData;
	}

	if (Vector2::Distance(enemyData.Position, target) > 1)
	{
		enemyData.Velocity = Vector2::Lerp(enemyData.Velocity, Vector2::GetNormalizedDirection(enemyData.Position, target), 0.5);
		enemyData.Velocity.Normalize();
		angle = Vector2::AngleFromDirection(enemyData.Velocity);
		enemyData.Position += enemyData.Velocity * enemyData.MoveSpeed * enemyData.DeltaTime;
	}

	if (enemyData.currentFireTime > enemyData.fireDelay)
	{

	}


	/*
	if (!enemyData.IsActive) {
		//cout << "current enemyData index" << endl;
		return enemyData;//continue;// enemyData;
	}

	//cout << "index " << endl;
	float deltaToMove = enemyData.DeltaTime * enemyData.MoveSpeed;

	Vector2 dir = (target - enemyData.Position).Normalized();
	dir = dir * deltaToMove;

	enemyData.Velocity = dir;
	enemyData.Position += enemyData.Velocity;*/
	
	return enemyData;
}
void Enemy::Render(SDL_Renderer* renderer, EnemyData data[], int arrayLength) {

	//int size = sizeof(data) / sizeof(int);

	for (int i = 0; i < arrayLength; i++)
	{
		if (!data[i].IsActive)
		{
			return;
		}

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		data[i].Rect.h = (int)data[i].RectSize.y;
		data[i].Rect.w = (int)data[i].RectSize.x;

		data[i].Rect.x = round(data[i].Position.x);
		data[i].Rect.y = round(data[i].Position.y);

		SDL_RenderFillRect(renderer, &data[i].Rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		
		if (data[i].texture == nullptr)
			data[i].texture = RenderingUtilities::LoadTexture("Ressources/HomingRocket.png", renderer);
			
		if (data[i].texture != nullptr)
		{
			//cout << "texture is not null" << endl;
			//SDL_RenderCopy(renderer, data[i].texture, NULL, &data[i].Rect);// , 0, NULL, SDL_FLIP_NONE);
		}
		else {
			cout << "texture is null" << endl;
		}
	}
}

void Enemy::UpdatePosition(EnemyData* enemyData, Vector2 target, double deltaTime, int poolSize) 
{
	int aliveEnemy = 0;
	float angle = 0;
	float turnSpeed = 0.01;

	for (int i = 0; i < poolSize; i++)
	{
		if (!enemyData[i].IsActive)
		{
			continue;
		}

		aliveEnemy++;

		double deltaToMove = (deltaTime * enemyData[i].MoveSpeed);
		//enemyData[i].Velocity = (target - enemyData[i].Position).Normalized();//enemyData[i].Velocity = enemyData[i].Velocity * deltaToMove;//enemyData[i].Position = enemyData[i].Position + enemyData[i].Velocity;

		if (Vector2::Distance(enemyData[i].Position, target) > 1)
		{
			enemyData[i].Velocity = Vector2::Lerp(enemyData[i].Velocity, Vector2::GetNormalizedDirection(enemyData[i].Position, target), turnSpeed);
			enemyData[i].Velocity.Normalize();			
			angle = Vector2::AngleFromDirection(enemyData[i].Velocity);			
			enemyData[i].Position += enemyData[i].Velocity * deltaToMove;
		}
	}
	//cout << "aliveEnemy = " << aliveEnemy << endl;
}

