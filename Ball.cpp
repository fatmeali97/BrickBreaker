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

void Ball::SetIsBallMovingRight(bool isBallMovingRight)
{
	this->isBallMovingRight = isBallMovingRight;
}

void Ball::SetIsBallMovingLeft(bool isBallMovingLeft)
{
	this->isBallMovingLeft = isBallMovingLeft;
}

void Ball::SetIsBallMovingDown(bool isBallMovingDown)
{
	this->isBallMovingDown = isBallMovingDown;
}

void Ball::SetIsBallMovingUp(bool isBallMovingUp)
{
	this->isBallMovingUp = isBallMovingUp;
}

void Ball::SetIsBallMoving(bool isBallMoving)
{
	this->isBallMoving = isBallMoving;
}

bool Ball::GetIsBallMovingRight()
{
	return isBallMovingRight;
}

bool Ball::GetIsBallMovingLeft()
{
	return isBallMovingLeft;
}

bool Ball::GetIsBallMovingDown()
{
	return isBallMovingDown;
}

bool Ball::GetIsBallMovingUp()
{
	return isBallMovingUp;
}

bool Ball::GetIsBallMoving()
{
	return isBallMoving;
}



