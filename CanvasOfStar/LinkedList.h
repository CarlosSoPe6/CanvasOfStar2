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
	ALLEGRO_SAMPLE *shoot;
	ALLEGRO_SAMPLE *die;
} BitMap;

typedef struct list
{
	BitMap *prev;
	BitMap bitMap;
	BitMap *next;
} BitMapsList;
BitMapsList *first = NULL;
BitMapsList *last = NULL;

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
void addBitMapsListElemet(int size_x, int size_y, float x, float y, float speed_x, float speed_y, float damage, float life, ALLEGRO_BITMAP * image, ALLEGRO_SAMPLE *shoot, ALLEGRO_SAMPLE *die, BitMap * element, BitMapsList * list)
{
	BitMapsList * nextElement = NULL;

	element->damage = damage;
	element->image = image;
	element->life = life;
	element->size_x = size_x;
	element->size_y = size_y;
	element->x = x;
	element->y = y;
	element->speed_x = speed_x;
	element->speed_y = speed_y;
	element->shoot = shoot;
	element->die = die;

	nextElement->bitMap = element;

	//add "element" to "list"
	if (first == NULL)
	{
		first = nextElement;
		last = nextElement;
	}
	else
	{
		last->prev = last;
		last->next = nextElement;
		last = nextElement;
	}
}

/**
 * Has a next element
 */
bool next()
{
	//TODO Create algorithm to get elements
	
}

/**
 * Gets the next bit map
 */
BitMap getNextBitMap()
{

}


/**
 * Deletes a element from a list
 * param: element
 * param: list
 */
void deleteElement(BitMap element, BitMapsList list)
{

}