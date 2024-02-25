#pragma once
#include <SDL.h>
class Ball
{
public:
	void SetPosition(int x, int y);
	void SetIsBallMovingRight(bool isBallMovingRight);
	void SetIsBallMovingLeft(bool isBallMovingLeft);
	void SetIsBallMovingDown(bool isBallMovingDown);
	void SetIsBallMovingUp(bool isBallMovingUp);
	void SetIsBallMoving(bool isBallMoving);

	int GetSpeed() const;
	int GetBallWidth() const;
	int GetBallHeight() const;
	int GetBallX() const;
	int GetBallY() const;

	bool GetIsBallMovingRight();
	bool GetIsBallMovingLeft();
	bool GetIsBallMovingDown();
	bool GetIsBallMovingUp();
	bool GetIsBallMoving();

	void Draw(SDL_Renderer* ren);

private:
	int const m_ballWidth = 35;
	int const m_ballHeight = 35;
	int m_speed = 5;
	int m_ballX;
	int m_ballY;

	bool m_isBallMovingRight = false;
	bool m_isBallMovingLeft = false;
	bool m_isBallMovingDown = false;
	bool m_isBallMovingUp = false;
	bool m_isBallMoving = false;
};

