#pragma once

#include "PlayerBullet.h"

class PlayerBullet01 : public PlayerBulletUnit{
private:
	float speed;
	float angle;

public:
	PlayerBullet01(int imageHangle, Vector& position, float power, float speed, float angle);
	void update(); 
	void move();

private:
	void adjustHitCircle();
	void explosion();
};

class SupporterBullet01 : public PlayerBulletUnit{
private:
	float m_speed;
	float m_angle;

public:
	SupporterBullet01(int imageHangle, Vector& position, float power, float speed, float angle);
	void update(); 
	void move();

private:
	void hitCircleUpdate();
	void explosion();
};