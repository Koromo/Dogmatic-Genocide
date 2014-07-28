#include "Enemy01A.h"
#include "EnemyBullet.h"

Enemy01A::Enemy01A(int imageHandle, Vector& position, float life) :
Enemy01(imageHandle, position, life)
{ }

void Enemy01A::move(){
	const int comeCnt = 90;
	const int stopCnt = 60;
	const float maxSpeed = 3.0f;
	const float accel = 0.1f;
	float angle = 0.0f;
	float rad;

	if(moveCnt <= comeCnt){
		angle = 0.25f;
		speed = static_cast<float>(comeCnt - moveCnt) * accel;
	}else if(moveCnt > comeCnt + stopCnt){
		angle = -0.25f;
		speed += accel;
	}

	if(speed > maxSpeed){
		speed = maxSpeed;
	}

	rad = angle * TWO_PI;
	position.x += cosf(rad) * speed;
	position.y += sinf(rad) * speed;

	++moveCnt;
}

Enemy01AEasy::Enemy01AEasy(int imageHandle, Vector& position, float life) :
Enemy01A(imageHandle, position, life),
m_shotCnt(-10)
{ }

void Enemy01AEasy::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt % 60 == 0){
			int handle = ImageMng.get(EB_02R);

			EnemyBulletMng.set(new EnemyBullet02(handle, position, RED, 3.5f, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}

Enemy01ANormal::Enemy01ANormal(int imageHandle, Vector& position, float life) :
Enemy01A(imageHandle, position, life),
m_shotCnt(-10)
{ }

void Enemy01ANormal::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt % 50 == 0){
			int handleR = ImageMng.get(EB_02R);

			EnemyBulletMng.set(new EnemyBullet02(handleR, position, RED, 3.8f, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}

Enemy01AHard::Enemy01AHard(int imageHandle, Vector& position, float life) :
Enemy01A(imageHandle, position, life),
m_shotCnt(-10)
{ }

void Enemy01AHard::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt % 40 == 0){
			int handleR = ImageMng.get(EB_02R);

			EnemyBulletMng.set(new EnemyBullet02(handleR, position, RED, 3.8f, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}

Enemy01AexEasy::Enemy01AexEasy(int imageHandle, Vector& position, float life, bool& b) :
Enemy01AEasy(imageHandle, position, life),
m_b(b)
{ }

Enemy01AexEasy::~Enemy01AexEasy(){
	m_b = false;
}

Enemy01AexNormal::Enemy01AexNormal(int imageHandle, Vector& position, float life, bool& b) :
Enemy01ANormal(imageHandle, position, life),
m_b(b)
{ }

Enemy01AexNormal::~Enemy01AexNormal(){
	m_b = false;
}

Enemy01AexHard::Enemy01AexHard(int imageHandle, Vector& position, float life, bool& b) :
Enemy01AHard(imageHandle, position, life),
m_b(b)
{ }

Enemy01AexHard::~Enemy01AexHard(){
	m_b = false;
}