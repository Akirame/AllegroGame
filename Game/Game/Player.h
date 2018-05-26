#ifndef PLAYER_H
#define PLAYER_H
#include "allegro5\allegro.h"
#include <iostream>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>

class Player
{
private:
	int width;
	int height;
	float x;
	float y;
	ALLEGRO_BITMAP* sprite = NULL;
public:	
	Player(int screenWidth, int screenHeight);
	~Player();
	void SetX(float _x);
	void SetY(float _y);
	float GetX();
	float GetY();
	float GetHeight();
	float GetWidht();
	ALLEGRO_BITMAP* GetBitmap();
	void Movement(ALLEGRO_EVENT ev);
	void Update(ALLEGRO_EVENT ev);

};
#endif
