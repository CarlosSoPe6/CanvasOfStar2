/**
 * This is the code to dectect if there is a colission
 */
bool colission(Entity *entyA, Entity *entyB);
bool intersecs(float aX, float aY, int aSize_x, int aSize_y, float bX, float bY, int bSize_x, int bSize_y);

/**
* param: BitMapsList entyA
* param: BitMapsList entyB
* return: bool
* summary detects if a BitMap intersects with other
*/
bool colission(Entity *entyA, Entity *entyB)
{
#ifdef DEBUG
		printf_s("Ax: %f, ", entyA->x);
		printf_s("Ay: %f, ", entyA->y);
		printf_s("Af: %c\n", entyA->updateFlag ? 'V' : 'F');
		printf("---------------------------------------\n");
		printf_s("Bx: %f, ", entyB->x);
		printf_s("By: %f, ", entyB->y);
		printf_s("Bf: %c\n", entyB->updateFlag ? 'V' : 'F');
		printf("---------------------------------------\n");


#endif // DEBUG

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
bool intersecs(float aX, float aY, int aSize_x, int aSize_y, float bX, float bY, int bSize_x, int bSize_y)
{
	if ((aX <= bX) && ((aX + aSize_x) >= bX))
	{
		if ((aY <= bY) && ((aY + aSize_y) >= bY))
		{
			return true;
		}
	}

	if (((aX) <= (bX + bSize_x)) && ((aX + aSize_x) >= (bX + bSize_x)))
	{
		if (((aY) <= (bY + bSize_y)) && ((aY + aSize_y) >= (bY + bSize_y)))
		{
  			return true;
		}
	}
	return false;
}
