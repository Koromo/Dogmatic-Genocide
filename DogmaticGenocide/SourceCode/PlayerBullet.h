#pragma once

#include "Bullet.h"

class PlayerBulletUnit : public Object, public IPlayerBullet{
protected:
	std::vector<HitCircle> hitCircle;
	bool collision;
	float power;

public:
	PlayerBulletUnit(int imageHandle, Vector& position, float power, bool collision);
	void draw();
	bool isCollision();
	const std::vector<HitCircle>& getHitCircle();
	void hitAction(IEnemy* enemy);
	float getPower();

protected:
	void collideJudge();
	virtual void explosion() = 0;
};

class PlayerBulletBoost : public PlayerBulletUnit{
private:
	float m_speed;
	float m_angle;
	int m_color;

public:
	PlayerBulletBoost(int imageHangle, Vector& position, int color, float power, float speed, float angle);
	void update(); 
	void move();

protected:
	void collideJudge();
	void hitCircleUpdate();
	void explosion();
};