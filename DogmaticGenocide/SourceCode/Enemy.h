#pragma once

#include "Object.h"
#include "Item.h"
#include "Effect.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "EnemyBullet01.h"
#include "EnemyBullet02.h"
#include "EnemyBullet03.h"

class EnemyUnit : public Object, public IEnemy{
protected:
	std::vector<HitCircle> hitCircle;
	bool collision;
	float life;

public:
	EnemyUnit(int imageHandle, Vector& position, float life, bool collision);
	void draw();
	bool isCollision();
	const std::vector<HitCircle>& getHitCircle();
	const Vector& getPosition();
	void hitAction(IPlayerBullet* playerBullet);
};