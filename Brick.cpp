#include "Brick.h"
#include "TextureManager.h"
#include <iostream>

void Brick::SetPosition(int x, int y)
{
	m_brickX = x;
	m_brickY = y;
}

void Brick::SetBrickWidth(int width)
{
	this->m_brickWidth = width;
}

void Brick::SetBrickStrength(int strength)
{
	this->m_strength = strength;
}

void Brick::SetBrickHeight(int height)
{
	this->m_brickHeight = height;
}

void Brick::DecreaseStrength(int strength)
{
	m_strength = m_strength - strength;
}

int Brick::GetBrickWidth() const
{
	return m_brickWidth;
}

int Brick::GetBrickHeight() const
{
	return m_brickHeight;
}

int Brick::GetBrickStrength() const
{
	return m_strength;
}

int Brick::GetBrickX() const
{
	return m_brickX;
}

int Brick::GetBrickY() const
{
	return m_brickY;
}

void Brick::DrawBrick(SDL_Renderer* ren)
{
	if (GetBrickStrength() == 1)
	{
		TextureManager::Instance()->DrawTexture("YellowBrick",
			{ GetBrickX(), GetBrickY(),
			GetBrickWidth(), GetBrickHeight() }, ren);
	}
	else if (GetBrickStrength() == 2)
	{
		TextureManager::Instance()->DrawTexture("GreyBrick",
			{GetBrickX(), GetBrickY(),
			GetBrickWidth(), GetBrickHeight() }, ren);
	}
}
