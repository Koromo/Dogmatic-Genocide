#include "MiniBoss01.h"
#include "ObjectManager.h"
#include "EnemyBullet.h"

const float MINIBOSS01_LIFE = 4000.0f;

MiniBoss01::MiniBoss01(int imageHandle, Vector& position, float life) :
EnemyUnit(imageHandle, position, life, true),
m_fp_update(&MiniBoss01::update01),
m_move01(nullptr)
{
	hitCircle.resize(1);
	for(int i = 0; i < 1; ++i){
		hitCircle[i].radius = 35.0f;
	}
	adjustHitCircle();
	adjustPosition();

	m_move01 = new Move01_t();
	m_move01->speed = 4.0f;
}

MiniBoss01::~MiniBoss01(){
	delete m_move01;
	m_move01 = nullptr;
	EnemyMng.setAlive(false);
}

void MiniBoss01::update(){
	(this->*m_fp_update)();
	adjustHitCircle();
	adjustPosition();
	
	if(life <= 0.0f){
		EnemyBulletMng.explosion(true);
		ScoreMng.addScore(5000);
		needDelete = true;
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_02), position));
		int handle = ImageMng.get(ENERGY_S);
		createEnergy(handle, getVector(position.x - 30.0f, position.y - 5.0f), 2);
		createEnergy(handle, getVector(position.x + 20.0f, position.y), 2);
		createEnergy(handle, getVector(position.x, position.y + 20.0f), 2);
		PlaySound(SoundMng.get(SE_EXPLOSION03));
	}

	EnemyMng.update(this);
}

void MiniBoss01::adjustHitCircle(){
	hitCircle[0].position = position;
}

void MiniBoss01::adjustPosition(){
	m_position[0] = getVector(position.x, position.y + 45.0f);
	m_position[1] = getVector(position.x - 30.0f, position.y);
	m_position[2] = getVector(position.x + 30.0f, position.y);
}

void MiniBoss01::update01(){
	const float rad = 0.55f * TWO_PI;

	m_move01->speed -= 0.025f;

	if(m_move01->speed < 0.0f){
		m_move01->speed = 0.0f;
	}

	position.x += cosf(rad) * m_move01->speed;
	position.y += sinf(rad) * m_move01->speed;

	if(m_move01->speed == 0.0f){
		m_fp_update = &MiniBoss01::update02;
	}
}

void MiniBoss01::update02(){
	barrage01();

	++m_cnt;
	if(m_cnt > 120){
		m_move01->speed = 0.8f;
		m_fp_update = &MiniBoss01::update03;
		m_cnt = 0;
	}
}

void MiniBoss01::update03(){
	m_move01->speed -= 0.005f;

	if(m_move01->speed < 0.0f){
		m_move01->speed = 0.0f;
	} else {
		const float rad = atan2f(position, getVector(320.0f, 60.0f));

		position.x += cosf(rad) * m_move01->speed;
		position.y += sinf(rad) * m_move01->speed;
	}

	barrage02();

	++m_cnt;
	if(m_cnt == 360){
		m_fp_update = &MiniBoss01::update04;
		m_cnt = 0;
	}
}

void MiniBoss01::update04(){
	barrage03();

	++m_cnt;
	if(m_cnt > 90){
		m_fp_update = &MiniBoss01::update05;
		m_move01->speed = 1.0f;
		m_cnt = 0;
	}
}

void MiniBoss01::update05(){
	m_move01->speed -= 0.005f;

	if(m_move01->speed < 0.0f){
		m_move01->speed = 0.0f;
	} else {
		const float rad = atan2f(position, getVector(320.0f, 200.0f));

		position.x += cosf(rad) * m_move01->speed;
		position.y += sinf(rad) * m_move01->speed;
	}

	barrage04();

	++m_cnt;
	if(m_cnt > 400){
		m_fp_update = &MiniBoss01::update06;
		m_cnt = -30;
	}
}

void MiniBoss01::update06(){
	const float rad = 0.55f * TWO_PI;

	m_move01->speed += 0.03f;

	if(m_move01->speed > 3.0f){
		m_move01->speed = 3.0f;
	}

	position.x += cosf(rad) * m_move01->speed;
	position.y += sinf(rad) * m_move01->speed;

	if(isFrameOut(0)){
		needDelete = true;
	}
}

MiniBoss01Easy::MiniBoss01Easy(int imageHandle, Vector& position, float life) :
MiniBoss01(imageHandle, position, life)
{ }

