#pragma once

#include "Enemy03.h"

class Enemy03A : public Enemy03{
private:
	Counter moveCnt;
	float speed;

public:
	Enemy03A(int imageHandle, Vector& position, float life);

protected:
	void move();
};

class Enemy03AEasy : public Enemy03A{
private:
	Counter m_shotCnt;

public:
	Enemy03AEasy(int imageHandle, Vector& position, float life);

protected:
	void shot();
};

class Enemy03ANormal : public Enemy03A{
private:
	Counter m_shotCnt;

public:
	Enemy03ANormal(int imageHandle, Vector& position, float life);

protected:
	void shot();
};

class Enemy03AHard : public Enemy03A{
private:
	Counter m_shotCnt;

public:
	Enemy03AHard(int imageHandle, Vector& position, float life);

protected:
	void shot();
};

inline void createEnemy03A(int imageHandle, Vector& position, float life, int level){
	switch(level){
	case 1:
		EnemyMng.set(new Enemy03AEasy(imageHandle, position, life));
		break;
	case 2:
		EnemyMng.set(new Enemy03ANormal(imageHandle, position, life));
		break;
	case 3:
		EnemyMng.set(new Enemy03AHard(imageHandle, position, life));
		break;
	default:
		break;
	}
}