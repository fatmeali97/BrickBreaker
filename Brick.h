#pragma once
#include <SDL.h>
#include <string>

class Brick
{
public:
	void SetBrick(std::string brick_name);

	void SetPosition(int x, int y);
	void DrawBrick(SDL_Renderer* ren);

private:
	std::string brick_name;
	int xPos;
	int yPos;
};

