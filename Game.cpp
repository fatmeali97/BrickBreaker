//Game.cpp
#include "Game.h"
#include "TextureManager.h"
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
				InitBall();
				InitHolder();
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
	DrawBall();
	DrawBallHolder();

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
			if (event.key.keysym.sym == SDLK_0)
			{
				isMoving = true;
			}
		}; break;
		default: break;
		}
	}
}

void Game::update()
{
	if (isMoving)
	{
		MoveBall();
	}
	else
	{
		MoveBall();
	}
}

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
					{xPos, yPos, brickWidth, brickHeight},
					renderer);
			}
			else if (value == 2)
			{
				TextureManager::Instance()->drawTexture("GreyBrick",
					{xPos, yPos, brickWidth, brickHeight},
					renderer);
			}
		}
	}

}

void Game::DrawBall()
{
	TextureManager::Instance()->drawTexture("Ball",
		{ball.GetBallX(), ball.GetBallY(), ball.GetBallWidth(), ball.GetBallHeight()},
		renderer);
}

void Game::DrawBallHolder()
{
	TextureManager::Instance()->drawTexture("Desc",
		{holder.GetBallHolderX(), holder.GetBallHolderY(),
		holder.GetBallHolderWidth(), holder.GetBallHolderHeight()},
		renderer);
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

	TextureManager::Instance()->loadTexture("./assets/ball.png",
		"Ball",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/desc.png",
		"Desc",
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

void Game::InitBall()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	int ballX = (windowWidth / 2) - (ball.GetBallWidth() / 2);
	int ballY = windowHeight - 70;

	ball.SetPosition(ballX, ballY);
}

void Game::InitHolder()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	int ballHolderX = (windowWidth / 2) - (holder.GetBallHolderWidth() / 2);
	int ballHolderY = windowHeight - 35;

	holder.SetPosition(ballHolderX, ballHolderY);
}

void Game::MoveBall()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	std::cout << ball.GetBallY() << std::endl;

	int xpos = ball.GetBallX(); //623
	int ypos = ball.GetBallY(); //650


	if (ball.GetBallY() > (windowHeight - ball.GetBallHeight()) - 70)
	{
		isMoving = false;
	}
	else if (ball.GetBallY() < 0)
	{
		isMoving = true;
	}

	if (isMoving)
	{
		ball.SetPosition(++xpos, ++ypos);
	}

	else
	{
		ball.SetPosition(--xpos, --ypos);
	}
	

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