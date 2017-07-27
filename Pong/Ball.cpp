#include "Ball.h"


Ball::Ball(void)
	:GameObject(WIDTH/2,HEIGHT/2,10,10,BALL),speedX(6),affected(false),lastCollisionID(-1),addedSpd(0)
{
	if(rand() % 2)
		directionX = 1;
	else
		directionX = -1;

	if(rand() % 2)
		directionY = 1;
	else
		directionY = -1;

	speedY = rand() % 6;
	if(speedY == 0)
		directionY = 0;
}


Ball::~Ball(void)
{
}


void Ball::Render()
{
	GameObject::Render();

	al_draw_circle(x, y, boundX, neonBlue, 2);
	al_draw_circle(x, y, boundX / 2, neonBlue, 2);
}


void Ball::Update()
{
	x += speedX * directionX;
	y += speedY * directionY;

	al_draw_textf(font, al_map_rgb(255,0,255), 20, 20, 0, "Ball X: %f Ball Y: %f Ball Speed: %f Ball Direction: %i Step Size: %i", x, y, speedY, directionY, (int)(speedY * directionY));

	if(x - boundX <= 0)
	{
		x = boundX;
		Collided(BORDER);
	}
	else if(x + boundX >= WIDTH)
	{
		x = WIDTH - boundX;
		Collided(BORDER);
	}

	if(y - boundY <= 0)
	{
		directionY = 1;
	}
	else if(y + boundY >= HEIGHT)
	{
		directionY = -1;
	}
}


void Ball::Collided(int otherID)
{
	if((otherID == PLAYER || otherID == COMPUTER) && lastCollisionID != otherID)
	{
		directionX *= -1;
		if(IsAffected())
			RemoveEffect();
		lastCollisionID = otherID;
	}
}


void Ball::RemoveEffect()
{
	speedY = speedY + ((6 - speedX)/speedX)*speedY;
	speedX = 6;

	affected = false;
}
