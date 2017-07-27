#pragma once
#include "GameObject.h"

class Ball :
	public GameObject
{
protected:
	friend class Computer;
	float speedX;
	float speedY;
	int directionX;
	int directionY;
	bool affected;
	int lastCollisionID;

	float addedSpd;

public:
	Ball(void);
	~Ball(void);

	void Render();
	void Update();
	void Collided(int otherID);

	int GetDirX() {return directionX;}
	int GetDirY() {return directionY;}

	void SetDirY(int dirY) {Ball::directionY = dirY;}

	float GetSpeedX() {return speedX;}
	void SetSpeedX(float spdX) {Ball::speedX = spdX;}

	float GetSpeedY() {return speedY;}
	void SetSpeedY(float spdY) {Ball::speedY = spdY;}

	float GetAddedSpd() {return addedSpd;}
	void SetAddedSpd(float addSpd) {Ball::addedSpd = addSpd;}

	void Affect() {affected = true;}
	void RemoveEffect();
	bool IsAffected() {return affected;}
};

