typedef struct ennts
{
	float size_x;
	float size_y;
	float x;
	float y;
	float speed_x;
	float speed_y;
	float damage;
	float life;
	int type;
	bool updateFlag;
	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *shoot;
	ALLEGRO_SAMPLE *die;
} Entity;

typedef struct list
{
	struct list * prev;
	struct list *next;
	Entity *entity;
} EntityList;

/**
 * Inits EntityList
 * param: EntityList * list
 */
void initializeEntityList(EntityList * list)
{
	list->next = NULL;
	list->prev = NULL;
	list->entity = NULL;
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
void addEntityListElement(
	int size_x, 
	int size_y, 
	float x, 
	float y, 
	float speed_x, 
	float speed_y, 
	float damage, 
	float life, 
	int type,
	ALLEGRO_BITMAP * image, 
	ALLEGRO_SAMPLE * shoot, 
	ALLEGRO_SAMPLE * die, 
	Entity * element, 
	EntityList * list)
{
	EntityList * current = list;

	while (current->next != NULL)
	{
		current = current->next;
	}

	//init element
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
	element->image = image;
	element->shoot = shoot;
	element->die = die;
	element->type = type;
	element->updateFlag = true;

	
	current->next = (EntityList *)malloc(sizeof(EntityList));
	current->next->prev = current;
	current->next->entity = element;
	current->next->next = NULL;
}

/**
 * Has a next element
 * param: EntityList * list
 */
bool hasNext(EntityList * list)
{
	if (list->next == NULL)
	{
		return false;
	}

	return true;
}

/**
 * Gets the next bit map
 * param: EntityList * list
 */
EntityList * getNextEntityList(EntityList * list)
{
	//TODO do this
	return list->next;
}


/**
 * Deletes a element from a list
 * param: EntityList * element
 */
void deleteElement(EntityList * element)
{
	EntityList * tempElement = element->prev;
	if (element->next != NULL)
	{
		element->next->prev = element->prev;
	}
	
	element->prev->next = element->next;
	element = tempElement;
}

/**
 * param propery
 * param: EntityList * element
 */
void setFlagEnabled(bool propery, EntityList * element)
{
	EntityList * current = element;

	while (current->next != NULL)
	{
		current = current->next;
		current->entity->updateFlag = propery;
	}
}