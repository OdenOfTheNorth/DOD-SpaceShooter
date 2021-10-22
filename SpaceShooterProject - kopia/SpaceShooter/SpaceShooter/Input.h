#pragma once
#include "SDL.h"
#include <iostream>
using namespace std;

struct DirectionInputs {
	bool wDown = false;
	bool sDown = false;
	bool dDown = false;
	bool aDown = false;
	bool quitPressed = false;
	bool Shoot = false;
};

class Input
{
public:
	Input();
	~Input();

	static void UpdateInputs(DirectionInputs* dirInput);
	static DirectionInputs* ChangeKeyState(SDL_Event event, DirectionInputs* dirInput, bool state);
};

