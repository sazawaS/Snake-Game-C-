#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"

#include "Snake.h"
#include "Food.h"


std::vector<char*> inputList = {};
std::vector<Food*> foodList = {};

void render(SDL_Window* window, SDL_Renderer* renderer, Snake* snake);
void update(Snake* snake);

int main(int argc, char* args[]) {

	Snake* snake = new Snake();
	snake->init(40, 40, 40, 0);
	foodList.push_back( new Food(40, 120));


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

				if (event.key.keysym.sym == SDLK_UP)
					inputList.push_back( (char*) "up");
				else if (event.key.keysym.sym == SDLK_DOWN)
					inputList.push_back( (char*) "down");
				else if (event.key.keysym.sym == SDLK_RIGHT)
					inputList.push_back( (char*) "right");
				else if (event.key.keysym.sym == SDLK_LEFT)
					inputList.push_back( (char*) "left");

			}
		}

		if (delta > 1000/4) {

			if (inputList.size() >= 1) {
				snake->inputSnake(inputList[inputList.size() - 1]);
				inputList.clear();
			}
			snake->updateSnake();

			update(snake);
			render(window, renderer, snake);

			b = SDL_GetTicks();
		}


	}

	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}


void update(Snake* snake)
{

	for (int i = 0; i < foodList.size(); i++) {

		std::cout << (snake->snakeParts[0].pos.x) << " " << snake->snakeParts[0].pos.y << std::endl;

		if (snake->snakeParts[0].pos.x == foodList[i]->pos.x && snake->snakeParts[0].pos.y == foodList[i]->pos.y) {
			foodList[i]->repositionFood();
			snake->eat();
		}
	}



}


void render(SDL_Window* window, SDL_Renderer* renderer, Snake* snake) 
{

	//Background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Elements
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < foodList.size(); i++) {
		SDL_Rect foodCopy = *foodList[i]->rect;
		foodCopy.x += 5;
		foodCopy.y += 5;
		foodCopy.w -= 10;
		foodCopy.h -= 10;

		SDL_RenderFillRect(renderer, &foodCopy);
	}

	for (int i = 0; i < snake->snakeParts.size(); i++) {

		SDL_Rect rectCopy = *snake->snakeParts[i].rect;
		rectCopy.h -= 2;
		rectCopy.w -= 2;

		SDL_RenderFillRect(renderer, &rectCopy);
	}



	SDL_RenderPresent(renderer);
}
