/**
 * This is the code to dectect if there is a colission
 */
bool colission(Entity *entyA, Entity *entyB);
bool intersecs(float aX, float aY, float aSize_x, float aSize_y, float bX, float bY, float bSize_x, float bSize_y);

/**
* param: BitMapsList entyA
* param: BitMapsList entyB
* return: bool
* summary detects if a BitMap intersects with other
*/
bool colission(Entity *entyA, Entity *entyB)
{
	// is the range between A and B
	if (intersecs(entyA->x, entyA->y, entyA->size_x, entyA->size_y, entyB->x, entyB->y, entyB->size_x, entyB->size_y))
	{
		return true;
	}

	return false;
}

/**
 * float aX
 * float aY
 * int aSize_x
 * int aSize_y
 * float b
 * float bY
 * int bSize_x
 * int bSize_y
 * @return: bool
 */
bool intersecs(float aX, float aY, float aSize_x, float aSize_y, float bX, float bY, float bSize_x, float bSize_y)
{
	int fix = 6;

	if (max(aX, bX - fix) < min((aX + aSize_x), (bX + bSize_x + fix)) &&
		max(aY, bY - fix) < min((aY + aSize_y), (bY + bSize_y + fix)))
	{
		return true;
	}
	return false;
}
