#pragma once

#include "Enemy01.h"

class Enemy01A : public Enemy01{
private:
	float speed;
	Counter moveCnt;

public:
	Enemy01A(int imageHandle, Vector& position, float life);

protected:
	void move();
};

class Enemy01AEasy : public Enemy01A{
private:
	Counter m_shotCnt;

public:
	Enemy01AEasy(int imageHandle, Vector& position, float life);

protected:
	void shot();
};

class Enemy01ANormal : public Enemy01A{
private:
	Counter m_shotCnt;

public:
	Enemy01ANormal(int imageHandle, Vector& position, float life);

protected:
	void shot();
};

class Enemy01AHard : public Enemy01A{
private:
	Counter m_shotCnt;

public:
	Enemy01AHard(int imageHandle, Vector& position, float life);

protected:
	void shot();
};

class Enemy01AexEasy : public Enemy01AEasy{
	bool& m_b;

public:
	Enemy01AexEasy(int imageHandle, Vector& position, float life, bool& b);
	~Enemy01AexEasy();
};

class Enemy01AexNormal : public Enemy01ANormal{
	bool& m_b;

public:
	Enemy01AexNormal(int imageHandle, Vector& position, float life, bool& b);
	~Enemy01AexNormal();
};

class Enemy01AexHard : public Enemy01AHard{
	bool& m_b;

public:
	Enemy01AexHard(int imageHandle, Vector& position, float life, bool& b);
	~Enemy01AexHard();
};

inline void createEnemy01A(int imageHandle, Vector& position, float life, int level){
	switch(level){
	case 1:
		EnemyMng.set(new Enemy01AEasy(imageHandle, position, life));
		break;
	case 2:
		EnemyMng.set(new Enemy01ANormal(imageHandle, position, life));
		break;
	case 3:
		EnemyMng.set(new Enemy01AHard(imageHandle, position, life));
		break;
	default:
		break;
	}
}

inline void createEnemy01Aex(int imageHandle, Vector& position, float life, bool& b, int level){
	switch(level){
	case 1:
		EnemyMng.set(new Enemy01AexEasy(imageHandle, position, life, b));
		break;
	case 2:
		EnemyMng.set(new Enemy01AexNormal(imageHandle, position, life, b));
		break;
	case 3:
		EnemyMng.set(new Enemy01AexHard(imageHandle, position, life, b));
		break;
	default:
		break;
	}
}