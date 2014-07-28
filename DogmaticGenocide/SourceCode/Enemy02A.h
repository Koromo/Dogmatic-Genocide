#pragma once

#include "Enemy02.h"

class Enemy02A : public Enemy02{
protected:
	Counter shotCnt;
	float angle;
	void (Enemy02A::*fp_shot)();

public:
	Enemy02A(int imageHandle, Vector& position, float angle, float life);

protected:
	void move();
};

class Enemy02AEasy : public Enemy02A{
private:
	Counter m_shotCnt;

public:
	Enemy02AEasy(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

class Enemy02ANormal : public Enemy02A{
private:
	Counter m_shotCnt;

public:
	Enemy02ANormal(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

class Enemy02AHard : public Enemy02A{
private:
	Counter m_shotCnt;

public:
	Enemy02AHard(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

inline void createEnemy02A(int imageHandle, Vector& position, float angle, float life, int level){
	switch(level){
	case 1:
		EnemyMng.set(new Enemy02AEasy(imageHandle, position, angle, life));
		break;
	case 2:
		EnemyMng.set(new Enemy02ANormal(imageHandle, position, angle, life));
		break;
	case 3:
		EnemyMng.set(new Enemy02AHard(imageHandle, position, angle, life));
		break;
	default:
		break;
	}
}