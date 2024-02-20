#pragma once

class Ball
{
public:
	void SetPosition(int x, int y);
	int GetBallWidth() const;
	int GetBallHeight() const;
	int GetBallX() const;
	int GetBallY() const;

private:
	int const m_ballWidth = 35;
	int const m_ballHeight = 35;

	int m_ballX = 0;
	int m_ballY = 0;

};

