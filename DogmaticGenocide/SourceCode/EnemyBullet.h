#pragma once

#include "Bullet.h"

class EnemyBulletUnit : public Object, public IEnemyBullet{
protected:
	std::vector<HitCircle> hitCircle;
	bool collision;
	int color;
	float speed;
	float angle;

public:
	EnemyBulletUnit(int imageHandle, Vector& position, int color, float speed, float angle, bool collision);
	void draw();
	bool isCollision();
	const std::vector<HitCircle>& getHitCircle();
	void hitAction(IPlayer* player);
	void explosion(bool itemCreate);
	int getColor();
};