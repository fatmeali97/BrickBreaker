#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Player
{
public:
	Player();
	~Player();
	void SetPoints(int points);
	int GetPoints();
	void IncreasePoints(int points);
	bool InitPoints(SDL_Renderer* ren);
	void RenderScore(SDL_Renderer* ren);
	void DrawLives(SDL_Renderer* ren);
	void DecreaseLives(int lives);
	int GetLives();
	void ResetPlayerData();
	void GameOver(SDL_Renderer* ren);
	void StartGame(SDL_Renderer* ren);
	void WinGame(SDL_Renderer* ren);

	void SetIsGameAtStartingPosition(bool isGameAtStartingPosition);
	bool GetIsGameAtStartingPosition();
	void SetIsGameOver(bool isGameOver);
	bool GetIsGameOver();
	void SetIsGameWin(bool isGameWin);
	bool GetIsGameWin();
	
private:
	int m_points = 0;
	int m_lives = 2;
	int m_heartWidth = 40;
	int m_heartHeight = 40;
	int m_livesXpos = 1000;
	int m_livesYpos = 15;

	bool m_isGameAtStartingPosition = true;
	bool m_isGameOver = false;
	bool m_isGameWin = false;

	TTF_Font* m_font;
	SDL_Texture* m_pointsTextTexture;
	SDL_Texture* m_textTexture;
	SDL_Rect m_textDestRect;
	SDL_Rect m_pointsDestRect;
};

