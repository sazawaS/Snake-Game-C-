#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

#include "SnakePart.h"


std::vector<SnakePart> snake = { };
std::vector<std::string> inputList = {};
SDL_Rect* foodRect = new SDL_Rect();

void createNewSnakePart(int x, int y, int dirX, int dirY);
void render(SDL_Window* window, SDL_Renderer* renderer);
void update();

int main(int argc, char* args[]) {

	createNewSnakePart(40, 40, 40, 0);
	createNewSnakePart(0, 40, 40, 0);
	createNewSnakePart(-40, 40, 40, 0);


	foodRect->x = (40);
	foodRect->y = (40);
	foodRect->w = 40;
	foodRect->h = 40;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 440, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	unsigned int a,b = SDL_GetTicks();
	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {

		a = SDL_GetTicks();
		int delta = a - b;

		while (SDL_PollEvent(&event)) {

			switch (event.type) 
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
					break;
				}



				if (event.key.keysym.sym == SDLK_UP) {
					inputList.push_back("up");
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					inputList.push_back("down");
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					inputList.push_back("right");
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					inputList.push_back("left");
				}

			}
		}

		if (delta > 1000/4) {
			update();
			render(window, renderer);

			b = SDL_GetTicks();
		}


	}

	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}



void createNewSnakePart(int x, int y, int dirX, int dirY) {
	SnakePart newSnakePart;
	newSnakePart.dirX = dirX;
	newSnakePart.dirY = dirY;

	newSnakePart.rect = new SDL_Rect();
	newSnakePart.rect->x = x;
	newSnakePart.rect->y = y;
	newSnakePart.rect->w = 40;
	newSnakePart.rect->h = 40;

	snake.push_back(newSnakePart);
}

void placeFood() {
	foodRect->x += 80;

}

void update()
{




	if (inputList.size() >= 1) {
		if (inputList[inputList.size() - 1] == "up" && snake[0].dirY != 40) {
			snake[0].dirX = 0;
			snake[0].dirY = -40;
		}
		else if (inputList[inputList.size() - 1] == "down" && snake[0].dirY != -40) {
			snake[0].dirX = 0;
			snake[0].dirY = 40;
		}
		else if (inputList[inputList.size() - 1] == "right" && snake[0].dirX != -40) {
			snake[0].dirX = 40;
			snake[0].dirY = 0;
		}
		else if (inputList[inputList.size() - 1] == "left" && snake[0].dirX != 40) {
			snake[0].dirX = -40;
			snake[0].dirY = 0;
		}

		inputList.clear();
	}

	for (int i = 0; i < snake.size(); i++) {
		snake[i].rect->x += snake[i].dirX;
		snake[i].rect->y += snake[i].dirY;
		snake[i].prevDirX = snake[i].dirX;
		snake[i].prevDirY = snake[i].dirY;

		if (i > 0) {
			snake[i].dirX = snake[i - 1].prevDirX;
			snake[i].dirY = snake[i - 1].prevDirY;
		}
	}

	if (snake[0].rect->x == foodRect->x && snake[0].rect->y == foodRect->y) {

		placeFood();
		SnakePart tail = snake[snake.size() - 1];
		createNewSnakePart(tail.rect->x - tail.dirX, tail.rect->y - tail.dirY, tail.dirX, tail.dirY);
	}



}


void render(SDL_Window* window, SDL_Renderer* renderer) 
{

	//Background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Elements
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect foodCopy = *foodRect;
	foodCopy.x += 5;
	foodCopy.y += 5;
	foodCopy.w -= 10;
	foodCopy.h -= 10;

	SDL_RenderFillRect(renderer, &foodCopy);

	for (int i = 0; i < snake.size(); i++) {

		SDL_Rect rectCopy = *snake[i].rect;
		rectCopy.h -= 2;
		rectCopy.w -= 2;

		SDL_RenderFillRect(renderer, &rectCopy);
	}



	SDL_RenderPresent(renderer);
}
