#include "Enemy01B.h"

Enemy01B::Enemy01B(int imageHandle, Vector& position, float angle, float life) :
Enemy01(imageHandle, position, life),
angle(angle),
shotCnt(-10)
{ }

void Enemy01B::move(){
	const float speed = 4.0f;
	float rad = angle * TWO_PI;
	float aimRad = rad;
	const float maxRad = 0.003f * TWO_PI; 
	float turnRad;

	if(ObjectMng.hasObject(PLAYER)){
		aimRad = PlayerMng.getAngle(position) * TWO_PI;
	}

	turnRad = rad - aimRad;

	if(turnRad > PI) turnRad -= TWO_PI;
	if(turnRad < -PI) turnRad += TWO_PI;
	if(turnRad > maxRad) turnRad = maxRad;
	if(turnRad < -maxRad) turnRad = -maxRad;

	rad -= turnRad;
	angle = rad / TWO_PI;

	position.x += cosf(rad) * speed;
	position.y += sinf(rad) * speed;
}

void Enemy01B::animetion(){
	image.angle = angle - 0.25f;
}

Enemy01BEasy::Enemy01BEasy(int imageHandle, Vector& position, float angle, float life) :
Enemy01B(imageHandle, position, angle, life),
m_shotCnt(-10)
{ }

void Enemy01BEasy::shot(){
	if(m_shotCnt >= 0){
	}
	++m_shotCnt;
}

Enemy01BNormal::Enemy01BNormal(int imageHandle, Vector& position, float angle, float life) :
Enemy01B(imageHandle, position, angle, life),
m_shotCnt(-10)
{ }

void Enemy01BNormal::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt % 80 == 0){
			int handle = ImageMng.get(EB_02R);

			EnemyBulletMng.set(new EnemyBullet02(handle, position, RED, 3.5f, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}

Enemy01BHard::Enemy01BHard(int imageHandle, Vector& position, float angle, float life) :
Enemy01B(imageHandle, position, angle, life),
m_shotCnt(-10)
{ }

void Enemy01BHard::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt % 60 == 0){
			int handle = ImageMng.get(EB_02R);

			EnemyBulletMng.set(new EnemyBullet02(handle, position, RED, 3.5f, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}
