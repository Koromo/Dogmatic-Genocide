#pragma once

#include "Object.h"
#include "Counter.h"
#include "Enemy.h"

//class Enemy_2 : public Enemy{
//protected:
//	float angle;
//	bool active;
//	bool privActive;
//
//public:
//	Enemy_2(int imageHandle, Vector& position, float life, float angle);
//	void update();
//	void draw();
//
//protected:
//	void hitCircleUpdate();
//	void animetion();
//	virtual bool isActive() = 0;
//	virtual void move() = 0;
//	virtual void shot() = 0;
//};
//
//class Enemy_2A : public Enemy_2{
//private:
//	Counter shotCnt;
//	float speed;
//
//public:
//	Enemy_2A(int imageHandle, Vector& position, float life, float angle);
//
//protected:
//	void move();
//	void shot();
//	bool isActive();
//	bool isAlive();
//};