//Game.cpp
#include "Game.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include <iostream>
#include <vector>

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
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

				time_t t;
				srand((unsigned)time(&t));

				
				LoadTextures();
				InitMap();
				InitBall();
				InitHolder();
				//InitPoints();
				//InitLives();
				player.InitPoints(renderer);
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



void Game::Render()
{
	SDL_RenderClear(renderer);

	DrawMap();
	DrawBall();
	DrawBallHolder();
	player.RenderScore(renderer);
	player.DrawLives(renderer);
	player.GameOver(renderer);
	player.StartGame(renderer);

	SDL_RenderPresent(renderer);
}

void Game::HandleEvents()
{
	auto keystate = SDL_GetKeyboardState(NULL);

	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	//continuous-response keys
	int ballMoveWidth = 0; 
	if (keystate[SDL_SCANCODE_LEFT])
	{
		int xpos = holder.GetBallHolderX();
		int newXpos = xpos - holder.GetSpeed();
		holder.SetBallHolderX(newXpos);

		if (holder.GetBallHolderX() < 0)
		{
			holder.SetBallHolderX(0);
		}

		newXpos = holder.GetBallHolderX();
		ballMoveWidth = newXpos - xpos; // to keep ball with holder
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		int xpos = holder.GetBallHolderX();
		int newXpos = xpos + holder.GetSpeed();
		holder.SetBallHolderX(newXpos);

		int mostRightPos = windowWidth - holder.GetBallHolderWidth();
		if (holder.GetBallHolderX() > mostRightPos)
		{
			holder.SetBallHolderX(mostRightPos);
		}

		newXpos = holder.GetBallHolderX();
		ballMoveWidth = newXpos - xpos;
	}

	if (!ball.GetIsBallMoving())
	{
		int xpos = ball.GetBallX();
		ball.SetPosition(xpos + ballMoveWidth, ball.GetBallY());
	}

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: running = false; break;

		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (player.GetIsGameStart() == true)
				{
					player.SetIsGameStart(false);
					return;
				}

				if (isGameOver)
				{
					player.ResetPlayerData();
					isGameOver = false;
				}
				
				else 
				{
				//player.SetIsGameStart(true);
				ball.SetIsBallMovingUp(true);
				ball.SetIsBallMovingRight(true);
				ball.SetIsBallMoving(true);
				}
				
			}

			if (event.key.keysym.sym == SDLK_KP_ENTER)
			{
			
			}

		}; break;
		
		default: break;
		}
	}
}

