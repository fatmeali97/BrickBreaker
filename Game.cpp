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

		m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_window != 0) //window init success
		{
			std::cout << "window creation success\n";
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
			if (m_renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

				time_t t;
				srand((unsigned)time(&t));

				LoadTextures();
				InitMap();
				InitBall();
				InitHolder();
				m_player.InitPoints(m_renderer);
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
	m_running = true;
	return true;
}



void Game::Render()
{
	SDL_RenderClear(m_renderer);

	DrawMap();
	m_ball.Draw(m_renderer);
	m_holder.Draw(m_renderer);
	m_player.RenderScore(m_renderer);
	m_player.DrawLives(m_renderer);
	m_player.GameOver(m_renderer);
	m_player.StartGame(m_renderer);
	m_player.WinGame(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void Game::HandleEvents()
{
	auto keystate = SDL_GetKeyboardState(NULL);

	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

	//continuous-response keys
	int ballMoveWidth = 0; 
	if (keystate[SDL_SCANCODE_LEFT])
	{
		int xpos = m_holder.GetBallHolderX();
		int newXpos = xpos - m_holder.GetSpeed();
		m_holder.SetBallHolderX(newXpos);

		if (m_holder.GetBallHolderX() < 0)
		{
			m_holder.SetBallHolderX(0);
		}
		newXpos = m_holder.GetBallHolderX();
		ballMoveWidth = newXpos - xpos; // to keep ball with holder
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		int xpos = m_holder.GetBallHolderX();
		int newXpos = xpos + m_holder.GetSpeed();
		m_holder.SetBallHolderX(newXpos);

		int mostRightPos = windowWidth - m_holder.GetBallHolderWidth();
		if (m_holder.GetBallHolderX() > mostRightPos)
		{
			m_holder.SetBallHolderX(mostRightPos);
		}

		newXpos = m_holder.GetBallHolderX();
		ballMoveWidth = newXpos - xpos;
	}

	if (!m_ball.GetIsBallMoving())
	{
		int xpos = m_ball.GetBallX();
		m_ball.SetPosition(xpos + ballMoveWidth, m_ball.GetBallY());
	}

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: m_running = false; break;

		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (m_player.GetIsGameAtStartingPosition() == true) // we have starting image;
				{
					SoundManager::Instance()->PlayMusic("backgroudMusic", -1);
					SoundManager::Instance()->ChangeVolume("backgroundMusic");
					SoundManager::Instance()->PlaySound("start", 0, 0);
					m_player.SetIsGameAtStartingPosition(false); // starting game part, images is no more on screen;
					SDL_Delay(700);
					return;
				}

				else if (m_player.GetIsGameOver() == true) // if the game is ended, restart
				{
					m_player.ResetPlayerData();
					m_player.SetIsGameOver(false);
					m_player.SetIsGameAtStartingPosition(true);
				}

				else if (m_player.GetIsGameWin() == true) // if the player win the game, restart data
				{
					m_ball.SetIsBallMoving(false);
					m_player.SetIsGameWin(false);
					m_player.SetIsGameAtStartingPosition(true);
				}

				else if (m_ball.GetIsBallMoving() == false) // to start game 
				{
			
					m_ball.SetIsBallMovingUp(true);
					m_ball.SetIsBallMovingRight(true);
					m_ball.SetIsBallMoving(true);
					return;
				}
			}

		}; break;
		
		default: break;
		}
	}
}

void Game::Update()
{
	int xpos = m_ball.GetBallX();
	int ypos = m_ball.GetBallY();
	int speed = m_ball.GetSpeed();

 	if (m_ball.GetIsBallMoving())
	{
		int newXpos = xpos;
		int newYpos = ypos;
		if (m_ball.GetIsBallMovingRight())
		{
			newXpos = xpos + speed;
		}
		if (m_ball.GetIsBallMovingLeft())
		{
			newXpos = xpos - speed;
		}
		if (m_ball.GetIsBallMovingDown())
		{
			newYpos = ypos + speed;
		}
		if (m_ball.GetIsBallMovingUp())
		{
			newYpos = ypos - speed;
		}
		m_ball.SetPosition(newXpos, newYpos);
	}
	SolveWallCollision();
	SolveBrickCollision();
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

bool Game::IsRunning()
{
	return Game::m_running;
}

void Game::DrawMap()
{
	TextureManager::Instance()->DrawTexture("background",{ 0, 0, 1280, 720 }, m_renderer);

	for (int i = 0; i < m_bricks.size(); ++i)
	{
		m_bricks.at(i).DrawBrick(m_renderer);
	}
}

void Game::LoadAndPlaySound()
{
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/Sakura-Girl-Beach.mp3",
		"backgroudMusic", 1);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/gameOver.wav",
		"gameOver", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/hitDesc.wav",
		"ballHitDesc", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/start.wav",
		"start", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/hitBrick.wav",
		"hitBrick", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/win.wav",
		"win", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/push.wav",
		"pushBall", 0);
	SoundManager::Instance()->LoadMusicAndSound("./assets/sound/missingBall.wav",
		"missingBall", 0);
}

void Game::LoadTextures()
{
	SDL_SetRenderDrawColor(m_renderer, 230, 230, 230, 0);

	TextureManager::Instance()->LoadTexture("./assets/grey_Brick.png",
		"GreyBrick",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/yellow_Brick.png",
		"YellowBrick",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/ball.png",
		"Ball",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/desc.png",
		"Desc",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/heart.png",
		"lives",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/gameOver.png",
		"gameOver",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/start.png",
		"Start",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/winner.png",
		"winner",
		m_renderer);

	TextureManager::Instance()->LoadTexture("./assets/background.png",
		"background",
		m_renderer);
}

