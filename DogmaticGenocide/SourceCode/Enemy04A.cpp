#include "Enemy04A.h"
#include "DxLib.h"
#include "ObjectManager.h"
#include "EnemyBullet.h"

Enemy04A::Enemy04A(int imageHandle, Vector& position, float angle, float life) :
Enemy04(imageHandle, position, life),
comeAngle(angle)
{ }

void Enemy04A::move(){
	const float backAngle = 0.25f;
	const int comeCnt = 150;
	const int stopCnt = 0;
	const float lowSpeed = 1.5f;
	const float maxSpeed = 2.5f;
	const float accel = 0.02f;
	float rad = 0.25f * TWO_PI;

	if(moveCnt <= comeCnt){
		speed = static_cast<float>(comeCnt - moveCnt) * accel;
		rad = comeAngle * TWO_PI;

		if(speed > maxSpeed){
			speed = maxSpeed;
		}

	}else if(moveCnt > comeCnt + stopCnt){
		speed += accel;
		rad = backAngle * TWO_PI;

		if(speed > lowSpeed){
			speed = lowSpeed;
		}
	}

	position.x += cosf(rad) * speed;
	position.y += sinf(rad) * speed;

	++moveCnt;
}

Enemy04AEasy::Enemy04AEasy(int imageHandle, Vector& position, float angle, float life) :
Enemy04A(imageHandle, position, angle, life),
m_shotCnt(-25)
{ }

void Enemy04AEasy::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt == 0){
			int handleR = ImageMng.get(EB_01R);
			int handleB = ImageMng.get(EB_01B);
			Vector pos1 = getVector(position.x - 30.0f, position.y);
			Vector pos2 = getVector(position.x + 30.0f, position.y);
			float angle1 = getNWayAngle(PlayerMng.getAngle(pos1), 0.04f, 5);
			float angle2 = getNWayAngle(PlayerMng.getAngle(pos2), 0.04f, 5);

			for(int i = 0; i < 5; ++i){
				for(int j = 0; j < 3; ++j){
					EnemyBulletMng.set(new EnemyBullet01(handleR, pos1, RED, 4.0f - 0.3f * j, angle1 + 0.04f * i));
					EnemyBulletMng.set(new EnemyBullet01(handleB, pos2, BLUE, 4.0f - 0.3f * j, angle2 + 0.04f * i));
				}
			}
		}
	}
	++m_shotCnt;
}

Enemy04ANormal::Enemy04ANormal(int imageHandle, Vector& position, float angle, float life) :
Enemy04A(imageHandle, position, angle, life),
m_shotCnt(-25)
{ }

void Enemy04ANormal::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt == 0){
			int handleR = ImageMng.get(EB_01R);
			int handleB = ImageMng.get(EB_01B);
			Vector pos1 = getVector(position.x - 30.0f, position.y);
			Vector pos2 = getVector(position.x + 30.0f, position.y);
			float angle1 = getNWayAngle(PlayerMng.getAngle(pos1), 0.035f, 7);
			float angle2 = getNWayAngle(PlayerMng.getAngle(pos2), 0.035f, 7);

			for(int i = 0; i < 5; ++i){
				for(int j = 0; j < 5; ++j){
					EnemyBulletMng.set(new EnemyBullet01(handleR, pos1, RED, 4.2f - 0.3f * j, angle1 + 0.035f * i));
					EnemyBulletMng.set(new EnemyBullet01(handleB, pos2, BLUE, 4.2f - 0.3f * j, angle2 + 0.035f * i));
				}
			}
		}
	}
	++m_shotCnt;
}

Enemy04AHard::Enemy04AHard(int imageHandle, Vector& position, float angle, float life) :
Enemy04A(imageHandle, position, angle, life),
m_shotCnt(-25)
{ }

void Enemy04AHard::shot(){
	if(m_shotCnt >= 0){
		if(m_shotCnt == 0){
			int handleR = ImageMng.get(EB_01R);
			int handleB = ImageMng.get(EB_01B);
			Vector pos1 = getVector(position.x - 30.0f, position.y);
			Vector pos2 = getVector(position.x + 30.0f, position.y);
			float angle1 = getNWayAngle(PlayerMng.getAngle(pos1), 0.03f, 11);
			float angle2 = getNWayAngle(PlayerMng.getAngle(pos2), 0.03f, 11);

			for(int i = 0; i < 7; ++i){
				for(int j = 0; j < 8; ++j){
					EnemyBulletMng.set(new EnemyBullet01(handleR, pos1, RED, 4.2f - 0.2f * j, angle1 + 0.03f * i));
					EnemyBulletMng.set(new EnemyBullet01(handleB, pos2, BLUE, 4.2f - 0.2f * j, angle2 + 0.03f * i));
				}
			}
		}
	}
	++m_shotCnt;
}