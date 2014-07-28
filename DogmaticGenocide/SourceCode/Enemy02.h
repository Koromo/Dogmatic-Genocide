#pragma once

#include "Enemy.h"

extern const float ENEMY01_LIFE;

class Enemy02 : public EnemyUnit{
private:
	bool active_;
	bool privActive_;

public:
	Enemy02(int imageHandle, Vector& position, float life);
	void update();

protected:
	void adjustHitCircle();
	virtual void move() = 0;
	virtual void shot() = 0;
};