void MiniBoss01Easy::barrage01(){
	if(m_cnt == 0){
		m_barrage01.wayNum = 3;
		m_barrage01.width = 0.05f;
	}

	if(m_cnt % 60 == 0){
		float angle = getNWayAngle(PlayerMng.getAngle(m_position[0]), m_barrage01.width, m_barrage01.wayNum);
		int handle = ImageMng.get(EB_01R);

		for(int i = 0; i < m_barrage01.wayNum; ++i){
			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], RED, 4.3f, angle + m_barrage01.width * i));
		}
		++m_barrage01.wayNum;
		m_barrage01.width -= 0.005f;
	}

	if(m_cnt % 45 == 0){
		int handle = ImageMng.get(EB_03B);
		int way = 9;
		float width = 0.04f;
		float angle = getNWayAngle(PlayerMng.getAngle(m_position[0]), width, way);

		for(int i = 0; i < way; ++i){
			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], BLUE, 4.0f, angle + width * i));
		}
	}
}

void MiniBoss01Easy::barrage02(){
	if(m_cnt == 0){
		m_barrage02.wayNum = 2;
		m_barrage02.shotNum = 2;
	}

	if(m_cnt > 90){
		int n = m_cnt % 60;

		if(n == 0){
			++m_barrage02.wayNum;
			++m_barrage02.shotNum;
		}

		if(n < m_barrage02.shotNum * 5 && n % 5 == 0){
			float width = 0.05f;
			float speed = 4.5f;
			float angle1 = getNWayAngle(PlayerMng.getAngle(m_position[1]), width, m_barrage02.wayNum);
			float angle2 = getNWayAngle(PlayerMng.getAngle(m_position[2]), width, m_barrage02.wayNum);
			int handle1 = ImageMng.get(EB_02R);
			int handle2 = ImageMng.get(EB_02B);

			for(int i = 0; i < m_barrage02.wayNum; ++i){
				EnemyBulletMng.set(new EnemyBullet02(handle1, m_position[1], RED, speed, angle1 + width * i));
				EnemyBulletMng.set(new EnemyBullet02(handle2, m_position[2], BLUE, speed, angle2 + width * i));
			}
		}
	}
}

void MiniBoss01Easy::barrage03(){
	if(m_cnt % 20 == 0){
		int handle;
		int color;
		float angle = GetRand(1000) * 0.001f;

		if(m_cnt == 0 || m_cnt % 40 == 0){
			handle = ImageMng.get(EB_03R);
			color = RED;
		} else {
			handle = ImageMng.get(EB_03B);
			color = BLUE;
		}

		for(int i = 0; i < 20; ++i){
			float width = static_cast<float>(i) / 20.0f;

			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], color, 4.0f, angle + width));
		}
	}
}

void MiniBoss01Easy::barrage04(){
	if(m_cnt == 0){
		m_barrage04.angle = 0.0f;
		m_barrage04.angleRate = 0.035f;
	}

	if(m_cnt > 80){
		if(m_cnt % 60 <= 10 && m_cnt % 10 == 0){
			float angle = PlayerMng.getAngle(m_position[0]);
			EnemyBulletMng.set(new EnemyBullet01(ImageMng.get(EB_01R), m_position[0], RED, 4.3f, angle));
		}

		if(m_cnt % 6 == 0){
			int handle = ImageMng.get(EB_03B);

			for(int i = 0; i < 2; ++i){
				float angle = static_cast<float>(i) / 2.0f + m_barrage04.angle;

				EnemyBulletMng.set(new EnemyBullet01(handle, m_position[1], BLUE, 4.0f, angle));
				EnemyBulletMng.set(new EnemyBullet01(handle, m_position[2], BLUE, 4.0f, angle));
			}
			m_barrage04.angleRate += 0.0007f;
			m_barrage04.angle += m_barrage04.angleRate;
		}
	}
}

MiniBoss01Normal::MiniBoss01Normal(int imageHandle, Vector& position, float life) :
MiniBoss01(imageHandle, position, life)
{ }

