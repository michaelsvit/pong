#include "Player.h"


Player::Player()
	:GameObject(25, HEIGHT / 2, 5, 50, PLAYER),speedY(7),directionY(0),ball(nullptr)
{
}


Player::Player(Ball *ball)
	:GameObject(25, HEIGHT / 2, 5, HEIGHT / 2, PLAYER),speedY(7),directionY(0)
{
	Player::ball = ball;
}


Player::~Player(void)
{
}


void Player::Render()
{
	GameObject::Render();

	al_draw_rounded_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, 5, 5, neonBlue, 3);
}


void Player::Update()
{
	GameObject::Update();

	y += speedY * directionY;

	if(y - boundY < 0)
		y = boundY;
	else if(y + boundY > HEIGHT)
		y = HEIGHT - boundY;
}


void Player::Collided(int otherID)
{
	if(otherID == BALL && collisions[ID] == false)
	{
		float addSpeed;
		addSpeed = ((float)(ball->GetY() - Player::y) / Player::boundY) * 5;

		if(ball->GetY() > Player::y && ball->GetDirY() == 1)
			ball->SetSpeedY(ball->GetSpeedY() + addSpeed);
		else if(ball->GetY() > Player::y && ball->GetDirY() == -1)
		{
			float newSpeed = ball->GetSpeedY() - addSpeed;
			if(newSpeed > 0)
				ball->SetSpeedY(newSpeed);
			else if(newSpeed < 0)
			{
				ball->SetSpeedY(newSpeed * -1);
				ball->SetDirY(1);
			}
		}
		else if(ball->GetY() > Player::y && ball->GetDirY() == 0)
		{
			ball->SetSpeedY(addSpeed);
			ball->SetDirY(1);
		}
		else if(ball->GetY() < Player::y && ball->GetDirY() == -1)
			ball->SetSpeedY(ball->GetSpeedY() - addSpeed);
		else if(ball->GetY() < Player::y && ball->GetDirY() == 1)
		{
			float newSpeed = ball->GetSpeedY() + addSpeed;
			if(newSpeed > 0)
				ball->SetSpeedY(newSpeed);
			else if(newSpeed < 0)
			{
				ball->SetSpeedY(newSpeed * -1);
				ball->SetDirY(-1);
			}
		}
		else if(ball->GetY() < Player::y && ball->GetDirY() == 0)
		{
			ball->SetSpeedY(addSpeed * -1);
			ball->SetDirY(-1);
		}

		if(ball->GetSpeedY() == 0)
			ball->SetDirY(0);
		else if(ball->GetSpeedY() > 10)
			ball->SetSpeedY(10);

		if(ball->GetSpeedX() > 6)
			ball->SetSpeedX(6);

		ball->SetAddedSpd(addSpeed);

		collisions[ID] = true;
		if(ID == PLAYER)
			collisions[COMPUTER] = false;
		else if(ID == COMPUTER)
			collisions[PLAYER] = false;
	}
}