#pragma once
class BallHolder
{
public:
	void SetPosition(int x, int y);
	int GetBallHolderWidth() const;
	int GetBallHolderHeight() const;
	int GetBallHolderX() const;
	int GetBallHolderY() const;
	void SetBallHolderX(int x);
	int GetSpeed();
private:
	int const m_ballHolderWidth = 250;
	int const m_ballHolderHeight = 20;

	int m_ballHolderX;
	int m_ballHolderY;
	int m_speed = 10;
};

