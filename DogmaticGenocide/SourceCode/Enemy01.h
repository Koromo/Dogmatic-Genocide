#pragma once

#include "Enemy.h"

extern const float ENEMY01_LIFE;

class Enemy01 : public EnemyUnit{
protected:
	bool active;
	bool privActive;

public:
	Enemy01(int imageHandle, Vector& position, float life);
	void update();

protected:
	void explosion();
	void adjustHitCircle();
	void deathAction();
	virtual void animetion();
	virtual bool isActive();
	virtual bool isAlive();
	virtual void move() = 0;
	virtual void shot() = 0;
};