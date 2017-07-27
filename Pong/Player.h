#pragma once
#include "GameObject.h"
#include "Ball.h"

class Player :
	public GameObject
{
protected:
	int speedY;
	int directionY;
	Ball *ball;

public:
	Player(void);
	Player(Ball *ball);
	~Player(void);

	void Render();
	virtual void Update();

	void Collided(int otherID);

	void MoveUp() {directionY = -1;}
	void MoveDown() {directionY = 1;}
	void ResetAnimation() {directionY = 0;}

	void SetLength(int length) {Player::boundY = length / 2;}
	int GetLength() {return Player::boundY * 2;}
};

