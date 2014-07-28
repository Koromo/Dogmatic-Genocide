#include "Enemy02A.h"

Enemy02A::Enemy02A(int imageHandle, Vector& position, float angle, float life) :
Enemy02(imageHandle, position, life),
angle(angle),
shotCnt(-10)
{ }

void Enemy02A::move(){
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

Enemy02AEasy::Enemy02AEasy(int imageHandle, Vector& position, float angle, float life) :
Enemy02A(imageHandle, position, angle, life),
m_shotCnt(-10)
{ }

void Enemy02AEasy::shot(){
}

Enemy02ANormal::Enemy02ANormal(int imageHandle, Vector& position, float angle, float life) :
Enemy02A(imageHandle, position, angle, life),
m_shotCnt(-10)
{ }

void Enemy02ANormal::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt % 20 == 0){
			int handle = ImageMng.get(EB_01B);
			float angle = image.angle;

			for(int i = 0; i < 2; ++i){
				EnemyBulletMng.set(new EnemyBullet01(handle, position, BLUE, 3.2f, angle + static_cast<float>(i / 2.0f)));
			}
		}
	}
	++m_shotCnt;
}

Enemy02AHard::Enemy02AHard(int imageHandle, Vector& position, float angle, float life) :
Enemy02A(imageHandle, position, angle, life),
m_shotCnt(-10)
{ }

void Enemy02AHard::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt % 20 == 0){
			int handle = ImageMng.get(EB_01B);
			float angle = image.angle;

			for(int i = 0; i < 4; ++i){
				EnemyBulletMng.set(new EnemyBullet01(handle, position, BLUE, 3.2f, angle + static_cast<float>(i / 4.0f)));
			}
		}
	}
	++m_shotCnt;
}
