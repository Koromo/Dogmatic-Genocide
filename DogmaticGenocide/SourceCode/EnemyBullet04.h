#pragma once

#include "EnemyBullet.h"

class EnemyBullet04 : public EnemyBulletUnit{
private:
	Counter CNT_;
	Counter cnt_;
	float angle2_;

public:
	EnemyBullet04(int imageHandle, Vector& position, int color, float speed, float angle, float angle2_, Counter cnt);
	void update();
};