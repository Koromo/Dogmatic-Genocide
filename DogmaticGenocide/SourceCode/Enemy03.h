#pragma once

#include "Enemy.h"

extern const float ENEMY03_LIFE;

class Enemy03 : public EnemyUnit{
protected:
	bool active;
	bool privActive;

public:
	Enemy03(int imageHandle, Vector& position, float life);
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