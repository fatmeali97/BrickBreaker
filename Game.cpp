//Game.cpp
#include "Game.h"
#include "Brick.h"
#include "TextureManager.h"
#include "Brick.h"
#include <iostream>
#include <vector>

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) //window init success
		{
			std::cout << "window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				
				loadTextures();
				InitMap();
			}
			else
			{
				std::cout << "renderer init failed\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init failed\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false;
	}
	std::cout << "init success\n";
	running = true;
	return true;
}



void Game::render()
{
	SDL_RenderClear(renderer);
	DrawMap();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: running = false; break;

		case SDL_KEYDOWN:
		{
		}
		default: break;
		}
	}
}

void Game::update()
{}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::isRunning()
{
	return Game::running;
}

void Game::DrawMap()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	int mapColumCount = mapCord.size();
	int mapRowCount = mapCord[0].size();

	int brickWidth = windowWidth / mapColumCount;
	int brickHeight = windowHeight / mapRowCount;
	
	
	for (int i = 0; i < mapCord.size(); ++i) //colums
	{
		for (int j = 0; j < mapCord[i].size(); ++j) // rows
		{
			int xPos = i * brickWidth;
			int yPos = j * brickHeight;
			int value = mapCord[i][j];
			 
			if (value == 1)
			{
				TextureManager::Instance()->drawTexture("YellowBrick",
					{ xPos, yPos, brickWidth, brickHeight }, renderer);
			}
			else if (value == 2)
			{
				TextureManager::Instance()->drawTexture("GreyBrick",
					{ xPos, yPos, brickWidth, brickHeight }, renderer);
			}
		}
	}

}

void Game::loadTextures()
{
	SDL_SetRenderDrawColor(renderer, 230, 230, 230, 0);

	TextureManager::Instance()->loadTexture("./assets/grey_Brick.png",
		"GreyBrick",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/yellow_Brick.png",
		"YellowBrick",
		renderer);
}

void Game::InitMap()
{
	mapCord =
	{
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	//{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	//{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	//{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	//{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	};
}

Game::Game()
{
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}

Game::~Game()
{
	delete window;
	delete renderer;
}