void MiniBoss01Normal::barrage01(){
	if(m_cnt == 0){
		m_barrage01.wayNum = 1;
	}

	if(m_cnt % 60 == 0){{
			float speed = 4.0f;
			float width = 0.008f;
			int handle = ImageMng.get(EB_01R);

			for(int i = 1; i < m_barrage01.wayNum; ++i){
				float angle = getNWayAngle(PlayerMng.getAngle(m_position[0]), width, i);

				for(int j = 0; j < i; ++j){
					EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], RED, speed, angle + width * j));
				}
				speed -= 0.25f;
			}
			for(int i = m_barrage01.wayNum; i > 0; --i){
				float angle = getNWayAngle(PlayerMng.getAngle(m_position[0]), width, i);

				for(int j = 0; j < i; ++j){
					EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], RED, speed, angle + width * j));
				}
				speed -= 0.25f;
			}
			++m_barrage01.wayNum;
		}
	}

	if(m_cnt % 30 == 0){
		float speed = 4.5f;
		float angle1 = getNWayAngle(PlayerMng.getAngle(m_position[1]), 0.04f, 9);
		float angle2 = getNWayAngle(PlayerMng.getAngle(m_position[2]), 0.04f, 9);
		int handle = ImageMng.get(EB_01B);

		for(int i = 0; i < 9; ++i){
			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[1], BLUE, speed, angle1 + 0.04f * i));
			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[2], BLUE, speed, angle2 + 0.04f * i));
		}
	}
}

void MiniBoss01Normal::barrage02(){
	if(m_cnt == 0){
		m_barrage02.wayNum = 3;
		m_barrage02.shotNum = 3;
	}

	if(m_cnt > 90){
		int n = m_cnt % 60;

		if(n == 0){
			++m_barrage02.wayNum;
			++m_barrage02.shotNum;
		}

		if(n < m_barrage02.shotNum * 4 && n % 4 == 0){
			float width = 0.04f;
			float speed = 4.5f;
			float angle1 = getNWayAngle(PlayerMng.getAngle(m_position[1]), width, m_barrage02.wayNum);
			float angle2 = getNWayAngle(PlayerMng.getAngle(m_position[2]), width, m_barrage02.wayNum);
			int handle1 = ImageMng.get(EB_02R);
			int handle2 = ImageMng.get(EB_02B);

			for(int i = 0; i < m_barrage02.wayNum; ++i){
				EnemyBulletMng.set(new EnemyBullet02(handle1, m_position[1], RED, speed, angle1 + width * i));
				EnemyBulletMng.set(new EnemyBullet02(handle2, m_position[2], BLUE, speed, angle2 + width * i));
			}
		}
	}
}

void MiniBoss01Normal::barrage03(){
	if(m_cnt % 15 == 0){
		int handle;
		int color;
		float angle = GetRand(1000) * 0.001f;

		if(m_cnt == 0 || m_cnt % 30 == 0){
			handle = ImageMng.get(EB_03R);
			color = RED;
		} else {
			handle = ImageMng.get(EB_03B);
			color = BLUE;
		}

		for(int i = 0; i < 40; ++i){
			float width = static_cast<float>(i) / 40.0f;

			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], color, 4.2f, angle + width));
		}
	}
}

void MiniBoss01Normal::barrage04(){
	if(m_cnt == 0){
		m_barrage04.angle = 0.0f;
		m_barrage04.angleRate = 0.03f;
	}

	if(m_cnt > 80){
		if(m_cnt % 60 <= 10 && m_cnt % 10 == 0){
			float angle = PlayerMng.getAngle(m_position[0]);
			EnemyBulletMng.set(new EnemyBullet01(ImageMng.get(EB_01R), getVector(m_position[0].x - 10.0f, m_position[0].y), RED, 4.3f, angle));
			EnemyBulletMng.set(new EnemyBullet01(ImageMng.get(EB_01R), getVector(m_position[0].x + 10.0f, m_position[0].y), RED, 4.3f, angle));
		}

		if(m_cnt % 4 == 0){
			int handle = ImageMng.get(EB_03B);

			for(int i = 0; i < 3; ++i){
				float angle = static_cast<float>(i) / 3.0f + m_barrage04.angle;

				EnemyBulletMng.set(new EnemyBullet01(handle, m_position[1], BLUE, 4.0f, angle));
				EnemyBulletMng.set(new EnemyBullet01(handle, m_position[2], BLUE, 4.0f, angle));
			}
			m_barrage04.angleRate += 0.0007f;
			m_barrage04.angle += m_barrage04.angleRate;
		}
	}
}

MiniBoss01Hard::MiniBoss01Hard(int imageHandle, Vector& position, float life) :
MiniBoss01(imageHandle, position, life)
{ }

