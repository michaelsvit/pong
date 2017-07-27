#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <list>

#include "Globals.h"
#include "GameObject.h"
#include "Player.h"
#include "Ball.h"
#include "Computer.h"
#include "PowerUp.h"


//Globals
std::list<GameObject *> objects;
std::map<int, bool> collisions;
Player *player = nullptr;
Ball *ball = nullptr;
Computer *computer = nullptr;
PowerUp *powerup = nullptr;

int main(int argc, char *argv[])
{
	//=============================================
	//Shell Variables
	//=============================================

	bool done = false;
	bool create = true;
	bool render = true;
	const int FPS = 60;
	int timerCount = 0;
	int randTime = 0;

	enum KEYS{UP,DOWN};
	bool keys[] = {false, false};

	//=============================================
	//Allegro Variables
	//=============================================
	
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
	ALLEGRO_TIMER *timer = nullptr;
	ALLEGRO_FONT *font = nullptr;

	//=============================================
	//Allegro Initialize Functions
	//=============================================

	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);
	if(!display)
		return -1;

	event_queue = al_create_event_queue();

	timer = al_create_timer(1.0/FPS);

	srand(time(NULL));

	randTime = (rand() % 6 - 3) * FPS;

	//=============================================
	//Project Variables
	//=============================================

	ball = new Ball;
	player = new Player(ball);
	computer = new Computer(ball);

	//=============================================
	//Addon Install
	//=============================================

	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//=============================================
	//Project Initialize
	//=============================================
	
	objects.push_back(ball);
	objects.push_back(player);
	collisions[PLAYER] = false;
	objects.push_back(computer);
	collisions[COMPUTER] = false;

	font = al_load_ttf_font("ARIAL.ttf", 18, 0);

	//=============================================
	//Timer And Event Sources
	//=============================================

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_start_timer(timer);

	//=============================================
	//Game Loop
	//=============================================
	
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

	//=============================================
	//Input Handling
	//=============================================

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

	//=============================================
	//Game Update
	//=============================================

		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			

			if(keys[UP])
				player->MoveUp();
			else if(keys[DOWN])
				player->MoveDown();
			else
				player->ResetAnimation();


			for(auto iter:objects)
				iter->Update();


			for(auto iter1 = objects.begin(); iter1 != objects.end(); iter1++)
			{
				for(auto iter2 = iter1; iter2 != objects.end(); iter2++)
				{
					if((*iter1)->CheckCollisions(*iter2))
					{
						(*iter1)->Collided((*iter2)->GetID());
						(*iter2)->Collided((*iter1)->GetID());

						if(((*iter1)->GetID() == BALL && (*iter2)->GetID() == PLAYER) ||
							((*iter2)->GetID() == BALL && (*iter1)->GetID() == PLAYER))
						{
							for(auto iter:objects)
							{
								if(iter->GetID() == POWERUP)
								{
									if(!((PowerUp *)iter)->IsVisible())
									{
										if(((PowerUp *)iter)->IsOffensive())
										{
											if(((PowerUp *)iter)->GetTargetID() == PLAYER)
											{
												((PowerUp *)iter)->LowerCount();
											}
											else
											{
												((PowerUp *)iter)->Affect();
											}
										}
										else
										{
											if(((PowerUp *)iter)->GetTargetID() == COMPUTER)
											{
												((PowerUp *)iter)->Affect();
												((PowerUp *)iter)->LowerCount();
											}
										}
									}
								}
							}

							computer->CalcComplex(ball->GetAddedSpd() / 2.5);
							computer->Recalc();
							computer->ResetTimer();
						}
						else if(((*iter1)->GetID() == BALL && (*iter2)->GetID() == COMPUTER) ||
							((*iter2)->GetID() == BALL && (*iter1)->GetID() == COMPUTER))
						{
							for(auto iter:objects)
							{
								if(iter->GetID() == POWERUP)
								{
									if(!((PowerUp *)iter)->IsVisible())
									{
										if(((PowerUp *)iter)->IsOffensive())
										{
											if(((PowerUp *)iter)->GetTargetID() == COMPUTER)
											{
												((PowerUp *)iter)->LowerCount();
											}
											else
											{
												((PowerUp *)iter)->Affect();
											}
										}
										else
										{
											if(((PowerUp *)iter)->GetTargetID() == PLAYER)
											{
												((PowerUp *)iter)->Affect();
												((PowerUp *)iter)->LowerCount();
											}
										}
									}
								}
							}
						}
					}
				}
			}

			for(auto iter = objects.begin(); iter != objects.end(); iter++)
			{
				if((*iter)->GetID() == POWERUP)
				{
					if(((PowerUp *)(*iter))->IsDone())
					{
						delete *iter;
						objects.erase(iter);
						break;
					}
				}
			}

			al_draw_textf(font,al_map_rgb(255,0,0),100,100,0,"timerCount: %i, randTime: %i, al_get_timer_count: %i", timerCount, randTime, al_get_timer_count(timer));
			//if(timerCount + 5 * FPS + randTime == al_get_timer_count(timer))
			if(create)
			{
				create = false;
				objects.push_back(new PowerUp(objects));
				collisions[POWERUP] = false;
				timerCount = al_get_timer_count(timer);
				randTime = (rand() % 6 - 3) * FPS;
			}

			render = true;
		}

	//=============================================
	//Rendering
	//=============================================

		if(render && al_is_event_queue_empty(event_queue))
		{
			for(auto iter:objects)
				iter->Render();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
			render = false;
		}
	}

	//=============================================
	//Destroy Project Variables
	//=============================================

	for(auto iter:objects)
	{
		delete iter;
	}

	//Shell Variables
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);


	return 0;
}