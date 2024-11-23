#pragma once

#include "SDL.h"
#include <vector>

#include "Vec2.h"

class SnakePart {
public:

	SDL_Rect* rect = new SDL_Rect();
	Vec2 pos = Vec2(0, 0);
	Vec2 dir = Vec2(0, 0);
	Vec2 prevDir = Vec2(0, 0);

	void update() {
		this->rect->x += dir.x;
		this->rect->y += dir.y;
		this->pos = getVecFromRect(*this->rect);

		this->prevDir = dir;
	}
};

class Snake {
private:
	void createNewSnakePart(int x, int y, Vec2 dir) 
	{
		SnakePart newSnakePart;
		newSnakePart.dir = dir;
		newSnakePart.pos = Vec2(x, y);

		newSnakePart.rect = new SDL_Rect();
		newSnakePart.rect->x = x;
		newSnakePart.rect->y = y;
		newSnakePart.rect->w = 40;
		newSnakePart.rect->h = 40;

		this->snakeParts.push_back(newSnakePart);
	}


public:
	std::vector<SnakePart> snakeParts;


	void init(int x, int y, int dirX, int dirY) 
	{
		createNewSnakePart(x, y, Vec2(dirX, dirY) );
	}

	void inputSnake( const char* input) 
	{
		if (input == "up" && snakeParts[0].dir.y != 40)
			snakeParts[0].dir = Vec2(0, -40);
		else if (input == "down" && snakeParts[0].dir.y != -40)
			snakeParts[0].dir = Vec2(0, 40);
		else if (input == "right" && snakeParts[0].dir.x != -40)
			snakeParts[0].dir = Vec2(40, 0);
		else if (input == "left" && snakeParts[0].dir.x != 40)
			snakeParts[0].dir = Vec2(-40, 0);
	}

	void updateSnake() 
	{

		for (int i = 0; i < snakeParts.size(); i++)
		{
			snakeParts[i].update();
			if (i > 0)
				snakeParts[i].dir = snakeParts[i - 1].prevDir;
		}

	}

	void eat() 
	{
		SnakePart tail = snakeParts[snakeParts.size() - 1];
		createNewSnakePart(tail.rect->x - tail.dir.x, tail.rect->y - tail.dir.y, tail.dir);
	}
};