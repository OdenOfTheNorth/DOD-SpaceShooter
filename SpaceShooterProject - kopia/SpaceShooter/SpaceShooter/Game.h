#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_TTF.h>
#include "Enemy.h"
#include "SpaceShooterStructs.h"
#include "Input.h"
#include "Player.h"
#include "Collision2D.h"

struct Time
{
public:
	int cycleCount = 0;
	int frameCounter = 0;

	double accumilator = 0;
	double cycleTime = 0;
	double independedGameTime = 0;
	double gameTime = 0;
	double deltaTime = 0;	

	double DesiredFps = 60;
	double msPerSecond = 1000;

	double SpawnCounter = 7;
	double currentSpawnCounter = 0;
};

struct GameData
{
public:	
	int SpawnWave = 25;
	int EnemysAlive = 0;
	static const int EnemysPoolSize = 350;
	static const int BulletsPoolSize = 1000;
		
	PlayerData playerData;
	EnemyData EnemysData[EnemysPoolSize];
	BulletData Bullets[BulletsPoolSize];	
	
	vector<GameObject> gameObjects;

	bool IsRunning = true;
};

struct SDLRenderData
{
public:
	SDLRenderData(int xWidth = 1000, int yHight = 1000, bool screen = false , SDL_Window* _window = nullptr, SDL_Renderer* _renderer = nullptr) {
		resX = xWidth;
		resY = yHight;
		fullscreen = screen;
		window = _window;
		renderer = _renderer;
	}
	SDL_Window* window;
	SDL_Renderer* renderer;
	int resX;
	int resY;	
	bool fullscreen = false;
};

class Game
{
public:
	Game();
	~Game();

	void StartGame(SDLRenderData data);
	void GameLoop(SDLRenderData SDLData, GameData gameData);

	void Render(SDL_Renderer* renderer, PlayerData playerData, EnemyData enemyData[], int enemyCount,
		BulletData bulletData[], int bulletCount);

	//void RenderEnemys(SDL_Renderer* renderer, EnemyData enemyData[], int enemyCount);
	//void RenderPlayer(SDL_Renderer* renderer, PlayerData playerData);
	//void RenderBullets(SDL_Renderer* renderer, BulletData bulletData[], int bulletCount);
	
	void Update(GameData* gameData, Grid* grid, double deltaTime);
	//void UpdateEnemyPosition(EnemyData* enemyData, Vector2 target, int PoolSize);
	//void UpdatePlayerPosition(PlayerData* playerData);

	void SpawnEnemys(EnemyData* enemyData, Vector2 pos, int waveSize, int poolSize);

	//Collision2D* collsionSystem;
	//Player player;
	//Enemy Enemy;
	//Bullets bullets;

};

