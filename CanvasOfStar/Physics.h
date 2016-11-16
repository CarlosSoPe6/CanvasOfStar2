/**
 * This is the code to dectect if there is a colission
 */

#include "LinkedList.h"

 /**
 * param: BitMapsList frendly
 * param: BitMapsList enemy
 * return: bool
 * summary detects if a BitMap intersects with other
 */
bool colission(BitMap frendly, BitMap enemy);
bool intersecs(float aX, float aY, int aSize, float bX, float bY, float bSize);

bool colission(BitMap entyA, BitMap entyB)
{
	// is the range between A and B
	if (intersecs(entyA.x, entyA.y, entyA.size, entyB.x, entyB.y, entyB.size))
	{
		return true;
	}

	return false;
}

/**
 * param: float enemyX
 * param: float enemyY
 * param: int enemySize
 * param: float frendlyX
 * param: float frendlyY
 * param: int frendlySize
 * return: bool
 * summary detects if a BitMap intersects with other
 */
bool intersecs(float aX, float aY, int aSize, float bX, float bY, float bSize)
{
	if ((aX < bX) && ((aX + aSize) > bX))
	{
		if ((aY < bY) && ((aY + aSize) > bY))
		{
			return true;
		}
	}

	if (((aX) < (bX + bSize)) && ((aX + aSize) > (bX + bSize)))
	{
		if (((aY) < (bY + bSize)) && ((aY + aSize) > (bY + bSize)))
		{
			return true;
		}
	}
	return false;
}
