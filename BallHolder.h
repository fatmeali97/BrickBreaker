#pragma once
class BallHolder
{
public:
	void SetPosition(int x, int y);
	void SetBallHolderX(int x);
	int GetBallHolderWidth() const;
	int GetBallHolderHeight() const;
	int GetBallHolderX() const;
	int GetBallHolderY() const;
	int GetSpeed();

private:
	int const m_ballHolderWidth = 250;
	int const m_ballHolderHeight = 20;
	int m_ballHolderX;
	int m_ballHolderY;
	int m_speed = 10;
};

