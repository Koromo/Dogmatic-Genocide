#pragma once

#include "EnemyBullet.h"

class EnemyBullet02 : public EnemyBulletUnit{
protected:
	Counter animeCnt;

public:
	EnemyBullet02(int imageHandle, Vector& position, int color, float speed, float angle);
	void update();
};