#include "PowerUp.h"


PowerUp::PowerUp(std::list<GameObject *> &objectsList)
	:GameObject(WIDTH / 2, HEIGHT / 2, 20, 20, POWERUP), objects(objectsList), targetID(-1), visible(true), offensive(false)
{
	y = rand() % (HEIGHT - 40) + 20;
	type = rand() % 5;
	//type = SPEEDDOWN;
	powerupCount = 4;
}


PowerUp::~PowerUp(void)
{
}


void PowerUp::Render(void)
{
	if(visible)
	{
		GameObject::Render();

		al_draw_rectangle(x - boundX, y - boundY, x + boundX, y + boundY, neonBlue, 3);

		switch(type)
		{
		case TWOBALLS:
			al_draw_text(font,al_map_rgb(0,255,255),x,y,ALLEGRO_ALIGN_CENTER,"Two Balls");
			break;
		case SPEEDUP:
			al_draw_text(font,al_map_rgb(0,255,255),x,y,ALLEGRO_ALIGN_CENTER,"Speed Up");
			break;
		case SPEEDDOWN:
			al_draw_text(font,al_map_rgb(0,255,255),x,y,ALLEGRO_ALIGN_CENTER,"Speed Down");
			break;
		case LENGTHEN:
			al_draw_text(font,al_map_rgb(0,255,255),x,y,ALLEGRO_ALIGN_CENTER,"Lengthen");
			break;
		case SHORTEN:
			al_draw_text(font,al_map_rgb(0,255,255),x,y,ALLEGRO_ALIGN_CENTER,"Shorten");
			break;
		}
	}
}


void PowerUp::Update(void)
{
	GameObject::Update();
}


void PowerUp::Collided(int otherID)
{
	if(otherID == BALL && visible && collisions[ID] == false)
	{
		for(auto iter:objects)
		{
			if(iter->GetID() == BALL)
			{
				if(((Ball *)iter)->GetDirX() == 1)
				{
					switch(type)
					{
					case TWOBALLS:
						targetID = COMPUTER;
						offensive = true;
						break;
					case SPEEDUP:
						targetID = COMPUTER;
						offensive = true;
						break;
					case SPEEDDOWN:
						targetID = PLAYER;
						break;
					case LENGTHEN:
						targetID = PLAYER;
						break;
					case SHORTEN:
						targetID = COMPUTER;
						offensive = true;
						break;
					}
				}
				else
				{
					switch(type)
					{
					case TWOBALLS:
						targetID = PLAYER;
						offensive = true;
						break;
					case SPEEDUP:
						targetID = PLAYER;
						offensive = true;
						break;
					case SPEEDDOWN:
						targetID = COMPUTER;
						break;
					case LENGTHEN:
						targetID = COMPUTER;
						break;
					case SHORTEN:
						targetID = PLAYER;
						offensive = true;
						break;
					}
				}
			}
		}

		if(type != SPEEDDOWN)
			Affect();
		visible = false;

		collisions[ID] = true;
	}
}


void PowerUp::Affect()
{
	switch(type)
		{
		case TWOBALLS:
				break;
		case SPEEDUP:
			for(auto iter:objects)
			{
				if(iter->GetID() == BALL)
				{
					if(!((Ball *)iter)->IsAffected())
					{
						((Ball *)iter)->SetSpeedY(((Ball *)iter)->GetSpeedY() + (4 / ((Ball *)iter)->GetSpeedX()) * ((Ball *)iter)->GetSpeedY());
						((Ball *)iter)->SetSpeedX(((Ball *)iter)->GetSpeedX() + 4);
						((Ball *)iter)->Affect();
					}
				}
			}
			break;
		case SPEEDDOWN:
			for(auto iter:objects)
			{
				if(iter->GetID() == BALL)
				{
					if(!((Ball *)iter)->IsAffected())
					{
						((Ball *)iter)->SetSpeedY(((Ball *)iter)->GetSpeedY() - (3 / ((Ball *)iter)->GetSpeedX()) * ((Ball *)iter)->GetSpeedY());
						((Ball *)iter)->SetSpeedX(((Ball *)iter)->GetSpeedX() - 3);
						((Ball *)iter)->Affect();
					}
				}
			}
			break;
		case LENGTHEN:
				for(auto iter:objects)
				{
					if(iter->GetID() == targetID)
							((Player *)iter)->SetLength(150);
				}
			break;
		case SHORTEN:
				for(auto iter:objects)
				{
					if(iter->GetID() == targetID)
							((Player *)iter)->SetLength(50);
				}
			break;
		}
}


bool PowerUp::IsDone()
{
	if(powerupCount == 0)
	{
		switch(type)
		{
		case TWOBALLS:
			break;
		case LENGTHEN:
		case SHORTEN:
			for(auto iter:objects)
				if(iter->GetID() == targetID)
					((Player *)iter)->SetLength(100);
			break;
		}

		return true;
	}
	else
	{
		return false;
	}
}
