#ifndef PLAYER_H
#define PLAYER_H
#include "allegro5\allegro.h"
#include <iostream>
class Player
{
public:
	Player();
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
private:
	int width;
	int height;
	float x;
	float y;
	ALLEGRO_BITMAP *player;
};
#endif
