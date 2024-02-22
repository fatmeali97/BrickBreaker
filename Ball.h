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

private:
	int const m_ballWidth = 35;
	int const m_ballHeight = 35;

	int m_ballX;
	int m_ballY;
	int m_speed = 5;
};

