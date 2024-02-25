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
	this->m_isBallMovingRight = isBallMovingRight;
}

void Ball::SetIsBallMovingLeft(bool isBallMovingLeft)
{
	this->m_isBallMovingLeft = isBallMovingLeft;
}

void Ball::SetIsBallMovingDown(bool isBallMovingDown)
{
	this->m_isBallMovingDown = isBallMovingDown;
}

void Ball::SetIsBallMovingUp(bool isBallMovingUp)
{
	this->m_isBallMovingUp = isBallMovingUp;
}

void Ball::SetIsBallMoving(bool isBallMoving)
{
	this->m_isBallMoving = isBallMoving;
}

bool Ball::GetIsBallMovingRight()
{
	return m_isBallMovingRight;
}

bool Ball::GetIsBallMovingLeft()
{
	return m_isBallMovingLeft;
}

bool Ball::GetIsBallMovingDown()
{
	return m_isBallMovingDown;
}

bool Ball::GetIsBallMovingUp()
{
	return m_isBallMovingUp;
}

bool Ball::GetIsBallMoving()
{
	return m_isBallMoving;
}

void Ball::Draw(SDL_Renderer* ren)
{
	TextureManager::Instance()->DrawTexture("Ball",
		{ GetBallX(), GetBallY(), GetBallWidth(), GetBallHeight() },
		ren);
}



