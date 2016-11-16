/**
 * This is the file for the inteligence
 */

#include "LinkedList.h"

void intelligentEnemyMove(BitMap frendly, BitMap enemy);
void intelligentBossMove(BitMap frendly, BitMap boss, BitMap bullet);

void intelligentEnemyMove(BitMap frendly, BitMap enemy)
{
	if (frendly.y < enemy.y)
	{
		enemy.y -= 10.0;
	}
	else if (frendly.y < enemy.y)
	{
		enemy.y += 10.0;
	}
}

void intelligentBossMove(BitMap frendly, BitMap boss, BitMap bullet) {

}