void Game::Update()
{
	int xpos = ball.GetBallX();
	int ypos = ball.GetBallY();
	int speed = ball.GetSpeed();

 	if (ball.GetIsBallMoving())
	{
		int newXpos = xpos;
		int newYpos = ypos;
		if (ball.GetIsBallMovingRight())
		{
			newXpos = xpos + speed;
		}
		if (ball.GetIsBallMovingLeft())
		{
			newXpos = xpos - speed;
		}
		if (ball.GetIsBallMovingDown())
		{
			newYpos = ypos + speed;
		}
		if (ball.GetIsBallMovingUp())
		{
			newYpos = ypos - speed;
		}
		ball.SetPosition(newXpos, newYpos);
	}

	SolveWallCollision();
	SolveBrickCollision();
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::IsRunning()
{
	return Game::running;
}

void Game::DrawMap()
{

	for (int i = 0; i < bricks.size(); ++i)
	{
		if (bricks.at(i).GetBrickStrength()  == 1)
		{
			/*bricks.at(i).SetBrick("YellowBrick");
			bricks.at(i).DrawBrick(renderer);*/
			TextureManager::Instance()->DrawTexture("YellowBrick",
				{ bricks.at(i).GetBrickX(), bricks.at(i).GetBrickY(),
				bricks.at(i).GetBrickWidth(), bricks.at(i).GetBrickHeight() }, renderer);
		}
		else if (bricks.at(i).GetBrickStrength() == 2)
		{
		/*	bricks.at(i).SetBrick("GreyBrick");
			bricks.at(i).DrawBrick(renderer);*/
			TextureManager::Instance()->DrawTexture("GreyBrick",
				{ bricks.at(i).GetBrickX(), bricks.at(i).GetBrickY(),
				bricks.at(i).GetBrickWidth(), bricks.at(i).GetBrickHeight() }, renderer);
		}
	}
}

void Game::DrawBall()
{
	TextureManager::Instance()->DrawTexture("Ball",
		{ball.GetBallX(), ball.GetBallY(), ball.GetBallWidth(), ball.GetBallHeight()},
		renderer);
}

void Game::DrawBallHolder()
{
	TextureManager::Instance()->DrawTexture("Desc",
		{holder.GetBallHolderX(), holder.GetBallHolderY(),
		holder.GetBallHolderWidth(), holder.GetBallHolderHeight()},
		renderer);
}


void Game::LoadAndPlaySound()
{
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/Sakura-Girl-Beach.mp3",
		"backgroudMusic", 1);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/gameOver.wav",
		"gameOver", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/ballHitDesc.wav",
		"ballHitDesc", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/start.wav",
		"start", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/hitBrick.wav",
		"hitBrick", 0);

	//SoundManager::Instance()->PlayMusic("backgroudMusic", -1);

	//SoundManager::Instance()->PlaySound("start", 0, 0);
	//SoundManager::Instance()->PlaySound("hitBrick", 0, 0);
	//SoundManager::Instance()->PlaySound("gameOver", 0, 0);
}

void Game::LoadTextures()
{
	SDL_SetRenderDrawColor(renderer, 230, 230, 230, 0);

	TextureManager::Instance()->LoadTexture("./assets/grey_Brick.png",
		"GreyBrick",
		renderer);

	TextureManager::Instance()->LoadTexture("./assets/yellow_Brick.png",
		"YellowBrick",
		renderer);

	TextureManager::Instance()->LoadTexture("./assets/ball.png",
		"Ball",
		renderer);

	TextureManager::Instance()->LoadTexture("./assets/desc.png",
		"Desc",
		renderer);

	TextureManager::Instance()->LoadTexture("./assets/heart.png",
		"lives",
		renderer);

	TextureManager::Instance()->LoadTexture("./assets/gameOver.jpg",
		"gameOver",
		renderer);

	TextureManager::Instance()->LoadTexture("./assets/start.jpg",
		"Start",
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

	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	int mapColumCount = mapCord.size();
	int mapRowCount = mapCord[0].size();

	int brickWidth = windowWidth / mapColumCount;
	int brickHeight = windowHeight / mapRowCount;

	bricks.clear();
	for (int i = 0; i < mapCord.size(); ++i) //colums
	{
		for (int j = 0; j < mapCord[i].size(); ++j) // rows
		{
			int xPos = i * brickWidth;
			int yPos = j * brickHeight;
			int newValue = mapCord[i][j];

			Brick tempBrick;
			tempBrick.SetBrickStrength(newValue);
			tempBrick.SetBrickWidth(brickWidth);
			tempBrick.SetBrickHeight(brickHeight);
			tempBrick.SetPosition(xPos, yPos);
			bricks.push_back(tempBrick);
		}
	}
}

void Game::InitBall()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	int ballX = (windowWidth / 2) - (ball.GetBallWidth() / 2);
	int ballY = windowHeight - ball.GetBallHeight() - holder.GetBallHolderHeight();

	ball.SetPosition(ballX, ballY);
}

void Game::InitHolder()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	int ballHolderX = (windowWidth / 2) - (holder.GetBallHolderWidth() / 2);
	int ballHolderY = windowHeight - holder.GetBallHolderHeight();

	holder.SetPosition(ballHolderX, ballHolderY);
}

