#pragma once

#include "SDL.h"

class SnakePart {
public:
	
	SDL_Rect* rect = new SDL_Rect();
	int dirX = 0;
	int dirY = 0;
	int prevDirX = 0;
	int prevDirY = 0;
	
};