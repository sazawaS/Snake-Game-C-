#pragma once

#include "SDL.h"
#include "Vec2.h"

class Food {
public:
	SDL_Rect* rect = new SDL_Rect();
	Vec2 pos = Vec2(0,0);

	Food(int x, int y) {
		this->rect->x = x;
		this->rect->y = y;
		this->rect->w = 40;
		this->rect->h = 40;
		this->pos = getVecFromRect(*this->rect);
	}

	void repositionFood() {
		this->rect->x += 120;
		this->pos = getVecFromRect(*this->rect);
	}
};