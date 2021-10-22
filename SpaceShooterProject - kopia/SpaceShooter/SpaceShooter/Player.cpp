#include "Player.h"
#include "RenderingUtilities.h"
#include "Math.h"
#include <list>
#include <vector>
#include <iostream>
#include <map>

void Player::Update(PlayerData* playerData)
{
	playerData->currentFireTime += playerData->DeltaTime;
	UpdatePosition(playerData);

	//UpdateParticalPosition(playerData);		
}

void Player::UpdatePosition(PlayerData* playerData) {

	Input::UpdateInputs(&playerData->DirInput);

	SDL_GetMouseState(&playerData->MousePositionX, &playerData->MousePositionY);

	bool horizontalMovement = false;
	bool verticalMovement = false;
		
	if (playerData->DirInput.aDown)	{
		horizontalMovement = true;
		playerData->Velocity.x += -playerData->MoveSpeed * playerData->DeltaTime;		
	}
	if (playerData->DirInput.dDown) {
		horizontalMovement = true;
		playerData->Velocity.x += playerData->MoveSpeed * playerData->DeltaTime;		
	}
	if (playerData->DirInput.wDown) {
		verticalMovement = true;
		playerData->Velocity.y += -playerData->MoveSpeed * playerData->DeltaTime;		
	}
	if (playerData->DirInput.sDown) {
		verticalMovement = true;
		playerData->Velocity.y += playerData->MoveSpeed * playerData->DeltaTime;	
	}
			
	Vector2 minSpeedVector = Vector2(-playerData->MaxMoveSpeed, -playerData->MaxMoveSpeed);
	Vector2 maxSpeedVector = Vector2(playerData->MaxMoveSpeed, playerData->MaxMoveSpeed);

	playerData->Velocity = playerData->Velocity - (playerData->Velocity * playerData->drag); // drag

	playerData->Velocity = Vector2::Clamp(playerData->Velocity, minSpeedVector, maxSpeedVector);

	//cout << "playerData->Velocity x " << playerData->Velocity.x << "playerData->Velocity y " << playerData->Velocity.y << endl;
	//if (!horizontalMovement)	{	//	playerData->Velocity.x = 0;	}	//if (!verticalMovement)	{	//	playerData->Velocity.y = 0;	}	

	playerData->Position.x = playerData->Position.x + (playerData->Velocity.x); //*playerData.DeltaTime
	playerData->Position.y = playerData->Position.y + (playerData->Velocity.y);  //*playerData.DeltaTime

	Vector2 maxVector = playerData->ScreenSize - playerData->RectSize;

	playerData->Position = Vector2::Clamp(playerData->Position, Vector2(0, 0), maxVector);
}

void Player::Render(SDL_Renderer* renderer, PlayerData playerData) {

	RenderPlayer(renderer, playerData);
	//RenderPartical(renderer, playerData.Particals);
}

void Player::SpawnPartical(SDL_Renderer* renderer, PlayerData* playerData, ParticalsData* Particals[])
{
	if (renderer == nullptr || playerData == nullptr)
	{
		return;
	}


	for (int x = 0; x < sizeof(Particals); x++)
	{
		if (Particals[x] == nullptr)
		{
			continue;
		}

		if (!Particals[x]->IsActive)
		{
			Particals[x]->IsActive = true;

			for (int y = 0; y < Particals[x]->amountOfParticals; y++)
			{
				Particals[x]->Position[y] = playerData->Position;
				Particals[x]->Velocity[y] = -playerData->Velocity;
				Particals[x]->Velocity[y].y += Math::GetRandom(x + y, -2, 2);
				Particals[x]->Velocity[y].y += Math::GetRandom(x + y, -2, 2);
			}
		}
		else 
		{
			for (int y = 0; y < sizeof(Particals[x]->Velocity[y]); y++)
			{
				Particals[x]->Position[y] += Particals[x]->Velocity[y] * playerData->DeltaTime;

				Particals[x]->ParticalRect[y].x = Particals[x]->Position[y].x;
				Particals[x]->ParticalRect[y].y = Particals[x]->Position[y].y;
				Particals[x]->ParticalRect[y].w = Particals[x]->ParticalRect[y].h = 4;
				
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderFillRect(renderer, &Particals[x]->ParticalRect[y]);
			}			
		}
	}
}

void Player::UpdateParticalPosition(PlayerData* playerData) {
	/*
	for (int x = 0; x < playerData->Particals[x].amountOfParticals; x++)
	{
		if (!playerData->Particals[x].IsActive)
		{
			return;
		}	

		for (int y = 0; y < playerData->Particals[x].amountOfParticals; y++)
		{
			playerData->Particals[x].Position[y] += playerData->Particals[x].Velocity[y];
		}
	}*/
}

void Player::RenderPartical(SDL_Renderer* renderer, ParticalsData Particals[]) 
{
	for (int x = 0; x < sizeof(Particals); x++)
	{
		if (!Particals[x].IsActive)
		{
			return;
		}

		for (int y = 0; y < sizeof(Particals[x].Velocity[y]); y++)
		{
			Particals[x].Position[y] += Particals[x].Velocity[y];
		}
	}
}

void Player::RenderPlayer(SDL_Renderer* renderer, PlayerData playerData) {
	
	if (!playerData.IsActive)
		return;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	playerData.Rect.h = (int)playerData.RectSize.y;
	playerData.Rect.w = (int)playerData.RectSize.x;

	playerData.Rect.x = (int)round(playerData.Position.x);
	playerData.Rect.y = (int)round(playerData.Position.y);	//playerData.PlayerRect.y = (int)round(screenMiddle.y);	//playerData.PlayerRect.x = (int)round(screenMiddle.x);

	SDL_RenderFillRect(renderer, &playerData.Rect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_Rect healthRect;

	healthRect.x = healthRect.y = 20;
	healthRect.w = playerData.Health;
	healthRect.h = 20;

	SDL_RenderFillRect(renderer, &healthRect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	playerData.MouseRect.h = playerData.MouseRect.w = 20;
	playerData.MouseRect.x = playerData.MousePositionX;
	playerData.MouseRect.y = playerData.MousePositionY;

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &playerData.MouseRect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//if (playerData.texture == nullptr)
	//	playerData.texture = RenderingUtilities::LoadTexture("Ressources/PlayerRocket.png", renderer);

	//SDL_RenderCopyEx(renderer, playerData.texture, NULL, &playerData.PlayerRect, 0, NULL, SDL_FLIP_NONE);
}