void Game::SolveWallCollision()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	// solve right collision
	if (ball.GetBallX() > windowWidth - ball.GetBallWidth())
	{
		ball.SetIsBallMovingLeft(true);
		ball.SetIsBallMovingRight(false);
	}
	// solve left collision
	else if (ball.GetBallX() <= 0)
	{
		ball.SetIsBallMovingLeft(false);
		ball.SetIsBallMovingRight(true);
	}

	// solve top collision
	if (ball.GetBallY() <= 0)
	{
		ball.SetIsBallMovingDown(true);
		ball.SetIsBallMovingUp(false);
	}
	// solve bottom collision
	if (ball.GetBallY() + ball.GetBallHeight() > windowHeight - holder.GetBallHolderHeight())
	{
		int holderBegin = holder.GetBallHolderX();
		int holderEnd = holder.GetBallHolderX() + holder.GetBallHolderWidth();
		if (ball.GetBallX() + ball.GetBallWidth() > holderBegin && ball.GetBallX() < holderEnd)
		{
			ball.SetIsBallMovingDown(false);
			ball.SetIsBallMovingUp(true);
			SoundManager::Instance()->PlaySound("ballHitDesc", 0, 0);
		}
		else
		{
			player.DecreaseLives();
			if (player.GetLives() > 0) // have lives
			{
				ResetGame();
			}
			else
			{
				GameOver();
			
			}
		}
	}
}



void Game::ResetGame()
{
	//ball.SetIsBallMovingDown(false);
	//ball.SetIsBallMovingUp(false);
	//ball.SetIsBallMovingLeft(false);
	//ball.SetIsBallMovingRight(false);
	ball.SetIsBallMoving(false);

	InitBall();
	InitHolder();
}

void Game::GameOver()
{
	ball.SetIsBallMovingDown(false);
	ball.SetIsBallMovingUp(false);
	ball.SetIsBallMovingLeft(false);
	ball.SetIsBallMovingRight(false);
	ball.SetIsBallMoving(false);

	InitMap();
	InitBall();
	InitHolder();
	//player.SetPoints(0);

	isGameOver = true;

	SoundManager::Instance()->PlaySound("gameOver", 0, 0);
}



void Game::SolveBrickCollision()
{
	for (int i = 0; i < bricks.size(); ++i)
	{
		if (bricks.at(i).GetBrickStrength() > 0)
		{
			int ballLeft = ball.GetBallX();
			int ballRight = ball.GetBallX() + ball.GetBallWidth();

			int brickLeft = bricks.at(i).GetBrickX();
			int brickRight = bricks.at(i).GetBrickX() + bricks.at(i).GetBrickWidth();

			bool isOutsideFromLeft = (ballRight < brickLeft);
			if (isOutsideFromLeft)
			{
				continue;
			}
			bool isOutsideFromRight = (ballLeft > brickRight);
			if (isOutsideFromRight)
			{				
				continue;
			}

			int ballTop = ball.GetBallY();
			int ballBottom = ball.GetBallY() + ball.GetBallHeight();

			int brickTop = bricks.at(i).GetBrickY();
			int brickBottom = bricks.at(i).GetBrickY() + bricks.at(i).GetBrickHeight();

			bool isOutsideFromTop = (ballBottom < brickTop);
			if (isOutsideFromTop)
			{
				continue;
			}

			bool isOutsideFromBottom = (ballTop > brickBottom);
			if (isOutsideFromBottom)
			{
				continue;
			}

			//collision happen;
			int value = bricks.at(i).GetBrickStrength();
			int newValue = value - 1;
			bricks.at(i).SetBrickStrength(newValue);

			if (newValue == 0)
			{
				SDL_DestroyTexture(NULL);
			}

			player.IncreasePoints(1);

			SoundManager::Instance()->PlaySound("hitBrick", 0, 0);
			
			if (ball.GetIsBallMovingUp())
			{
				ball.SetIsBallMovingDown(true);
				ball.SetIsBallMovingUp(false);
			}
			else if (ball.GetIsBallMovingDown())
			{
				ball.SetIsBallMovingDown(false);
				ball.SetIsBallMovingUp(true);
			}
			break;
		}
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
