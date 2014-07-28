#pragma once

#include "Enemy.h"
#include <boost\coroutine\all.hpp>

class Boss01;

typedef boost::coroutines::coroutine<void(Boss01*)> MoveCoro_t;
typedef boost::coroutines::coroutine<void(Boss01*, int)> BarrageCoro_t;

extern const float BOSS01_LIFE;

class Boss01 : public EnemyUnit, public IBoss{
protected:
	void (Boss01::*fp_update_)();
	Vector position_[3];
	int level_;
	Counter loop_;
	MoveCoro_t move_;
	BarrageCoro_t barrage_;
	Counter cnt_;

public:
	Boss01(int imageHandle, Vector& position, float life, int level);
	~Boss01();
	void update();
	float getLife(){ return life; }
	Vector& refPosition(int n){
		if(n == 0) return position;
		return position_[n - 1];
	}

protected:
	void adjustHitCircle();
	void adjustPosition();
	void update01();
	void update02();
	void update03();
	void update04();
	void update05();
	void update06();
	void update07();
};

inline void createBoss01(int imageHandle, Vector& position, float life, int level){
	EnemyMng.set(new Boss01(imageHandle, position, life, level));	
}