#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Globals.h"

class GameObject
{
public:
	GameObject(int x, int y, int boundX, int boundY, int ID);
	virtual ~GameObject(void);

	virtual void Render();
	virtual void Update();

	int GetX() {return x;}
	void SetX(float X) {GameObject::x = x;}

	int GetY() {return y;}
	void SetY(float y) {GameObject::y = y;}

	int GetBoundX() {return boundX;}
	int GetBoundY() {return boundY;}

	int GetID() {return ID;}

	bool CheckCollisions(GameObject *otherObject);
	virtual void Collided(int otherID);

protected:
	int ID;
	float x;
	float y;
	int boundX;
	int boundY;
	ALLEGRO_FONT *font;
};

