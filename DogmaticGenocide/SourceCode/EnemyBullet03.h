#pragma once

#include "EnemyBullet.h"

class EnemyBullet03 : public EnemyBulletUnit{
public:
	EnemyBullet03(int imageHandle, Vector& position, int color, float speed, float angle);
	void update();
};