float backgroundX = 0.0;

#include <stdio.h>
#include <time.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "LinkedList.h"
#include "Constants.h"
#include "Physics.h"
#include "Intelligence.h"

ALLEGRO_DISPLAY *display;

ALLEGRO_SAMPLE *playerShoot;
ALLEGRO_SAMPLE *playerDie;
ALLEGRO_SAMPLE *enemyShoot;
ALLEGRO_SAMPLE *enemyDie;

ALLEGRO_BITMAP *shootA;
ALLEGRO_BITMAP *shootB;
ALLEGRO_BITMAP *shootC;//El de el jefe
ALLEGRO_BITMAP *enemyAImage = NULL;
ALLEGRO_BITMAP *enemyBImage = NULL;
ALLEGRO_BITMAP *enemyBulletImage = NULL;
ALLEGRO_BITMAP *Boss[3];

ALLEGRO_BITMAP *newNormal;
ALLEGRO_BITMAP *newHover;
ALLEGRO_BITMAP *insNormal;
ALLEGRO_BITMAP *insHover;


//background
ALLEGRO_BITMAP *background[3];

// List aux
EntityList *listTypeA;

EntityList *listTypeB;

Entity player;

int shootLock;
int gameStatus;

int enemySpawnCounter;

bool canShoot;
bool isBossSpawned;
bool mouseFlag;

int handleKeyEvents(ALLEGRO_EVENT ev, const bool * key);
void update();
void handlePlayerShoot();
void handleEnemyShoot(Entity enemy);
void spawnEnemies();

float  getBulletX(Entity element, int type);
float getBulletY(Entity element);

