#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "Player.h"
#include "Enemy.h"

bool bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int PLAYER_SIZE = 32;
const int ENEMY_SIZE = 32;

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;	
	Player* player;
	Enemy* enemy;

	bool redraw = true;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}
	if (!al_init_image_addon())
	{
		fprintf(stderr, "failed to initialize the image addon!\n");
		return -1;
	}
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	player = new Player(SCREEN_W, SCREEN_H);
	enemy = new Enemy(SCREEN_W, SCREEN_H);


	al_set_target_bitmap(player->GetBitmap());
	al_set_target_bitmap(enemy->GetBitmap());
			
	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(player->GetBitmap());
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			if (bounding_box_collision(player->GetX(), player->GetY(), player->GetWidht(), player->GetHeight(),
				enemy->GetX() , enemy->GetY(), enemy->GetWidht(), enemy->GetHeight()))
				break;
			enemy->Update(ev);
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			player->Update(ev);
		}
		

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(player->GetBitmap(), player->GetX(), player->GetY() , 0);
			al_draw_bitmap(enemy->GetBitmap(), enemy->GetX(), enemy->GetY(), 0);

			al_flip_display();
		}
	}

	delete player;
	delete enemy;
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
bool bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h)
{
	if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
		(b1_y > b2_y + b2_h - 1) || // is b1 under b2?
		(b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
		(b2_y > b1_y + b1_h - 1))   // is b2 under b1?
	{
		// no collision
		return false;
	}
	// collision
	return true;
}
