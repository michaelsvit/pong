#include "Computer.h"


Computer::Computer(Ball *ball)
	:timer(al_create_timer(0.1)),complex(0)
{
	ID = COMPUTER;
	Computer::ball = ball;

	x = WIDTH - 25;
	y = HEIGHT / 2;

	al_start_timer(timer);

	if(ball->directionX == 1)
	{
		ResetTimer();
		CalcComplex(0);
		recalc = true;
	}
	else
		recalc = false;
}


Computer::~Computer(void)
{
	al_destroy_timer(timer);
}


void Computer::Update()
{
	if(recalc)
	{
		int timerCount2 = al_get_timer_count(timer);
		al_draw_textf(font, al_map_rgb(255,0,255),20,50,0,"Complex: %i CurrentTime: %i SavedTime: %i", complex, timerCount2, timerCount);
		if(timerCount2 >= timerCount + 5)
		{
			directionY = ball->directionY;
			if(timerCount2 >= timerCount + 5 + complex)
			{
				if(ballTargY > y)
				{
					if(y + speedY >= ballTargY)
					{
						directionY = 0;
						timerCount = al_get_timer_count(timer);
						recalc = false;
					}
					else
						directionY = 1;
				}
				else if(ballTargY < y)
				{
					if(y - speedY <= ballTargY)
					{
						directionY = 0;
						timerCount = al_get_timer_count(timer);
						recalc = false;
					}
					else
						directionY = -1;
				}
				else
				{
					directionY = 0;
					timerCount = al_get_timer_count(timer);
					recalc = false;
				}
			}
		}
	}

	Player::Update();
}


void Computer::CalcComplex(int multiplier)
{
	double cyclesX;
	int dY;
	int wallHits;

	cyclesX = (Computer::x - Computer::boundX - ball->x + ball->boundX) / ball->speedX;
	dY = ball->speedY * cyclesX;
	if(ball->directionY == 1)
		wallHits = (dY + ball->y) / HEIGHT;
	else
		wallHits = (dY + (HEIGHT - ball->y)) / HEIGHT;
	CalcBallTarget(dY, wallHits);
	complex = wallHits * 4;

	//ballTargY += rand() % (boundY * 2 + 10 + complex * (4 + multiplier)) - boundY;
}


void Computer::CalcBallTarget(int dY, int wallHits)
{
	if(wallHits == 0)
	{
		ballTargY = ball->y + dY * ball->directionY;
	}
	else if(ball->directionY == 1)
	{
		if(wallHits % 2)
			ballTargY = HEIGHT - (int)(dY - (HEIGHT - ball->y)) % HEIGHT;
		else
			ballTargY = (int)(dY - (HEIGHT - ball->y)) % HEIGHT;
	}
	else if(ball->directionY == -1)
	{
		if(wallHits % 2)
			ballTargY = (int)(dY - ball->y) % HEIGHT;
		else
			ballTargY = HEIGHT - ((int)(dY - ball->y) % HEIGHT);
	}
}