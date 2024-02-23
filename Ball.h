#pragma once

class Ball
{
public:
	void SetPosition(int x, int y);
	int GetSpeed() const;
	int GetBallWidth() const;
	int GetBallHeight() const;
	int GetBallX() const;
	int GetBallY() const;

	void SetIsBallMovingRight(bool isBallMovingRight);
	void SetIsBallMovingLeft(bool isBallMovingLeft);
	void SetIsBallMovingDown(bool isBallMovingDown);
	void SetIsBallMovingUp(bool isBallMovingUp);
	void SetIsBallMoving(bool isBallMoving);

	bool GetIsBallMovingRight();
	bool GetIsBallMovingLeft();
	bool GetIsBallMovingDown();
	bool GetIsBallMovingUp();
	bool GetIsBallMoving();

private:
	int const m_ballWidth = 35;
	int const m_ballHeight = 35;

	int m_ballX;
	int m_ballY;
	int m_speed = 5;

	bool isBallMovingRight = false;
	bool isBallMovingLeft = false;
	bool isBallMovingDown = false;
	bool isBallMovingUp = false;
	bool isBallMoving = false;
};