void Game::InitMap()
{
	m_mapCord =
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
	SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

	int mapColumCount = m_mapCord.size();
	int mapRowCount = m_mapCord[0].size();

	int brickWidth = windowWidth / mapColumCount;
	int brickHeight = windowHeight / mapRowCount;

	m_bricks.clear();

	for (int i = 0; i < m_mapCord.size(); ++i) //colums
	{
		for (int j = 0; j < m_mapCord[i].size(); ++j) // rows
		{
			int xPos = i * brickWidth;
			int yPos = j * brickHeight;
			int newValue = m_mapCord[i][j];

			Brick tempBrick;
			tempBrick.SetBrickStrength(newValue);
			tempBrick.SetBrickWidth(brickWidth);
			tempBrick.SetBrickHeight(brickHeight);
			tempBrick.SetPosition(xPos, yPos);
			m_bricks.push_back(tempBrick);
		}
	}
}

void Game::InitBall()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

	int ballX = (windowWidth / 2) - (m_ball.GetBallWidth() / 2);
	int ballY = windowHeight - m_ball.GetBallHeight() - m_holder.GetBallHolderHeight();

	m_ball.SetPosition(ballX, ballY);
}

void Game::InitHolder()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

	int ballHolderX = (windowWidth / 2) - (m_holder.GetBallHolderWidth() / 2);
	int ballHolderY = windowHeight - m_holder.GetBallHolderHeight();

	m_holder.SetPosition(ballHolderX, ballHolderY);
}

void Game::SolveWallCollision()
{
	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

	// solve right collision
	if (m_ball.GetBallX() > windowWidth - m_ball.GetBallWidth())
	{
		m_ball.SetIsBallMovingLeft(true);
		m_ball.SetIsBallMovingRight(false);
	}
	// solve left collision
	else if (m_ball.GetBallX() <= 0)
	{
		m_ball.SetIsBallMovingLeft(false);
		m_ball.SetIsBallMovingRight(true);
	}

	// solve top collision
	if (m_ball.GetBallY() <= 0)
	{
		m_ball.SetIsBallMovingDown(true);
		m_ball.SetIsBallMovingUp(false);
	}
	// solve bottom collision
	if (m_ball.GetBallY() + m_ball.GetBallHeight() > windowHeight - m_holder.GetBallHolderHeight())
	{
		int holderBegin = m_holder.GetBallHolderX();
		int holderEnd = m_holder.GetBallHolderX() + m_holder.GetBallHolderWidth();
		if (m_ball.GetBallX() + m_ball.GetBallWidth() > holderBegin && m_ball.GetBallX() < holderEnd)
		{
			m_ball.SetIsBallMovingDown(false);
			m_ball.SetIsBallMovingUp(true);
			SoundManager::Instance()->PlaySound("ballHitDesc", 0, 0);
		}
		else
		{
			m_player.DecreaseLives(1);
			SoundManager::Instance()->PlaySound("missingBall", 0, 0);
			if (m_player.GetLives() > 0) // have lives
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
	m_ball.SetIsBallMoving(false);
	InitBall();
	InitHolder();
}

void Game::GameOver()
{
	m_ball.SetIsBallMoving(false);
	m_player.SetIsGameOver(true);
	InitMap();
	InitBall();
	InitHolder();

	SoundManager::Instance()->PlaySound("gameOver", 0, 0);
}

void Game::Win()
{
	m_ball.SetIsBallMoving(false);
	m_player.SetIsGameWin(true);
	InitMap();
	InitBall();
	InitHolder();
	m_player.ResetPlayerData();
	
	SoundManager::Instance()->PlaySound("win", 0, 0);
}



void Game::SolveBrickCollision()
{
	for (int i = 0; i < m_bricks.size(); ++i)
	{
		if (m_bricks.at(i).GetBrickStrength() > 0)
		{
			int ballLeft = m_ball.GetBallX();
			int ballRight = m_ball.GetBallX() + m_ball.GetBallWidth();

			int brickLeft = m_bricks.at(i).GetBrickX();
			int brickRight = m_bricks.at(i).GetBrickX() + m_bricks.at(i).GetBrickWidth();

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

			int ballTop = m_ball.GetBallY();
			int ballBottom = m_ball.GetBallY() + m_ball.GetBallHeight();

			int brickTop = m_bricks.at(i).GetBrickY();
			int brickBottom = m_bricks.at(i).GetBrickY() + m_bricks.at(i).GetBrickHeight();

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
			m_bricks.at(i).DecreaseStrength(1);
			m_player.IncreasePoints(1);

			if (m_player.GetPoints() == 120)
			{
				Win();
			}

			SoundManager::Instance()->PlaySound("hitBrick", 0, 0);
			
			if (m_ball.GetIsBallMovingUp())
			{
				m_ball.SetIsBallMovingDown(true);
				m_ball.SetIsBallMovingUp(false);
			}
			else if (m_ball.GetIsBallMovingDown())
			{
				m_ball.SetIsBallMovingDown(false);
				m_ball.SetIsBallMovingUp(true);
			}
			break;
		}
	}
}

Game::Game()
{
	Game::m_window = NULL;
	Game::m_renderer = NULL;
	Game::m_running = true;
}

Game::~Game()
{
	delete m_window;
	delete m_renderer;
}