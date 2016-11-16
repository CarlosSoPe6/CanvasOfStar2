#include "allegro5/allegro.h"

typedef struct bitMaps
{
	int size;
	float x;
	float y;
	float speed;
	float damage;
	float life;
	ALLEGRO_BITMAP *image;
} BitMap;

typedef struct list
{
	BitMap bitMap;
	BitMap *next;
} BitMapsList;

/**
 * param: BitMapsList elem
 * summary: Deletes a element from a list
 */
void removeBitMapsListElement(BitMapsList list, BitMap element)
{

}

/**
 * param: int size
 * param: float x
 * param: float y
 * param: float speed
 * param float damage;
 * param: float life;
 * param: ALLEGRO_BITMAP * image
 * param: BitMapsList list
 * param BitMap emenent
 * summary: Adds a element from a list
 */
void addBitMapsListElemet(int size, float x, float y, float speed, float damage, float life, ALLEGRO_BITMAP * image, BitMapsList list, BitMap element)
{
	element.damage = damage;
	element.image = image;
	element.life = life;
	element.size = size;
	element.speed = speed;
	element.x = x;
	element.y = y;
	//TODO add "element" to "list"
}

/**
 * summary: Gets a element from a list
 */
void getBitMapsListElement()
{
	//TODO Create algorithm to get elements
	
}