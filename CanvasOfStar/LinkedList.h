#include "allegro5/allegro.h"

typedef struct bitMaps
{
	int size;
	float x;
	float y;
	float speed;
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
void removeBitMapsListElement(BitMapsList elem)
{

}

/**
 * param: int size
 * param: float x
 * param: float y
 * param: float speed
 * param: ALLEGRO_BITMAP * image
 * param: BitMapsList list
 * summary: Adds a element from a list
 */
void addBitMapsListElemet(int size, float x, float y, float speed, ALLEGRO_BITMAP * image, BitMapsList list)
{

}

/**
 * summary: Gets a element from a list
 */
void getBitMapsListElement()
{
	//TODO Create algorithm to get elements
}