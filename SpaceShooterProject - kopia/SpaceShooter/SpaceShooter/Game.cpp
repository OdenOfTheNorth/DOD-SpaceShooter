#include "Game.h"
#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_TTF.h>
#include "RenderingUtilities.h"
#include "Math.h"

using namespace std;

Game::Game() {

	SDLRenderData renderData;	
	Grid grid;

	//Collision2D::Collision2D(&grid);

	int error = SDL_Init(SDL_INIT_EVERYTHING);
	int ttfError = TTF_Init();

	if (error == 0)
	{
		int flag = 0;
		if (renderData.fullscreen)
		{
			flag = SDL_WINDOW_FULLSCREEN;
		}

		cout << "SDL_Init Success" << endl;
		renderData.window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, renderData.resX, renderData.resY, flag);

		if (renderData.window)
		{
			cout << "Window successfully created" << endl;
		}

		if (ttfError == 0)
		{
			cout << "SDL_TTF successfully created" << endl;
		}

		renderData.renderer = SDL_CreateRenderer(renderData.window, -1, 0);

		if (renderData.renderer)
		{
			cout << "Renderer successfully created" << endl;
			SDL_SetRenderDrawColor(renderData.renderer, 255, 0, 0, 255);
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "IMG_Init failed to created SDL_image Error: %s/n" << IMG_GetError() << endl;
			}
			else
			{
				cout << "IMG_Init successfully created" << endl;
			}
		}
		SDL_RenderPresent(renderData.renderer);
	}

	//collsionSystem = new Collision2D(&grid, Vector2(renderData.resX, renderData.resY));

	StartGame(renderData);
}
Game::~Game()
{

}

void Game::StartGame(SDLRenderData data)
{
	//Grid grid;
	GameData* gameData = new GameData();
	gameData->playerData.ScreenSize	= Vector2(data.resX, data.resY);	
	gameData->playerData.Position = Vector2(data.resX / 2, data.resY / 2);
	gameData->playerData.IsActive = true;

	gameData->gameObjects.push_back(&gameData->playerData);
	gameData->playerData.layer = CollisionLayers::playerLayer;

	for (int i = 0; i < gameData->BulletsPoolSize; i++)
	{
		gameData->Bullets[i].layer = CollisionLayers::playerLayer;
		GameObject* obj = GameObject::ConverToGameObject(&gameData->Bullets[i]);
		gameData->gameObjects.push_back(obj);
	}

	for (int i = 0; i < gameData->EnemysPoolSize; i++)
	{
		gameData->EnemysData[i].layer = CollisionLayers::enemyLayer;
		GameObject* obj = GameObject::ConverToGameObject(&gameData->EnemysData[i]);
		gameData->gameObjects.push_back(obj);

		//gameData->gameObjects.push_back(&gameData.EnemysData[i]);
	}
	GameLoop(data, gameData);
}

void Game::SpawnEnemys(EnemyData* enemyData, Vector2 pos, int waveSize, int poolSize)
{
	int currenSpawnEnemys = 0;

	for (int i = 0; i < poolSize; i++)
	{
		double angle = Math::GetRandom(i, 0, 2 * 3.14);
		double magnitude = Math::GetRandom(i, 250, 700);

		if (enemyData[i].IsActive)
		{
			continue;
		}
		
		enemyData[i].IsActive = true;
		enemyData[i].MoveSpeed = Math::GetRandom(i * 3, 10, 70);
		enemyData[i].Position = pos + Vector2( magnitude * cos(angle), magnitude * sin(angle));
	
		currenSpawnEnemys++;

		if (currenSpawnEnemys >= waveSize)
		{
			return;
		}
	}
}
void Game::GameLoop(SDLRenderData SDLData, GameData* gameData)
{
	Time time;	
	Grid grid;

	SpawnEnemys(gameData->EnemysData, gameData->playerData.Position, gameData->SpawnWave, gameData->EnemysPoolSize);

	while (gameData->IsRunning)
	{
		time.cycleCount++;
		if (time.cycleCount % 3 == 0)
		{
			double newTime = SDL_GetTicks();
			time.cycleTime = (newTime - time.independedGameTime) / 3;
			time.independedGameTime = newTime;
		}

		time.accumilator += time.cycleTime;
		double framesec = 1 / time.DesiredFps;
		double frameMiliSec = framesec * time.msPerSecond;
				
		if (time.accumilator > frameMiliSec)
		{
			time.frameCounter++;
			time.accumilator = 0;
			time.deltaTime = SDL_GetTicks();
			double newTime = SDL_GetTicks();
			time.deltaTime = (newTime - time.gameTime) / 1000;
			time.gameTime = newTime; 

			time.currentSpawnCounter += time.deltaTime;

			if (time.currentSpawnCounter > time.SpawnCounter)
			{
				time.currentSpawnCounter = 0;
				SpawnEnemys(gameData->EnemysData, gameData->playerData.Position, gameData->SpawnWave, gameData->EnemysPoolSize);
			}

			Update(gameData, &grid, time.deltaTime);

			Render(SDLData.renderer, gameData->playerData, gameData->EnemysData, gameData->EnemysPoolSize,	gameData->Bullets, gameData->BulletsPoolSize);
		}

		gameData->IsRunning = !gameData->playerData.DirInput.quitPressed;
	}

	SDL_DestroyRenderer(SDLData.renderer);
	SDL_DestroyWindow(SDLData.window);
	TTF_Quit();
	SDL_Quit();
}

