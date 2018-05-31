#include "Enemy.h"

Enemy::Enemy(int screenWidth, int screenHeight)
{
	width = 32;
	height = 32;
	speed = 10;
	x = screenWidth / 4 - width / 2;
	y = screenHeight / 4 - height / 2;
	sprite = al_load_bitmap("assets/enemy.png");
	if (!sprite)
		fprintf(stderr, "failed to create enemy bitmap!\n");
}

Enemy::~Enemy()
{	
	al_destroy_bitmap(sprite);
}
void Enemy::Update(ALLEGRO_EVENT ev)
{
	Movement(ev);
}
// si choca contra el costado derecho vuelve
void Enemy::Movement(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		if (x < 0)
			speed *= -1;
		else if (x + width > 640)
			speed *= -1;
		x += speed;
	}
}
void Enemy::SetX(float _x)
{
	x += _x;
}
void Enemy::SetY(float _y)
{
	y += _y;
}
float Enemy::GetX()
{
	return x;
}
float Enemy::GetY()
{
	return y;
}
float Enemy::GetHeight()
{
	return height;
}
float Enemy::GetWidht()
{
	return width;
}
float Enemy::GetSpeed()
{
	return speed;
}
ALLEGRO_BITMAP* Enemy::GetBitmap()
{
	return sprite;
}
