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
	bool Init(const char* title, int xpos, int ypos, int width, int height,int flags);
	bool IsRunning();
	void Render();
	void Update();
	void HandleEvents();
	void Clean();
	
	void DrawMap();
	void LoadAndPlaySound();

private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_renderer = NULL;
	bool m_running;

	void LoadTextures();
	void InitMap();
	void InitBall();
	void InitHolder();
	void SolveWallCollision();
	void SolveBrickCollision();
	void ResetGame();
	void GameOver();
	void Win();

	std::vector<std::vector<int> > m_mapCord;
	std::vector<Brick> m_bricks;
	Ball m_ball;
	BallHolder m_holder;
	Player m_player;
	 
};