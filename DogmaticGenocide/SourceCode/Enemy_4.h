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

class Enemy04A : public Enemy04{
private:
	void (Enemy04A::*fp_shot)();
	float comeAngle;
	Counter moveCnt;
	Counter shotCnt;
	float speed;
	float shotAngle;

public:
	Enemy04A(int imageHandle, Vector& position, float life, float angle, int level);

protected:
	void move();
	void shot();
	void easyShot();
	void normalShot();
	void hardShot();
};