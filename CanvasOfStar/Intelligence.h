/**
 * This is the file for the inteligence
 */

void intelligentEnemyMove(Entity frendly, Entity * enemy);
void intelligentBossMove(Entity frendly, Entity * boss);

void intelligentEnemyMove(Entity frendly, Entity * enemy)
{
	if (frendly.y < enemy->y)
	{
		enemy->speed_y = -3;
	}
	else if (frendly.y > enemy->y)
	{
		enemy->speed_y = 3;
	}
}

void intelligentBossMove(Entity frendly, Entity * boss) {

}