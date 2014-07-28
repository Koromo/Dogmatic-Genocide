#pragma once

#include "Object.h"
#include "Counter.h"
#include "ObjectManager.h"
#include "Item.h"

class BulletExplosion : public Object{
private:
	Counter animeCnt;

public:
	BulletExplosion(int imageHandle, Vector& position);
	void update();
	void draw();
};

class EnemyBulletExplosion : public BulletExplosion{
private:
	float m_speed;
	float m_angle;
	bool m_item;

public:
	EnemyBulletExplosion(int imageHandle, Vector& position, float speed, float angle, bool b) : 
	  BulletExplosion(imageHandle, position), m_speed(speed), m_angle(angle),
		m_item(b)
	  {
		  if(m_speed >= 1.5f){
			  m_speed = 1.5f;
		  }
	  }
	  ~EnemyBulletExplosion(){
		  if(m_item){
			  createPoint(ImageMng.get(_POINT), position);
		  }
	  }
	void update(){
		BulletExplosion::update();

		const float rad = m_angle * TWO_PI;
		position.x += cosf(rad) * m_speed;
		position.y += sinf(rad) * m_speed;
	}
};

class EnemyExplosion : public Object{
private:
	Counter animeCnt;

public:
	EnemyExplosion(int imageHandle, Vector& position);
	void update();
	void draw();
};

class PlayerExplosion : public Object{
private:
	Counter animeCnt;

public:
	PlayerExplosion(int imageHandle, Vector& position);
	void update();
	void draw();
};