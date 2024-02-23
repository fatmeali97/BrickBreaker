#pragma once
#include <SDL.h>
#include <string>

class Brick
{
public:

	void SetBrick(std::string brick_name);
	void SetPosition(int x, int y);
	void SetBrickWidth(int width);
	void SetBrickStrength(int strength);
	void SetBrickHeight(int height);
	int GetBrickWidth() const;
	int GetBrickHeight() const;
	int GetBrickStrength() const;
	int GetBrickX() const;
	int GetBrickY() const;

	void DrawBrick(SDL_Renderer* ren);

private:
	std::string brick_name;
	int m_brickWidth;
	int m_brickHeight;

	int m_strength;
	int m_brickX;
	int m_brickY;
};

