#pragma once

#include "time.h"
#include "SDL.h"
#include "Vec2.h"
#include "Snake.h"

class Food {
private:
	bool isPosOcccupied(Vec2 pos, Snake snake) {

		for (int i = 0; i < snake.snakeParts.size(); i++) {
			if (snake.snakeParts[i].pos == pos)
				return true;
		}
		return false;
	}
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

	void repositionFood(Snake snake) {

		Vec2 newPos = snake.snakeParts[0].pos;

		srand(time(0));
		while (isPosOcccupied(newPos, snake)) {
			newPos = Vec2( 40 * round((rand() % 680)/40) , 40 * round((rand() % 440) / 40));
		}

		this->rect->x = newPos.x;
		this->rect->y = newPos.y;
		this->pos = newPos;
	}
};