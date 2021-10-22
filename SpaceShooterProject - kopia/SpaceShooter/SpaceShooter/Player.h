#pragma once
#include "Vector2.h"
#include "Input.h"
#include "Bullets.h"
#include "Data.h"


struct ParticalsData
{
public:
	static const int amountOfParticals = 8;

	Vector2 Position[amountOfParticals];
	Vector2 Velocity[amountOfParticals];
	SDL_Rect ParticalRect[amountOfParticals];

	double DeltaTime;
	double MoveSpeed = 45;

	bool IsActive = true;
};


struct PlayerData : GameObject, Gun//, Mouse
{
public:
	DirectionInputs DirInput;
		
	//Movement
	Vector2 Velocity = Vector2(0, 0);
	Vector2 RectSize = Vector2(40, 40);
	Vector2 ScreenSize = Vector2(0, 0);

	//Movement
	double MoveSpeed = 70;
	double drag = 0.02f;
	double MaxMoveSpeed = 3;

	//Time
	double DeltaTime;

	SDL_Rect MouseRect;
	int MousePositionX;
	int MousePositionY;

	

	//ParticalsData Particals[4];
};
/*
struct Mouse
{
public:
	//Mouse
	SDL_Rect MouseRect;
	int MousePositionX;
	int MousePositionY;
};*/


class Player
{
public:
	//Player();
	static void Update(PlayerData* playerData);
	static void UpdatePosition(PlayerData* playerData);
	static void UpdateParticalPosition(PlayerData* playerData);

	static void SpawnPartical(SDL_Renderer* renderer, PlayerData* playerData, ParticalsData* Particals[]);

	static void Render(SDL_Renderer* renderer, PlayerData playerData);
	static void RenderPlayer(SDL_Renderer* renderer, PlayerData playerData);
	static void RenderPartical(SDL_Renderer* renderer, ParticalsData Particals[]);
};


