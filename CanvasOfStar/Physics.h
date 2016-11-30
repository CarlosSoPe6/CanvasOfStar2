/**
 * This is the code to dectect if there is a colission
 */
bool colission(Entity entyA, Entity entyB);
bool intersecs(float aX, float aY, float aSize_x, float aSize_y, float bX, float bY, float bSize_x, float bSize_y);

/**
* param: BitMapsList entyA
* param: BitMapsList entyB
* return: bool
* summary detects if a BitMap intersects with other
*/
bool colission(Entity entyA, Entity entyB)
{

	// is the range between A and B
	if (intersecs(entyA.x, entyA.y, entyA.size_x, entyA.size_y, entyB.x, entyB.y, entyB.size_x, entyB.size_y))
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
	float indexAX[4];
	float indexAY[4];
	float auxW = 0;
	float auxH = 0;

	float auxBX1 = bX;
	float auxBX2 = bX + bSize_x;
	float auxBY1 = bY;
	float auxBY2 = bY + bSize_y;
	
	for(int i = 0; i < 4; i++)
	{
		auxW = i & 1;
		auxH = (i > 1) & 1;
		indexAX[i] = aX + (auxW*aSize_x);
		indexAY[i] = aY + (auxH*aSize_y);

		if(indexAX[i] >= auxBX1 &&
			indexAX[i] <= auxBX2 &&
			indexAY[i] >= auxBY1 &&
			indexAY[i] <= auxBY2)
		{
			return true;
		}
	}
	return false;
}