int main(int argc, char **argv) {
	
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_BITMAP *mainImage = NULL;
	ALLEGRO_BITMAP *mainButtons;

	float mx = 0.0;
	float my = 0.0;

	listTypeA = (EntityList*)malloc(sizeof(EntityList));
	listTypeB = (EntityList*)malloc(sizeof(EntityList));

	initializeEntityList(listTypeA);
	initializeEntityList(listTypeB);

	display = NULL;

	srand(time(NULL));

	//game states and helpers
	//FOR DEBUG
	gameStatus = HOME;
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
	bool clicked = false;

	canShoot = true;
	isBossSpawned = false;
	mouseFlag = false;

	shootLock = 0;
	enemySpawnCounter = 222;

	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
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

	al_reserve_samples(50);

	playerShoot = al_load_sample("sounds/las0.wav");
	enemyShoot = al_load_sample("sounds/las1.wav");
	playerDie = al_load_sample("sounds/exp0.wav");
	enemyDie = al_load_sample("sounds/exp1.wav");

	if (!playerShoot) {
		printf("Audio playerShoot clip not loaded!\n");
		return -1;
	}

	if (!enemyShoot) {
		printf("Audio enemyShoot clip not loaded!\n");
		return -1;
	}

	if (!playerDie) {
		printf("Audio playerDie clip not loaded!\n");
		return -1;
	}

	if (!enemyDie) {
		printf("Audio enemyDie clip not loaded!\n");
		return -1;
	}

	player.shoot = playerShoot;
	player.die = playerDie;

	display = al_create_display(SCREEN_W, SCREEN_H);

	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	al_set_window_title(display, "Canvas of Star");
	
	background[0] = al_load_bitmap("images/back_level1.bmp");
	background[1] = al_load_bitmap("images/back_level2.bmp");
	background[2] = al_load_bitmap("images/back_level3.bmp");

	mainImage = al_load_bitmap("images/SPRITES.png");

	mainButtons = al_load_bitmap("images/BUTTONS.jpg");
	newNormal = al_create_sub_bitmap(mainButtons, 0, 0, BUTTON_W, BUTTON_H);
	newHover = al_create_sub_bitmap(mainButtons, 0, 50, BUTTON_W, BUTTON_H);
	insNormal = al_create_sub_bitmap(mainButtons, 0, 100, BUTTON_W, BUTTON_H);
	insHover = al_create_sub_bitmap(mainButtons, 0, 150, BUTTON_W, BUTTON_H);

	enemyAImage = al_create_sub_bitmap(mainImage, 0, 0, IMAGE_SIZE_WIDTH * 2, IMAGE_SIZE_HEIGHT *2);
	enemyBImage = al_create_sub_bitmap(mainImage, 64, 0, IMAGE_SIZE_WIDTH * 2, IMAGE_SIZE_HEIGHT * 2);

	shootA = al_create_sub_bitmap(mainImage, 224, 0, BULLET_SMALL_SIZE_X, BULLET_SMALL_SIZE_Y);
	shootB = al_create_sub_bitmap(mainImage, 192, 32, BULLET_SMALL_SIZE_X, BULLET_SMALL_SIZE_Y);
	shootC = al_create_sub_bitmap(mainImage, 224, 32, BULLET_SMALL_SIZE_X, BULLET_SMALL_SIZE_Y);
	player.image = al_create_sub_bitmap(mainImage, 128, 0, player.size_x, player.size_y);
	Boss[0] = al_create_sub_bitmap(mainImage, 0, IMAGE_SIZE_HEIGHT * 2, IMAGE_SIZE_WIDTH * 3, IMAGE_SIZE_HEIGHT * 3);
	Boss[1] = al_create_sub_bitmap(mainImage, IMAGE_SIZE_WIDTH * 3, IMAGE_SIZE_HEIGHT * 2, IMAGE_SIZE_WIDTH * 3, IMAGE_SIZE_HEIGHT * 3);
	Boss[2] = al_create_sub_bitmap(mainImage, 0, IMAGE_SIZE_HEIGHT * 5, IMAGE_SIZE_WIDTH * 3, IMAGE_SIZE_HEIGHT * 3);

	if (!background[0]) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return 0;
	}

	if (!background[1]) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return 0;
	}

	if (!background[2]) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return 0;
	}

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
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) 
		{
			redraw = true;
		}

		if (ev.type == ALLEGRO_KEY_ESCAPE)
		{
			doexit = true;
			continue;
		}

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			doexit = true;
			continue;
		}

		if(gameStatus == NO_LIFE)
		{

		}

		if (gameStatus == HOME || gameStatus == INSTRUCTIONS)
		{

			if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
				ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
			{
				mx = ev.mouse.x;
				my = ev.mouse.y;
			}

			else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
			{
				clicked = true;
			}
		}
		else if (gameStatus == LV1 || gameStatus == LV2 || gameStatus == LV3)
		{
			if (!mouseFlag)
			{
				al_uninstall_mouse();
				mouseFlag = true;
			}
			evtHandlderResult = handleKeyEvents(ev, key);

			if (evtHandlderResult < 0) 
			{
				redraw = true;
			}
			else if (evtHandlderResult == 0) {
				doexit = true;
				continue;
			}

			update();
		}
		else if (gameStatus == NO_LIFE)
		{

		}
		else if (gameStatus == WON)
		{

		}

		if (gameStatus >= LV1 && gameStatus <= LV3) {

			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			
			al_draw_bitmap(background[gameStatus - 2], backgroundX, 0, 0);

			EntityList * temp = listTypeA;
			Entity * element;

			while (hasNext(temp))
			{
				temp = getNextEntityList(temp);
				element = temp->entity;
				
				al_draw_bitmap(element->image, element->x, element->y, 0);
			}

			temp = listTypeB;

			while (hasNext(temp))
			{
				temp = getNextEntityList(temp);
				element = temp->entity;

				al_draw_bitmap(element->image, element->x, element->y, 0);
			}

			al_draw_bitmap(player.image, player.x, player.y, 0);

			al_flip_display();
		}
		else if (redraw && gameStatus == HOME)
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (mx >= 100 && mx <= 100 + BUTTON_W && my >= 300 && my <= 300 + BUTTON_H)
			{
				al_draw_bitmap(newHover, 100, 300, 0);
				if (clicked)
				{
					gameStatus = LV1;
					clicked = false;
				}
			}
			else
			{
				al_draw_bitmap(newNormal, 100, 300, 0);
			}

			if (mx >= 900 && mx <= 900 + BUTTON_W && my >= 300 && my <= 300 + BUTTON_H)
			{
				al_draw_bitmap(insHover, 900, 300, 0);
				if (clicked)
				{
					gameStatus = INSTRUCTIONS;
					clicked = false;
				}
			}
			else
			{
				al_draw_bitmap(insNormal, 900, 300, 0);
			}
			
			al_flip_display();
		}
		else if (redraw && gameStatus == INSTRUCTIONS)
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (mx >= 100 && mx <= 100 + BUTTON_W && my >= 300 && my <= 300 + BUTTON_H)
			{
				al_draw_bitmap(newHover, 100, 300, 0);
				if (clicked)
				{
					gameStatus = LV1;
					clicked = false;
				}
			}
			else
			{
				al_draw_bitmap(newNormal, 100, 300, 0);
			}

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
	if (ev.type == ALLEGRO_EVENT_TIMER) 
	{
		if (key[KEY_W] && player.y > 0) 
		{
			player.y -= player.speed_y;
		}

		if (key[KEY_S] && player.y < SCREEN_H - player.size_y) 
		{
			player.y += player.speed_y;
		}

		if (key[KEY_A] && player.x > 0) 
		{
			player.x -= player.speed_x;
		}

		if (key[KEY_D] && player.x < SCREEN_W - player.size_x) 
		{
			player.x += player.speed_x;
		}

		if (key[KEY_SPACE]) 
		{
			//perform shoot
			handlePlayerShoot();
		}

		return -1;
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
	{
		return 0;
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
	{
		switch (ev.keyboard.keycode) 
		{
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
	else if (ev.type == ALLEGRO_EVENT_KEY_UP) 
	{
		switch (ev.keyboard.keycode)
		{
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
		}
	}
	return 2;
}


void update()
{
	bool helper = true;
	EntityList * tempA = listTypeA;
	Entity * elementA;
	EntityList * tempB = listTypeB;
	Entity * elementB;

	enemySpawnCounter++;

	shootLock++;
	if (shootLock > SHOOT_LOCK) {
		canShoot = true;
		shootLock = 0;
	}

	if (!isBossSpawned)
	{
		if (enemySpawnCounter % 450 == 0)
		{
			spawnEnemies();
			spawnEnemies();
			spawnEnemies();
			enemySpawnCounter = 0;
		}

		if (backgroundX >= -(SCREEN_W * 2)) {
			backgroundX = backgroundX - .9;
		}
		else
		{
			isBossSpawned = true;
			//spawn boss;
			EntityList *tempBoss = listTypeB;
			Entity *bossEnt = (Entity*)malloc(sizeof(Entity));
			addEntityListElement(
				IMAGE_SIZE_WIDTH * 3,
				IMAGE_SIZE_HEIGHT * 3,
				SCREEN_W - (IMAGE_SIZE_WIDTH * 3),
				(SCREEN_H / 2) - ((IMAGE_SIZE_HEIGHT * 3) / 2),
				0,
				3,
				MAIN_DAMAGE,
				BOSS_LIFE,
				BIG_BOSS,
				Boss[gameStatus - 2],
				enemyShoot,
				enemyDie,
				bossEnt,
				tempBoss);
		}
	}

	if (hasNext(tempA))
	{
		tempA = getNextEntityList(tempA);
		elementA = tempA->entity;
	}
	else
	{
		elementA = &player;
	}

	setFlagEnabled(true, listTypeB);

	while (helper)
	 {
		helper = false;
		if ((elementA->x < (SCREEN_W + 6) && (elementA->x + elementA->size_x) > -6)
			&& (elementA->y < (SCREEN_H + 6) && (elementA->y + elementA->size_y) > -6))
		{
			if (elementA->type != PLAYER)
			{
				elementA->x = elementA->x + elementA->speed_x;
				elementA->y = elementA->y + elementA->speed_y;
			}

			while (hasNext(tempB))
			{
				tempB = getNextEntityList(tempB);
				elementB = tempB->entity;

				if ((elementB->x < SCREEN_W + 6 && (elementB->x + elementB->size_x) > -6)
					&& (elementB->y < SCREEN_H + 6 && (elementB->y + elementB->size_y) > -6))
				{
					if (elementB->updateFlag)
					{
						elementB->updateFlag = false;
						//routines
						if (elementB->type == ENEMY_STARCRAFT_INTELLIGENT)
						{
							intelligentEnemyMove(player, elementB);
						}
						if ((elementB->type == ENEMY_STARCRAFT || elementB->type == ENEMY_STARCRAFT_INTELLIGENT) && enemySpawnCounter % 160 == 0)
						{
							handleEnemyShoot(*elementB);
						}

						if (elementB->type == BIG_BOSS) 
						{
							printf_s("Hola\n");
							if (elementB->y < 0)
							{
								elementB->speed_y = 3;
							}
							else if (elementB->y + elementB->size_y > SCREEN_H)
							{
								elementB->speed_y = -3;
							}
							if (enemySpawnCounter % 160 == 0)
							{
								handleEnemyShoot(*elementB);
								printf_s("Hola");
							}
			
						}
						elementB->x = elementB->x + elementB->speed_x;
						elementB->y = elementB->y + elementB->speed_y;
						elementB->updateFlag = false;
					}
					//colissions

					if (colission(elementA, elementB))
					{
						elementA->life = elementA->life - elementB->damage;
						elementB->life = elementB->life - elementA->damage;

						printf_s("WE HAVE A COLLITION\n");

						if (elementA->life <= 0)
						{
							if (elementA->type != PLAYER)
							{
								deleteElement(tempA);
							}
							else
							{
								al_play_sample(player.die, SAMPLE_GAIN, SAMPLE_PAN, SAMPLE_SPEED, SAMPLE_PLAY_ONCE, NULL);
								gameStatus = NO_LIFE;
							}
						}

						if (elementB->life <= 0)
						{
							if (elementB->type != ENEMY_BULLET)
							{
								al_play_sample(elementB->die, SAMPLE_GAIN, SAMPLE_PAN, SAMPLE_SPEED, SAMPLE_PLAY_ONCE, NULL);
							}
							
							if (elementB->type == BIG_BOSS)
							{
								isBossSpawned = false;
								backgroundX = 0;
								gameStatus++;
							}
							deleteElement(tempB);
						}

					}

				}
				else
				{
					deleteElement(tempB);
				}
			}
		}
		else
		{
			deleteElement(tempA);
		}
		if (hasNext(tempA))
		{
			tempA = getNextEntityList(tempA);
			elementA = tempA->entity;
			helper = true;
		}
	}
	
}

void handlePlayerShoot()
{
	if (!canShoot)
	{
		return;
	}
	canShoot = false;
	al_play_sample(player.shoot, SAMPLE_GAIN, SAMPLE_PAN, SAMPLE_SPEED, SAMPLE_PLAY_ONCE, NULL);
	float buX = 0.0;
	float buY = 0.0;

	buX = getBulletX(player, GETTER_PLAYER_XY);
	buY = getBulletY(player);

	Entity * element = (Entity *)malloc(sizeof(Entity));

	addEntityListElement(
		BULLET_SMALL_SIZE_X,
		BULLET_SMALL_SIZE_Y,
		buX,
		buY,
		PLAYER_BULLET_SPEED,
		0,
		BULLET_SMALL_DAMAGE,
		BULLET_LIFE,
		FRENDLY_BULLET,
		shootA,
		NULL,
		NULL,
		element,
		listTypeA);
}

void spawnEnemies()
{
	int dy = (rand() % (SCREEN_H - 64)); //El valor de 'y' donde va a hacer spawn
	int enemyType;

	Entity * enemy = (Entity*)malloc(sizeof(Entity));

	ALLEGRO_BITMAP * enemyImage = NULL;
	if ((rand() % 2) == 0)// El enemigo es normal, sin inteligencia
	{
		enemyImage = enemyAImage;
		enemyType = ENEMY_STARCRAFT;
	}
	else //El enemigo es inteligente
	{
		enemyImage = enemyBImage;
		enemyType = ENEMY_STARCRAFT_INTELLIGENT;
	}

	addEntityListElement(
		IMAGE_SIZE_HEIGHT * 2,
		IMAGE_SIZE_WIDTH * 2,
		SCREEN_W,
		dy,
		ENEMY_SPEED_X,
		0,
		ENEMY_DAMAGE,
		ENEMY_LIFE,
		enemyType,
		enemyImage,
		enemyShoot,
		enemyDie,
		enemy,
		listTypeB
	);
}

float getBulletX(Entity element, int type)
{
	float result = 0.0;
	if (type == GETTER_ENEMY_XY)
	{
		result = (float) element.x;
	}
	else if (type == GETTER_PLAYER_XY)
	{
		result =(float) (element.x + element.size_x);
	}

	return result;
}

float getBulletY(Entity element)
{
	return (float) (element.y + (element.size_y / 2.0) - BULLET_SMALL_SIZE_Y / 2);
}

void handleEnemyShoot(Entity enemy)
{
	ALLEGRO_BITMAP *currentShoot = shootB;
	al_play_sample(enemyShoot, SAMPLE_GAIN, SAMPLE_PAN, SAMPLE_SPEED, SAMPLE_PLAY_ONCE, NULL);
	float buX = 0.0;
	float buY = 0.0;

	buX = getBulletX(enemy, GETTER_ENEMY_XY);
	buY = getBulletY(enemy);

	Entity * element = (Entity *)malloc(sizeof(Entity));

	if (enemy.type == BIG_BOSS)
		currentShoot = shootC;
	

	addEntityListElement(
		BULLET_SMALL_SIZE_X,
		BULLET_SMALL_SIZE_Y,
		buX,
		buY,
		ENEMY_BULLET_SPEED,
		0,
		BULLET_SMALL_DAMAGE,
		BULLET_LIFE,
		ENEMY_BULLET,
		currentShoot,
		NULL,
		NULL,
		element,
		listTypeA);
}