void Game::Update(GameData* gameData, Grid* grid, double deltaTime) 
{	
	if (gameData == nullptr)
		return;

	gameData->playerData.DeltaTime = deltaTime;
	gameData->playerData.currentFireTime += deltaTime;

	if (gameData->playerData.DirInput.Shoot && gameData->playerData.currentFireTime > gameData->playerData.fireDelay)
	{
		gameData->playerData.currentFireTime = 0;
		Vector2 dir = Vector2(gameData->playerData.MousePositionX, gameData->playerData.MousePositionY) - gameData->playerData.Position;
		Bullets::SpawnBullets(gameData->playerData.Position, dir, gameData->Bullets, CollisionLayers::playerLayer, gameData->BulletsPoolSize);
	}

	Player::Update(&gameData->playerData);
	Bullets::UpdateBullets(gameData->Bullets, deltaTime, gameData->BulletsPoolSize);
	Enemy::UpdatePosition(gameData->EnemysData, gameData->playerData.Position, deltaTime, gameData->EnemysPoolSize);
		
	CheckCollition(gameData->gameObjects);	
}

void Game::CheckCollition(vector<GameObject*> gameObjects)
{
	auto OverLap = [](float x1, float y1, float r1, float x2, float y2, float r2) {

		float squardX = (x1 - x2) * (x1 - x2);
		float squardY = (y1 - y2) * (y1 - y2);
		float RadiusSquard = (r1 + r2) * (r1 + r2);
		//cout << "squardX" << squardX << endl;
		//cout << "squardY" << squardY << endl;
		//cout << "RadiusSquard" << RadiusSquard << endl;

		//cout << "distance squard " << (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) << "radius squard " << (r1 + r2) * (r1 + r2) << endl;

		return fabs(squardX + squardY <= RadiusSquard);

		//return fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
	};
	
	int cheaks = 0;
	int NotActiveCurrentObject = 0;
	int NotActiveTargetObject = 0;
	/*
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		if (gameObjects[i] == nullptr)
		{
			continue;
		}

		if (!gameObjects[i]->IsActive)
		{
			NotActiveCurrentObject++;
			continue;
		}

		for (int j = 0; j < gameObjects.size() - 1; j++)
		{
			if (gameObjects[j] == nullptr)
			{
				break;
			}

			if (!gameObjects[j]->IsActive)
			{
				NotActiveTargetObject++;
				break;
			}			

			if (i == j)
			{
				break;
			}

			if (gameObjects[i]->layer != gameObjects[j]->layer)
			{
				cheaks++;
				if (OverLap(gameObjects[i]->Position.x, gameObjects[i]->Position.y, gameObjects[i]->radius, gameObjects[j]->Position.x, gameObjects[j]->Position.y, gameObjects[j]->radius))
				{
					cout << "collision " << endl;
					gameObjects[i]->OnCollision();
					gameObjects[j]->OnCollision();
				}
			}
		}
	}*/

	//cout << "Check Collition " << gameObjects.size() - 1 << " cheaks " << cheaks << " Not Active Current Object " << NotActiveCurrentObject << " Not Active Target Object " << NotActiveTargetObject << endl;
	
	for (auto& currentObject : gameObjects)
	{
		if (currentObject != nullptr)
		{
			if (currentObject->IsActive)
			{
				for (auto& targetObject : gameObjects)
				{
					if (targetObject != nullptr)
					{
						if (targetObject->IsActive)
						{
							if (currentObject != targetObject)
							{
								if (currentObject->layer != targetObject->layer)
								{
									//cheaks++;

									if (OverLap(targetObject->Position.x, targetObject->Position.y, targetObject->radius, currentObject->Position.x, currentObject->Position.y, currentObject->radius))
									{
										cout << "collision " << endl;
										currentObject->OnCollision();
										targetObject->OnCollision();
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout << "Check Collition " << gameObjects.size() - 1 << " cheaks " << cheaks << " Not Active Current Object " << NotActiveCurrentObject << " Not Active Target Object " << NotActiveTargetObject << endl;
}

void Game::Render(SDL_Renderer* renderer, PlayerData playerData, EnemyData enemyData[], int enemyCount, BulletData bulletData[], int bulletCount) 
{
	if (renderer == nullptr)
		return;

	SDL_RenderClear(renderer);	
		
	Enemy::Render(renderer, enemyData, enemyCount);
	Bullets::RenderBullets(renderer, bulletData, bulletCount);
	Player::Render(renderer, playerData);

	SDL_RenderPresent(renderer);
}

/*
void Game::RenderBullets(SDL_Renderer* renderer, BulletData bulletData[], int bulletCount) {

	if (renderer == nullptr)
		return;

	for (int i = 0; i < bulletCount; i++)
	{
		if (!bulletData[i].IsActive)
		{
			return;
		}

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		bulletData->Rect.h = (int)bulletData->RectSize.y;
		bulletData->Rect.w = (int)bulletData->RectSize.x;

		bulletData->Rect.x = round(bulletData->Position.x);
		bulletData->Rect.y = round(bulletData->Position.y);

		SDL_RenderFillRect(renderer, &bulletData[i].Rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
}*/