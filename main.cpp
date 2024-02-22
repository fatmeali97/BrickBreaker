#include "Game.h"
#include <iostream>

Game* game = NULL;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;


const int FPS = 60; 

void limitFPS(unsigned int startingTick)
{
	if ((1000 / FPS) > SDL_GetTicks() - startingTick) 
	{
		SDL_Delay((1000 / FPS) - (SDL_GetTicks() - startingTick));
	}
}

int main(int argc, char* argv[])
{
	game = new Game();
	game->Init("My new window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE);

	game->LoadAndPlaySound();

	while (game->IsRunning())
	{
		unsigned int startingTick = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		limitFPS(startingTick);
	}

	game->Clean();
	
	return 0;

};