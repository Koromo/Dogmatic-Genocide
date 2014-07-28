#pragma once

#include "Enemy04.h"

class Enemy04A : public Enemy04{
private:
	Counter moveCnt;
	float speed;
	float comeAngle;

public:
	Enemy04A(int imageHandle, Vector& position, float angle, float life);

protected:
	void move();
};

class Enemy04AEasy : public Enemy04A{
private:
	Counter m_shotCnt;

public:
	Enemy04AEasy(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

class Enemy04ANormal : public Enemy04A{
private:
	Counter m_shotCnt;

public:
	Enemy04ANormal(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

class Enemy04AHard : public Enemy04A{
private:
	Counter m_shotCnt;

public:
	Enemy04AHard(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

inline void createEnemy04A(int imageHandle, Vector& position, float angle, float life, int level){
	switch(level){
	case 1:
		EnemyMng.set(new Enemy04AEasy(imageHandle, position, angle, life));
		break;
	case 2:
		EnemyMng.set(new Enemy04ANormal(imageHandle, position, angle, life));
		break;
	case 3:
		EnemyMng.set(new Enemy04AHard(imageHandle, position, angle, life));
		break;
	default:
		break;
	}
}