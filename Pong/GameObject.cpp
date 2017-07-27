#include "GameObject.h"


GameObject::GameObject(int x, int y, int boundX, int boundY, int ID)
	:ID(ID),x(x),y(y),boundX(boundX),boundY(boundY)
{
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font("ARIAL.ttf", 18, 0);
}


GameObject::~GameObject(void)
{
}


void GameObject::Render(void)
{
}


void GameObject::Update(void)
{
}


bool GameObject::CheckCollisions(GameObject *otherObject)
{
	int oX = otherObject->GetX();
	int oY = otherObject->GetY();
	int obX = otherObject->GetBoundX();
	int obY = otherObject->GetBoundY();

	if(x + boundX > oX - obX && x - boundX < oX + obX &&
		y + boundY > oY - obY && y - boundY < oY + obY)
		return true;
	else
		return false;
}


void GameObject::Collided(int otherID)
{
}
