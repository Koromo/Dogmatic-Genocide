#include "BossFactory.h"
#include "Boss01.h"

void BossFactory::createBoss01(int imageHandle, Vector& position, float life, int level){
	switch(level){
	case 1:
		EnemyMng.set(new Boss01Easy(imageHandle, position, life));
		break;
	case 2:
		EnemyMng.set(new Boss01Normal(imageHandle, position, life));
		break;
	case 3:
		EnemyMng.set(new Boss01Hard(imageHandle, position, life));
		break;
	default:
		break;
	}
}