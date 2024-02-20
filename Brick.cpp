#include "Brick.h"
#include "TextureManager.h"
#include <iostream>

void Brick::SetBrick(std::string brick_name)
{
	this->brick_name = brick_name;
}

void Brick::SetPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void Brick::DrawBrick(SDL_Renderer* ren)
{
	TextureManager::Instance()->drawTexture("GreyBrick", {0, 0, 179, 106}, ren);
	//TextureManager::Instance()->drawTexture("GreyBrick", { xPos, yPos, 182, 106 }, ren);
}
