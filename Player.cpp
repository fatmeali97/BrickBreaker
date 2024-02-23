#include "Player.h"
#include <string>
#include "TextureManager.h"

void Player::SetPoints(int points)
{
	m_points = points;
}

int Player::GetPoints()
{
	return m_points;
}

void Player::IncreasePoints(int points)
{
	m_points = m_points + points;
}

bool Player::InitPoints(SDL_Renderer* ren)
{
	if (TTF_Init() == -1) // return error
	{
		return false;
	}

	font1 = TTF_OpenFont("./assets/fonts/Arcade.ttf", 40);

	SDL_Surface* tempSurfaceText = NULL;
	tempSurfaceText = TTF_RenderText_Blended(font1, "Points: ", { 255,255,255,255 });
	textTexture = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "0", { 255,255,255,255 });
	pointsTextTexture = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

	int tw, th;
	SDL_QueryTexture(pointsTextTexture, 0, 0, &tw, &th);
	SDL_QueryTexture(textTexture, 0, 0, &tw, &th);

	dRectText = { 10,15,tw,th };
	dRectText2 = { 130,12,35,45 };
	dRectText3 = { 320,220,600,400 };


	SDL_FreeSurface(tempSurfaceText);

	//TTF_CloseFont(font1);

	m_points = 0;

	return true;
}


void Player::RenderScore(SDL_Renderer* ren)
{
	if (!font1)
		return;

	SDL_Surface* tempSurfaceText = NULL;
	int tw, th;
	SDL_QueryTexture(pointsTextTexture, 0, 0, &tw, &th);
	tempSurfaceText = TTF_RenderText_Blended(font1, std::to_string(m_points).data(), {255,255,255,255});
	pointsTextTexture = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

	SDL_RenderCopy(ren, textTexture, NULL, &dRectText);
	SDL_RenderCopy(ren, pointsTextTexture, NULL, &dRectText2);

	SDL_FreeSurface(tempSurfaceText);
}

void Player::DrawLives(SDL_Renderer* ren)
{
	for (int i = 0; i < m_lives; ++i)
	{
		TextureManager::Instance()->DrawTexture("lives",
			{ m_livesXpos + (i * 40), m_livesYpos, m_heartWidth, m_heartHeight}, ren);
	}
	
}

void Player::DecreaseLives()
{
	m_lives = m_lives - 1;
}

int Player::GetLives()
{
	return m_lives;;
}

void Player::ResetPlayerData() 
{
	m_lives = 2;
	m_points = 0;
}

void Player::GameOver(SDL_Renderer* ren)
{
	SDL_Surface* tempSurfaceText = NULL;
	int tw, th;
	SDL_QueryTexture(gameOverText, 0, 0, &tw, &th);
	tempSurfaceText = TTF_RenderText_Blended(font1, "Game Over", {255,255,255,255});
	gameOverText = SDL_CreateTextureFromSurface(ren, tempSurfaceText);


	SDL_FreeSurface(tempSurfaceText);
	if (m_lives == 0)
	{
		SDL_RenderCopy(ren, gameOverText, NULL, &dRectText3);
		TextureManager::Instance()->DrawTexture("gameOver",
			{ 0, 0, 1280, 720 }, ren);

	}
}

void Player::StartGame(SDL_Renderer* ren)
{
	if (isGameStart)
	{
		SDL_RenderCopy(ren, gameOverText, NULL, &dRectText3);
			TextureManager::Instance()->DrawTexture("Start",
				{ 0, 0, 1280, 720 }, ren);
	}
	
}

void Player::SetIsGameStart(bool isGameStart)
{
	this->isGameStart = isGameStart;
}

bool Player::GetIsGameStart()
{
	return isGameStart;
}
