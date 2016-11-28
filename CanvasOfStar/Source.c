#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "LinkedList.h"
#include "Constants.h"

ALLEGRO_SAMPLE *playerShoot;
ALLEGRO_SAMPLE *playerDie;
ALLEGRO_SAMPLE *enemyShoot;
ALLEGRO_SAMPLE *enemyDie;

BitMap player;

int handleKeyEvents(ALLEGRO_EVENT ev, const bool * key);
void handleCollitions();

int main(int argc, char **argv) {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_BITMAP *mainImage = NULL;
	ALLEGRO_BITMAP *backgroundImage = NULL;

	//game states and helpers
	int gameStatus = LV1;
	//FOR DEBUG

	int evtHandlderResult = 0;
	//init player
	player.size_x = IMAGE_SIZE_WIDTH * 2;
	player.size_y = IMAGE_SIZE_HEIGHT * 2;
	player.speed_x = SPEED_LIMIT;
	player.speed_y = SPEED_LIMIT;
	player.x = SCREEN_W / 2.0 - player.size_x / 2.0;
	player.y = SCREEN_H / 2.0 - player.size_y / 2.0;
	
	bool key[5] = { false, false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	if (!al_install_audio()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}

	if (!al_reserve_samples(1)) {
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

	playerShoot = al_load_sample("sounds/las0.wav");
	enemyShoot = al_load_sample("sounds/las1.mp3");
	playerDie = al_load_sample("sounds/exp0.mp3");
	enemyDie = al_load_sample("sounds/exp1.mp3");

	if (!playerShoot && !enemyShoot && !playerDie && !enemyDie) {
	printf("Audio clip not loaded!\n");
	return -1;
	}

	display = al_create_display(800, 600);

	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	al_set_window_title(display, "Canvas of Star");
	
	mainImage = al_load_bitmap("images/SPRITES.png");

	player.image = al_create_sub_bitmap(mainImage, 128, 0, player.size_x, player.size_y);

	if (!player.image) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_bitmap(player.image);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return 0;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(player.image);
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

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (gameStatus == HOME)
		{
			evtHandlderResult = 0;
			switch (evtHandlderResult)
			{
			case -1:
				redraw = true;
				break;
			case 0:
				doexit = true;
				continue;
				break;
			case 1:
				doexit = true;
				break;
			case 2:
				break;
			}
			handleCollitions();
		}
		else if (gameStatus == INSTRUCTIONS)
		{
			evtHandlderResult = 0;
			switch (evtHandlderResult)
			{
			case -1:
				redraw = true;
				break;
			case 0:
				doexit = true;
				continue;
				break;
			case 1:
				doexit = true;
				break;
			case 2:
				break;
			}
		}
		else if (gameStatus == LV1)
		{
			evtHandlderResult = handleKeyEvents(ev, key);

			if (evtHandlderResult < 0) {
				redraw = true;
			}
			else if (evtHandlderResult == 0) {
				doexit = true;
				continue;
			}

			handleCollitions();
		}
		else if (gameStatus == LV2)
		{
			evtHandlderResult = handleKeyEvents(ev, key);

			if (evtHandlderResult < 0) {
				redraw = true;
			}
			else if (evtHandlderResult == 0) {
				doexit = true;
				continue;
			}

			handleCollitions();
		}
		else if (gameStatus == LV3)
		{
			evtHandlderResult = handleKeyEvents(ev, key);

			if (evtHandlderResult < 0) {
				redraw = true;
			}
			else if (evtHandlderResult == 0) {
				doexit = true;
				continue;
			}

			handleCollitions();
		}
		else if (gameStatus == NO_LIFE)
		{

		}
		else if (gameStatus == WON)
		{

		}

		if (redraw && al_is_event_queue_empty(event_queue) && (gameStatus >= LV1 && gameStatus <= LV3)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(player.image, player.x, player.y, 0);

			al_flip_display();
		}
	}

	al_destroy_bitmap(player.image);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}

int handleKeyEvents(ALLEGRO_EVENT ev, bool * key)
{
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		if (key[KEY_W] && player.y > 0) {
			player.y -= player.speed_y;
		}

		if (key[KEY_S] && player.y < SCREEN_H - player.size_y) {
			player.y += player.speed_y;
		}

		if (key[KEY_A] && player.x > 0) {
			player.x -= player.speed_x;
		}

		if (key[KEY_D] && player.x < SCREEN_W - player.size_x) {
			player.x += player.speed_x;
		}

		if (key[KEY_SPACE]) {
			//perform shoot
			al_play_sample(playerShoot, SAMPLE_GAIN, SAMPLE_PAN, SAMPLE_SPEED, SAMPLE_PLAY_ONCE, NULL);
		}

		return -1;
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		return 0;
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			key[KEY_W] = true;
			break;

		case ALLEGRO_KEY_S:
			key[KEY_S] = true;
			break;

		case ALLEGRO_KEY_A:
			key[KEY_A] = true;
			break;

		case ALLEGRO_KEY_D:
			key[KEY_D] = true;
			break;

		case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = true;
			break;
		}


	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			key[KEY_W] = false;
			break;

		case ALLEGRO_KEY_S:
			key[KEY_S] = false;
			break;

		case ALLEGRO_KEY_A:
			key[KEY_A] = false;
			break;

		case ALLEGRO_KEY_D:
			key[KEY_D] = false;
			break;

		case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = false;
			break;

		case ALLEGRO_KEY_ESCAPE:
			return 0;
		}
	}
	return 2;
}

void handleCollitions()
{

}