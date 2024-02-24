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
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	void LoadTextures();

	void InitMap();
	void InitBall();
	void InitHolder();
	void SolveWallCollision();
	void SolveBrickCollision();
	void ResetGame();
	void GameOver();
	void Win();
	std::vector<std::vector<int> > mapCord;
	std::vector<Brick> bricks;
	Ball ball;
	BallHolder holder;
	Player player;
	std::string backgroundName;
};
