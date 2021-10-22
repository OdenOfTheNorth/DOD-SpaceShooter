#include "Game.h"
#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_TTF.h>
#include "RenderingUtilities.h"
#include "Math.h"


Game::Game() {

	SDLRenderData renderData;	
	Grid grid;

	Collision2D::Collision2D(&grid);

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
	GameData gameData;
	gameData.playerData.ScreenSize = Vector2(data.resX, data.resY);
	gameData.playerData.Position = Vector2(data.resX / 2, data.resY / 2);
	gameData.playerData.IsActive = true;
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
void Game::GameLoop(SDLRenderData SDLData, GameData gameData)
{
	Time time;	
	Grid grid;

	//collsionSystem->AddCollider(&grid, &gameData.playerData, 0);
	//collsionSystem->AddCollider(&grid, gameData.EnemysData, gameData.EnemysPoolSize);
	//collsionSystem->AddCollider(&grid, gameData.Bullets, gameData.BulletsPoolSize);

	//Collision2D::AddCollider(&grid, &gameData.playerData, 0);
	//Collision2D::AddCollider(&grid, gameData.EnemysData, gameData.EnemysPoolSize);
	//Collision2D::AddCollider(&grid, gameData.Bullets, gameData.EnemysPoolSize);

	SpawnEnemys(gameData.EnemysData, gameData.playerData.Position, gameData.SpawnWave, gameData.EnemysPoolSize);

	while (gameData.IsRunning)
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
			time.gameTime = newTime; //gameData.playerData.DeltaTime

			time.currentSpawnCounter += time.deltaTime;

			cout << time.currentSpawnCounter << endl;

			if (time.currentSpawnCounter > time.SpawnCounter)
			{
				time.currentSpawnCounter = 0;
				SpawnEnemys(gameData.EnemysData, gameData.playerData.Position, gameData.SpawnWave, gameData.EnemysPoolSize);
			}

			Update(&gameData, &grid, time.deltaTime);

			Render(SDLData.renderer, gameData.playerData, gameData.EnemysData, gameData.EnemysPoolSize,	gameData.Bullets, gameData.BulletsPoolSize);
		}

		gameData.IsRunning = !gameData.playerData.DirInput.quitPressed;
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
	//Collision2D::Update(grid);

	//for (int i = 0; i < gameData->EnemysPoolSize; i++)	//{	//	gameData->EnemysData[i].DeltaTime = deltaTime;
	//	gameData->EnemysData[i] = Enemy::UpdatePosition(gameData->EnemysData[i], gameData->playerData.Position, gameData->EnemysPoolSize);	//}		
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