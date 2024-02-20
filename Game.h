#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "Ball.h"
#include "BallHolder.h"

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title,
		int xpos,
		int ypos,
		int width,
		int height,
		int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();

	void DrawMap();
	void DrawBall();
	void DrawBallHolder();
private:
	void loadTextures();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;

	void InitMap();
	std::vector<std::vector<int> > mapCord;

	void InitBall();
	Ball ball;

	void InitHolder();
	BallHolder holder;

	void MoveBall();
	bool isMoving = true;
};