#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "Brick.h"
#include "Ball.h"
#include "BallHolder.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	bool Init(const char* title,
		int xpos,
		int ypos,
		int width,
		int height,
		int flags);

	void Render();
	void Update();
	void HandleEvents();
	void Clean();
	bool IsRunning();

	void DrawMap();
	void DrawBall();
	void DrawBallHolder();

	void LoadAndPlaySound();

private:

	void LoadTextures();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	

	void InitMap();
	std::vector<std::vector<int> > mapCord;
	std::vector<Brick> bricks;

	void InitBall();
	Ball ball;

	void InitHolder();
	BallHolder holder;

	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool isMovingDown = false;
	bool isMovingUp = false;

	bool isHavingCollision = false;
	bool isBallMoving = false;

	void SolveWallCollision();
	void SolveBrickCollision();

	bool isGameOver = false;
	
	std::string backgroundName; 
};
