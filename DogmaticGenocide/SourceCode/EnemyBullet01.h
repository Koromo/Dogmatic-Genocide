#pragma once

#include "EnemyBullet.h"

class EnemyBullet01 : public EnemyBulletUnit{
public:
	EnemyBullet01(int imageHandle, Vector& position, int color, float speed, float angle);
	void update();
};