#include "Enemy03A.h"
#include "EnemyBullet.h"

Enemy03A::Enemy03A(int imageHandle, Vector& position, float life) :
Enemy03(imageHandle, position, life)
{ }

void Enemy03A::move(){
	const int comeCnt = 170;
	const int stopCnt = 0;
	const float lowSpeed = 1.0f;
	const float maxSpeed = 2.0f;
	const float accel = 0.02f;
	float rad = 0.25f * TWO_PI;

	if(moveCnt <= comeCnt){
		speed = static_cast<float>(comeCnt - moveCnt) * accel;

		if(speed > maxSpeed){
			speed = maxSpeed;
		}

	}else if(moveCnt > comeCnt + stopCnt){
		speed += accel;

		if(speed > lowSpeed){
			speed = lowSpeed;
		}
	}

	position.x += cosf(rad) * speed;
	position.y += sinf(rad) * speed;

	++moveCnt;
}

Enemy03AEasy::Enemy03AEasy(int imageHandle, Vector& position, float life) :
Enemy03A(imageHandle, position, life),
m_shotCnt(-20)
{ }

void Enemy03AEasy::shot(){
	if(m_shotCnt >= 0){
		int n = m_shotCnt % 80;

		if(n < 3 * 8 && n % 8 == 0){
			int handle = ImageMng.get(EB_02B);
			EnemyBulletMng.set(new EnemyBullet02(handle, position, BLUE, 4.0f, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}

Enemy03ANormal::Enemy03ANormal(int imageHandle, Vector& position, float life) :
Enemy03A(imageHandle, position, life),
m_shotCnt(-20)
{ }

void Enemy03ANormal::shot(){
	if(m_shotCnt >= 0){
		int n = m_shotCnt % 80;

		if(n < 3 * 8 && n % 8 == 0){
			int handle = ImageMng.get(EB_02B);
			EnemyBulletMng.set(new EnemyBullet02(handle, getVector(position.x - 10.0f, position.y), BLUE, 4.2f, PlayerMng.getAngle(position)));
			EnemyBulletMng.set(new EnemyBullet02(handle, getVector(position.x + 10.0f, position.y), BLUE, 4.2f, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}

Enemy03AHard::Enemy03AHard(int imageHandle, Vector& position, float life) :
Enemy03A(imageHandle, position, life),
m_shotCnt(-20)
{ }

void Enemy03AHard::shot(){
	if(m_shotCnt >= 0){
		int n = m_shotCnt % 80;

		if(n < 4 * 4 && n % 4 == 0){
			int handle = ImageMng.get(EB_02B);
			float angle = getNWayAngle(PlayerMng.getAngle(position), 0.08f, 2);

			for(int i = 0; i < 2; ++i){
				EnemyBulletMng.set(new EnemyBullet02(handle, getVector(position.x - 10.0f, position.y), BLUE, 4.2f, angle + 0.08f * i));
				EnemyBulletMng.set(new EnemyBullet02(handle, getVector(position.x + 10.0f, position.y), BLUE, 4.2f, angle + 0.08f * i));
			}
		}

		if(n < 3 * 2 && n % 2){
			int handle = ImageMng.get(EB_02B);

			EnemyBulletMng.set(new EnemyBullet02(handle, getVector(position.x - 10.0f, position.y), BLUE, 3.7f + 0.5f * n / 2, PlayerMng.getAngle(position)));
			EnemyBulletMng.set(new EnemyBullet02(handle, getVector(position.x + 10.0f, position.y), BLUE, 3.7f + 0.5f * n / 2, PlayerMng.getAngle(position)));
		}
	}
	++m_shotCnt;
}