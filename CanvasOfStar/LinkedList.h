#include "allegro5/allegro.h"

typedef struct bitMaps
{
	int size_x;
	int size_y;
	float x;
	float y;
	float speed_x;
	float speed_y;
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
 * Inits a BitMap
 * param: size_x
 * param: size_y
 * param: x
 * param: y
 * param: speed_x
 * param: speed_y
 * param: damage
 * param: life
 * param: image
 * param: list
 * param: element
 */
void addBitMapsListElemet(int size_x, int size_y, float x, float y, float speed_x, float speed_y, float damage, float life, ALLEGRO_BITMAP * image, BitMapsList * list, BitMap element)
{
	element.damage = damage;
	element.image = image;
	element.life = life;
	element.size_x = size_x;
	element.size_y = size_y;
	element.x = x;
	element.y = y;
	element.speed_x = speed_x;
	element.speed_y = speed_y;

	//TODO add "element" to "list"
}

/**
 * Gets a element from a list
 */
void getBitMapsListElement()
{
	//TODO Create algorithm to get elements
	
}

/**
 * Deletes a element from a list
 * param: element
 * param: list
 */
void deleteElement(BitMap element, BitMapsList list)
{

}