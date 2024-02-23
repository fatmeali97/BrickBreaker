#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Player
{
public:
	void SetPoints(int points);
	int GetPoints();
	void IncreasePoints(int points);
	bool InitPoints(SDL_Renderer* ren);
	void RenderScore(SDL_Renderer* ren);
	void DrawLives(SDL_Renderer* ren);
	void DecreaseLives();
	int GetLives();
	void ResetPlayerData();
	void GameOver(SDL_Renderer* ren);
	void StartGame(SDL_Renderer* ren);

	void SetIsGameStart(bool isGameStart);
	bool GetIsGameStart();
	
private:
	int m_points = 0;
	int m_lives = 2;

	int m_heartWidth = 40;
	int m_heartHeight = 40;
	int m_livesXpos = 1000;
	int m_livesYpos = 15;

	bool isGameStart = true;

	TTF_Font* font1;
	SDL_Texture* pointsTextTexture,	* textTexture, *gameOverText;
	SDL_Rect dRectText,dRectText2, dRectText3;
};

