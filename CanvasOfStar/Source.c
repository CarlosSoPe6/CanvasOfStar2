#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "LinkedList.h"
#include "Constants.h"

void update(BitMapsList elem);
void render(BitMapsList elem);
bool intersects(BitMapsList elemA, BitMapsList elemB);

enum MYKEYS {
	KEY_W, KEY_A, KEY_S, KEY_D
};

int main(int argc, char **argv) {

	//BitMapsList * elementA;
	//BitMapsList * elementA_Connector;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//create player
	BitMap player;
	player.x = SCREEN_W / 2.0 - IMAGE_SIZE / 2.0;
	player.y = SCREEN_H / 2.0 - IMAGE_SIZE / 2.0;;

	//elementA = (BitMapsList *)malloc(sizeof(BitMapsList));

	bool key[4] = { false, false, false, false };
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

	display = al_create_display(800, 600);

	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	player.image = al_load_bitmap("image2.png");
	player.size = 32;

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

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_W] && player.y >= 4.0) {
				player.y -= 4.0;
			}

			if (key[KEY_S] && player.y <= SCREEN_H - IMAGE_SIZE - 4.0) {
				player.y += 4.0;
			}

			if (key[KEY_A] && player.x >= 4.0) {
				player.x -= 4.0;
			}

			if (key[KEY_D] && player.x <= SCREEN_W - IMAGE_SIZE - 4.0) {
				player.x += 4.0;
			}

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
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

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
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

void update(BitMapsList elem)
{

}

void render(BitMapsList elem)
{

}

bool intersects(BitMapsList elemA, BitMapsList elemB)
{
	return false;
}