void MiniBoss01Hard::barrage01(){
	if(m_cnt == 0){
		m_barrage01.wayNum = 2;
	}

	if(m_cnt % 60 == 0){{
			float speed = 4.0f;
			float width = 0.008f;
			int handle = ImageMng.get(EB_01R);

			for(int i = 1; i < m_barrage01.wayNum; ++i){
				float angle = getNWayAngle(PlayerMng.getAngle(m_position[0]), width, i);

				for(int j = 0; j < i; ++j){
					EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], RED, speed, angle + width * j));
				}
				speed -= 0.25f;
			}
			for(int i = m_barrage01.wayNum; i > 0; --i){
				float angle = getNWayAngle(PlayerMng.getAngle(m_position[0]), width, i);

				for(int j = 0; j < i; ++j){
					EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], RED, speed, angle + width * j));
				}
				speed -= 0.25f;
			}
			++m_barrage01.wayNum;
		}
	}

	if(m_cnt % 25 == 0){
		float speed = 4.5f;
		float angle1 = getNWayAngle(PlayerMng.getAngle(m_position[1]), 0.03f, 9);
		float angle2 = getNWayAngle(PlayerMng.getAngle(m_position[2]), 0.03f, 9);
		int handle = ImageMng.get(EB_01B);

		for(int i = 0; i < 9; ++i){
			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[1], BLUE, speed, angle1 + 0.03f * i));
			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[2], BLUE, speed, angle2 + 0.03f * i));
		}
	}
}

void MiniBoss01Hard::barrage02(){
	if(m_cnt == 0){
		m_barrage02.wayNum = 3;
		m_barrage02.shotNum = 4;
	}

	if(m_cnt > 90){
		int n = m_cnt % 60;

		if(n == 0){
			++m_barrage02.wayNum;
			m_barrage02.shotNum += 2;
		}

		if(n < m_barrage02.shotNum * 3 && n % 3 == 0){
			float width = 0.035f;
			float speed = 4.5f;
			float angle1 = getNWayAngle(PlayerMng.getAngle(m_position[1]), width, m_barrage02.wayNum);
			float angle2 = getNWayAngle(PlayerMng.getAngle(m_position[2]), width, m_barrage02.wayNum);
			int handle1 = ImageMng.get(EB_02R);
			int handle2 = ImageMng.get(EB_02B);

			for(int i = 0; i < m_barrage02.wayNum; ++i){
				EnemyBulletMng.set(new EnemyBullet02(handle1, m_position[1], RED, speed, angle1 + width * i));
				EnemyBulletMng.set(new EnemyBullet02(handle2, m_position[2], BLUE, speed, angle2 + width * i));
			}
		}

		n = (m_cnt + 20) % 60;

		if(n < 6 * 3 && n % 3 == 0){
			EnemyBulletMng.set(new EnemyBullet02(ImageMng.get(EB_04Y), m_position[0], YELLOW, 4.0f + n / 3 * 0.6f, PlayerMng.getAngle(m_position[0])));
		}
	}
}

void MiniBoss01Hard::barrage03(){
	if(m_cnt % 15 == 0){
		int handle;
		int color;
		float angle = GetRand(1000) * 0.001f;

		if(m_cnt == 0 || m_cnt % 30 == 0){
			handle = ImageMng.get(EB_03R);
			color = RED;
		} else {
			handle = ImageMng.get(EB_03B);
			color = BLUE;
		}

		for(int i = 0; i < 60; ++i){
			float width = static_cast<float>(i) / 60.0f;

			EnemyBulletMng.set(new EnemyBullet01(handle, m_position[0], color, 4.2f, angle + width));
		}
	}
}

void MiniBoss01Hard::barrage04(){
	if(m_cnt == 0){
		m_barrage04.angle = 0.0f;
		m_barrage04.angleRate = 0.03f;
	}

	if(m_cnt > 90){
		if(m_cnt % 60 < 15 && m_cnt % 5 == 0){
			float angle = PlayerMng.getAngle(m_position[0]);
			EnemyBulletMng.set(new EnemyBullet01(ImageMng.get(EB_01R), getVector(m_position[0].x - 10.0f, m_position[0].y), RED, 4.3f, angle));
			EnemyBulletMng.set(new EnemyBullet01(ImageMng.get(EB_01R), getVector(m_position[0].x + 10.0f, m_position[0].y), RED, 4.3f, angle));
		}

		if(m_cnt % 4 == 0){
			int handle = ImageMng.get(EB_03B);

			for(int i = 0; i < 4; ++i){
				float angle = static_cast<float>(i) / 4.0f + m_barrage04.angle;

				EnemyBulletMng.set(new EnemyBullet01(handle, m_position[1], BLUE, 4.0f, angle));
				EnemyBulletMng.set(new EnemyBullet01(handle, m_position[2], BLUE, 4.0f, angle));
			}
			m_barrage04.angleRate += 0.0005f;
			m_barrage04.angle += m_barrage04.angleRate;
		}
	}
}