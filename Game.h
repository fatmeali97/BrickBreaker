#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>

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
private:
	void loadTextures();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;

	void InitMap();
	std::vector<std::vector<int> > mapCord;
	//int mapCord[20][23]; //my screen 
};