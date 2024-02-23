#include "Game.h"
#include <iostream>

Game* game = NULL;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;


const int FramePerSecond = 60; 

void limitFPS(unsigned int elapseTimeFromProgramStartBeforeGameUpdate)
{
	double elapseTimeFromProgramStartAfterUpdate = SDL_GetTicks(); 
	double diffrenceInTimeBetweenBeeforeAndAfter = elapseTimeFromProgramStartAfterUpdate - elapseTimeFromProgramStartBeforeGameUpdate; 
	double frameDuration = 1000 / FramePerSecond;

	if (frameDuration > diffrenceInTimeBetweenBeeforeAndAfter)
	{
		double timeToWait = frameDuration - diffrenceInTimeBetweenBeeforeAndAfter;
		SDL_Delay(timeToWait);
	}
}

int main(int argc, char* argv[])
{
	game = new Game();

	game->Init("My new window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	game->LoadAndPlaySound();
	
	while (game->IsRunning())
	{
		unsigned int elapseTimeFromProgramStartBeforeGameUpdate = SDL_GetTicks(); 
		
		game->HandleEvents();
		game->Update();
		game->Render();
		
		limitFPS(elapseTimeFromProgramStartBeforeGameUpdate);
	}

	game->Clean();
	
	return 0;

};