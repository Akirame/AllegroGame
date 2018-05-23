#include "Player.h"

Player::Player()
{
	width = 32;
	height = 32;
	x = 10;
	y = 10;
	player = al_load_bitmap("assets/player.png");
	if (!player)
		fprintf(stderr, "failed to create player bitmap!\n");

}
Player::Player(int screenWidth, int screenHeight)
{
	width = 32;
	height = 32;
	x = screenWidth / 2 - width / 2;
	y = screenHeight / 2 - height / 2;
	player = al_load_bitmap("assets/player.png");
	if (!player)
		fprintf(stderr, "failed to create player bitmap!\n");
}


Player::~Player()
{
	delete player;
}
void Player::Movement(ALLEGRO_EVENT ev)
{	
		if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
			y -= 10;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
			y += 10;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
			x -= 10;
		else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			x += 10;	
}
void Player::SetX(float _x)
{
	x += _x;
}
void Player::SetY(float _y)
{
	y += _y;
}
float Player::GetX()
{
	return x;
}
float Player::GetY()
{
	return y;
}
float Player::GetHeight()
{
	return height;
}
float Player::GetWidht()
{
	return width;
}
ALLEGRO_BITMAP* Player::GetBitmap()
{
	return player;
}