#pragma once
#include "Player.h"

class Computer :
	public Player
{
private:
	bool recalc;
	ALLEGRO_TIMER *timer;
	int timerCount;
	int complex;
	int ballTargY;

	void CalcBallTarget(int dY, int wallHits);

public:
	Computer(Ball *ball);
	~Computer(void);

	void Update();
	void CalcComplex(int multiplier);
	void Recalc() {recalc = true;}

	//void SetDirY(int directionY) {Computer::directionY = directionY;}
	void ResetTimer() {timerCount = al_get_timer_count(timer);}
};

