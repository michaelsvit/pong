#pragma once
#include "GameObject.h"
#include "Ball.h"
#include "Player.h"
#include <list>

class PowerUp :
	public GameObject
{
private:
	int type;
	enum TYPE{TWOBALLS, SPEEDUP, SPEEDDOWN, LENGTHEN, SHORTEN};
	std::list<GameObject *> objects;
	int powerupCount;
	int targetID;
	bool visible;
	bool offensive;

	void Render();
	void Update();
	void Collided(int otherID);

public:
	PowerUp(std::list<GameObject *> &objectsList);
	~PowerUp(void);

	void Affect();
	bool IsOffensive() {return offensive;}
	void LowerCount() {powerupCount--;}
	bool IsDone();
	bool IsVisible() {return visible;}
	int GetTargetID() {return targetID;}
};

