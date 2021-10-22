#pragma once
using namespace std;
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class RenderingUtilities
{
public:
	static SDL_Texture* LoadTexture(std::string path, SDL_Renderer* renderer);
};

