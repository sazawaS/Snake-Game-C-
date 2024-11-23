#pragma once

#import "SDL.h"

class Vec2 {
public:
	int x;
	int y;

	Vec2(int x, int y) 
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Vec2 const& obj)
	{
		return (x == obj.x && y == obj.y);
	}
};

Vec2 getVecFromRect(SDL_Rect rect) 
{
	return Vec2(rect.x, rect.y);
}