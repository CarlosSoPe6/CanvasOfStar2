#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

typedef struct square
{
	int a;
} Square;

typedef struct bitMaps
{
	int size;
	float x;
	float y;
	float speed;
	ALLEGRO_BITMAP *image;
} BitMaps;

typedef struct list
{
	BitMaps bitMap;
	BitMaps *next;
} BitMapsList;

/**
 * param: BitMapsList elem
 * summary: Deletes a element from a list
 */
void removeBitMapsListElement(BitMapsList elem);
void addBitMapsListElemet(const int size,
	float x,
	float y,
	float speed,
	ALLEGRO_BITMAP * image,
	BitMapsList list);
void getBitMapsListElement();
void update(BitMapsList elem);
void render(BitMapsList elem);
bool intersects(BitMapsList elemA, BitMapsList elemB);
//int getBounds(BitMapsList elem);

const float FPS = 60.0;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int IMAGE_SIZE = 32;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv) {

	BitMapsList * elementA;
	BitMapsList * elementA_Connector;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *image;

	elementA = (BitMapsList *)malloc(sizeof(BitMapsList));

	float image_x = SCREEN_W / 2.0 - IMAGE_SIZE / 2.0;
	float image_y = SCREEN_H / 2.0 - IMAGE_SIZE / 2.0;

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

	image = al_load_bitmap("image2.png");

	if (!image) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_bitmap(image);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return 0;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(image);
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
			if (key[KEY_UP] && image_y >= 4.0) {
				image_y -= 4.0;
			}

			if (key[KEY_DOWN] && image_y <= SCREEN_H - IMAGE_SIZE - 4.0) {
				image_y += 4.0;
			}

			if (key[KEY_LEFT] && image_x >= 4.0) {
				image_x -= 4.0;
			}

			if (key[KEY_RIGHT] && image_x <= SCREEN_W - IMAGE_SIZE - 4.0) {
				image_x += 4.0;
			}

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(image, image_x, image_y, 0);

			al_flip_display();
		}
	}

	al_destroy_bitmap(image);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}

void removeBitMapsListElement(BitMapsList elem)
{

}

void addBitMapsListElemet(const int size, float x, float y, float speed, ALLEGRO_BITMAP * image, BitMapsList list)
{
	
}

void getBitMapsListElement()
{

}

void update(BitMapsList elem)
{

}

void render(BitMapsList elem)
{

}

bool intersects(BitMapsList elemA, BitMapsList elemB)
{

}