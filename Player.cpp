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

	m_font = TTF_OpenFont("./assets/fonts/Arcade.ttf", 40);

	SDL_Surface* tempSurfaceText = NULL;
	tempSurfaceText = TTF_RenderText_Blended(m_font, "Points: ", { 0,0,0,255 });
	m_textTexture = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

	int tw, th;
	SDL_QueryTexture(m_pointsTextTexture, 0, 0, &tw, &th);
	SDL_QueryTexture(m_textTexture, 0, 0, &tw, &th);

	m_textDestRect = { 10,15,tw,th };
	m_pointsDestRect = { 130,12,35,45 };

	SDL_FreeSurface(tempSurfaceText);
	m_points = 0;
	return true;
}


void Player::RenderScore(SDL_Renderer* ren)
{
	if (!m_font)
		return;

	SDL_Surface* tempSurfaceText = NULL;
	int tw, th;
	SDL_QueryTexture(m_pointsTextTexture, 0, 0, &tw, &th);
	tempSurfaceText = TTF_RenderText_Blended(m_font, std::to_string(m_points).data(), {0,0,0,255});
	m_pointsTextTexture = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

	SDL_RenderCopy(ren, m_textTexture, NULL, &m_textDestRect);
	SDL_RenderCopy(ren, m_pointsTextTexture, NULL, &m_pointsDestRect);

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
		TextureManager::Instance()->DrawTexture("gameOver",
			{ 0, 0, 1280, 720 }, ren);
	}
}

void Player::StartGame(SDL_Renderer* ren)
{
	if (m_isGameAtStartingPosition)
	{
			TextureManager::Instance()->DrawTexture("Start",
				{ 0, 0, 1280, 720 }, ren);
	}
}

void Player::WinGame(SDL_Renderer* ren)
{
	if (m_isGameWin)
	{
		TextureManager::Instance()->DrawTexture("winner",
			{ 0, 0, 1280, 720 }, ren);
	}
}

void Player::SetIsGameAtStartingPosition(bool isGameAtStartingPosition)
{
	this->m_isGameAtStartingPosition = isGameAtStartingPosition;
}

bool Player::GetIsGameAtStartingPosition()
{
	return m_isGameAtStartingPosition;
}

void Player::SetIsGameOver(bool isGameOver)
{
	this->m_isGameOver = isGameOver;
}

bool Player::GetIsGameOver()
{
	return m_isGameOver;
}

void Player::SetIsGameWin(bool isGameWin)
{
	this->m_isGameWin = isGameWin;
}

bool Player::GetIsGameWin()
{
	return m_isGameWin;
}

Player::Player()
{}

Player::~Player()
{
	TTF_CloseFont(m_font);
}
