#include "Ball.h"
#include "TextureManager.h"

void Ball::SetPosition(int x, int y)
{
	m_ballX = x;
	m_ballY = y;
}

int Ball::GetSpeed() const
{
	return m_speed;
}

int Ball::GetBallWidth() const
{
	return m_ballWidth;
}

int Ball::GetBallHeight() const
{
	return m_ballHeight;
}

int Ball::GetBallX() const
{
	return m_ballX;
}

int Ball::GetBallY() const
{
	return m_ballY;
}



