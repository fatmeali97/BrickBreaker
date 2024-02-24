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
	tempSurfaceText = TTF_RenderText_Blended(font1, "Points: ", { 0,0,0,255 });
	textTexture = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

	int tw, th;
	SDL_QueryTexture(pointsTextTexture, 0, 0, &tw, &th);
	SDL_QueryTexture(textTexture, 0, 0, &tw, &th);

	dRectText = { 10,15,tw,th };
	dRectText2 = { 130,12,35,45 };
	dRectText3 = { 320,220,600,400 };

	SDL_FreeSurface(tempSurfaceText);
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
	tempSurfaceText = TTF_RenderText_Blended(font1, std::to_string(m_points).data(), {0,0,0,255});
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

void Player::DecreaseLives(int lives)
{
	m_lives = m_lives - lives;
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
	if (m_lives == 0)
	{
		SDL_RenderCopy(ren, gameOverText, NULL, &dRectText3);
		TextureManager::Instance()->DrawTexture("gameOver",
			{ 0, 0, 1280, 720 }, ren);
	}
}

void Player::StartGame(SDL_Renderer* ren)
{
	if (isGameAtStartingPosition)
	{
		SDL_RenderCopy(ren, gameOverText, NULL, &dRectText3);
			TextureManager::Instance()->DrawTexture("Start",
				{ 0, 0, 1280, 720 }, ren);
	}
}

void Player::WinGame(SDL_Renderer* ren)
{
	if (isGameWin)
	{
		SDL_RenderCopy(ren, gameOverText, NULL, &dRectText3);
		TextureManager::Instance()->DrawTexture("winner",
			{ 0, 0, 1280, 720 }, ren);
	}
}

void Player::SetIsGameAtStartingPosition(bool isGameAtStartingPosition)
{
	this->isGameAtStartingPosition = isGameAtStartingPosition;
}

bool Player::GetIsGameAtStartingPosition()
{
	return isGameAtStartingPosition;
}

void Player::SetIsGameOver(bool isGameOver)
{
	this->isGameOver = isGameOver;
}

bool Player::GetIsGameOver()
{
	return isGameOver;
}

void Player::SetIsGameWin(bool isGameWin)
{
	this->isGameWin = isGameWin;
}

bool Player::GetIsGameWin()
{
	return isGameWin;
}

Player::Player()
{
	dRectText = 0;
}

Player::~Player()
{
	TTF_CloseFont(font1);
}
