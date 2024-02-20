#pragma once
class BallHolder
{
public:
	void SetPosition(int x, int y);
	int GetBallHolderWidth() const;
	int GetBallHolderHeight() const;
	int GetBallHolderX() const;
	int GetBallHolderY() const;

private:
	int const m_ballHolderWidth = 120;
	int const m_ballHolderHeight = 20;

	int m_ballHolderX;
	int m_ballHolderY;
};

