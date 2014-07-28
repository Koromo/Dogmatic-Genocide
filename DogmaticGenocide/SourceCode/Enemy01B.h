#pragma once

#include "Enemy01.h"

class Enemy01B : public Enemy01{
private:
	Counter shotCnt;
	float angle;
	void (Enemy01B::*fp_shot)();

public:
	Enemy01B(int imageHandle, Vector& position, float angle, float life);

protected:
	void animetion();
	void move();
};

class Enemy01BEasy : public Enemy01B{
private:
	Counter m_shotCnt;

public:
	Enemy01BEasy(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

class Enemy01BNormal : public Enemy01B{
private:
	Counter m_shotCnt;

public:
	Enemy01BNormal(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

class Enemy01BHard : public Enemy01B{
private:
	Counter m_shotCnt;

public:
	Enemy01BHard(int imageHandle, Vector& position, float angle, float life);

protected:
	void shot();
};

inline void createEnemy01B(int imageHandle, Vector& position, float angle, float life, int level){
	switch(level){
	case 1:
		EnemyMng.set(new Enemy01BEasy(imageHandle, position, angle, life));
		break;
	case 2:
		EnemyMng.set(new Enemy01BNormal(imageHandle, position, angle, life));
		break;
	case 3:
		EnemyMng.set(new Enemy01BHard(imageHandle, position, angle, life));
		break;
	default:
		break;
	}
}