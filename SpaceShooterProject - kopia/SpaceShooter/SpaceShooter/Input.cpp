#include "Input.h"

Input::Input() {

}

Input::~Input()
{
}

void Input::UpdateInputs(DirectionInputs* dirInput)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_KEYDOWN:
			dirInput = ChangeKeyState(event, dirInput, true);
			break;
		case SDL_QUIT:
			dirInput->quitPressed = true;
			cout << "Quit" << endl;
			break;
		case SDL_KEYUP:
			dirInput = ChangeKeyState(event, dirInput, false);
		default:
			break;
		}
	}

	//return dirInput;
}

DirectionInputs* Input::ChangeKeyState(SDL_Event event, DirectionInputs* dirInput, bool state)
{	
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		dirInput->wDown = state;
		//cout << "w Pressed, " << state << endl;
		break;
	case SDLK_s:
		dirInput->sDown = state;
		break;
	case SDLK_a:
		dirInput->aDown = state;
		break;
	case SDLK_d:
		dirInput->dDown = state;
		break;
	case SDLK_ESCAPE:
		dirInput->quitPressed = true;
		break;
	case SDLK_SPACE:
		dirInput->Shoot = state;
		break;
	default:
		break;
	}
	return dirInput;
}