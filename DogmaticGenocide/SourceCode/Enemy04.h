#pragma once

#include "Enemy.h"

extern const float ENEMY04_LIFE;

class Enemy04 : public EnemyUnit{
protected:
	bool active;
	bool privActive;

public:
	Enemy04(int imageHandle, Vector& position, float life);
	void update();

protected:
	void explosion();
	void hitCircleUpdate();
	void dropItem();
	virtual bool isActive();
	virtual bool isAlive();
	virtual void move() = 0;
	virtual void shot() = 0;
};