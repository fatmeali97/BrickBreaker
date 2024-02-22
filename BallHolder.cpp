#include "BallHolder.h"

void BallHolder::SetPosition(int x, int y)
{
	m_ballHolderX = x;
	m_ballHolderY = y;
}

int BallHolder::GetBallHolderWidth() const
{
	return m_ballHolderWidth;
}

int BallHolder::GetBallHolderHeight() const
{
	return m_ballHolderHeight;
}

int BallHolder::GetBallHolderX() const
{
	return m_ballHolderX;
}

int BallHolder::GetBallHolderY() const
{
	return m_ballHolderY;
}

void BallHolder::SetBallHolderX(int x)
{
	m_ballHolderX = x;
}

int BallHolder::GetSpeed()
{
	return m_speed;
}