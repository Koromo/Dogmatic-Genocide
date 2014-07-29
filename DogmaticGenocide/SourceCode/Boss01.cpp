#include "Boss01.h"
#include "EnemyBullet04.h"
#include "ScoreManager.h"
#include "Game.h"

const float BOSS01_LIFE = 10000.0f;

#define WAIT(n) { for(int i = 0; i < n; ++i) yield(); }

void move01(MoveCoro_t::caller_type& yield){
	const float SPEED = 1.0f;
	Vector aim = getVector(320.0f, 150.0f);
	yield();

	while(true){
		float distance = getDistance(yield.get()->refPosition(0), aim);
		float rad = atan2f(yield.get()->refPosition(0), aim);

		if(distance < SPEED){
			yield.get()->refPosition(0).x += cosf(rad) * distance;
			yield.get()->refPosition(0).y += sinf(rad) * distance;
			break;
		}

		yield.get()->refPosition(0).x += cosf(rad) * SPEED;
		yield.get()->refPosition(0).y += sinf(rad) * SPEED;
		yield();
	}
}

void move02(MoveCoro_t::caller_type& yield){
	const float SPEED = 1.0f;
	Vector aim = getVector(320.0f, 80.0f);
	yield();

	while(true){
		float distance = getDistance(yield.get()->refPosition(0), aim);
		float rad = atan2f(yield.get()->refPosition(0), aim);

		if(distance < SPEED){
			yield.get()->refPosition(0).x += cosf(rad) * distance;
			yield.get()->refPosition(0).y += sinf(rad) * distance;
			break;
		}

		yield.get()->refPosition(0).x += cosf(rad) * SPEED;
		yield.get()->refPosition(0).y += sinf(rad) * SPEED;
		yield();
	}
}

void move03(MoveCoro_t::caller_type& yield){
	Vector pos = getVector(320.0f, 150.0f);
	float cnt = 0.0f;
	const float SPEED = 1.0f;
	Vector aim = getVector(320.0f, 150.0f);
	yield();

	while(true){
		float distance = getDistance(yield.get()->refPosition(0), aim);
		float rad = atan2f(yield.get()->refPosition(0), aim);

		if(distance < SPEED){
			yield.get()->refPosition(0).x += cosf(rad) * distance;
			yield.get()->refPosition(0).y += sinf(rad) * distance;
			break;
		}

		yield.get()->refPosition(0).x += cosf(rad) * SPEED;
		yield.get()->refPosition(0).y += sinf(rad) * SPEED;
		yield();
	}

	WAIT(30);

	while(true){
		yield.get()->refPosition(0).x = pos.x + sinf(cnt) * 80.0f;
		yield.get()->refPosition(0).y = pos.y - fabs(sinf(cnt)) * 40.0f;
		cnt += 0.01f;
		yield();
	}
}

void barrage01Easy(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();

	Vector& pos1 = obj->refPosition(2);
	Vector& pos2 = obj->refPosition(3);

	const int HANDLE = ImageMng.get(EB_02B);
	int num = 3 + loop;
	yield();
	
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < num; ++j){
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos1, BLUE, 4.0f, PlayerMng.getAngle(pos1)));
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos2, BLUE, 4.0f, PlayerMng.getAngle(pos2)));
			WAIT(3);
		}
		++num;
		WAIT(45 - loop * 5);
	}
}

void barrage01Normal01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();

	Vector& pos1 = obj->refPosition(2);
	Vector& pos2 = obj->refPosition(3);

	const int HANDLE = ImageMng.get(EB_02B);
	int num = 5 + loop;
	yield();
	
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < num; ++j){
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos1, BLUE, 4.0f, PlayerMng.getAngle(pos1)));
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos2, BLUE, 4.0f, PlayerMng.getAngle(pos2)));
			WAIT(3);
		}
		++num;
		WAIT(45 - loop * 5);
	}
}

void barrage01Normal02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();

	Vector& pos = obj->refPosition(1);

	const int HANDLE = ImageMng.get(EB_01R);
	const int WAY = 9 + loop;
	const float WIDTH = 0.04f - 0.008f * loop;
	yield();

	for(int i = 0; i < 9; ++i){
		float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, WAY) + GetRand(1600) * 0.0001f - 0.08f;
		for(int j = 0; j < WAY; ++j){
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 3.5f, angle + WIDTH * j));
		}
		WAIT(20);
	}
}

void barrage01Normal(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t barrage01(barrage01Normal01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t barrage02(barrage01Normal02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(barrage01) barrage01(obj, loop);
		if(barrage02) barrage02(obj, loop);
		yield();
	}
}

void barrage01Hard01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(2);
	const int HANDLE = ImageMng.get(EB_02B);
	const int NUM = 4;
	const int CONTINUE_INTERVAL = 2;
	const int INTERVAL = 10 - loop * 2;
	yield();
	
	while(true){
		for(int i = 0; i < NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos, BLUE, 4.4f, PlayerMng.getAngle(pos)));
			WAIT(CONTINUE_INTERVAL);
		}
		WAIT(INTERVAL);
	}
}

void barrage01Hard02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(3);
	const int HANDLE = ImageMng.get(EB_02B);
	const int NUM = 4;
	const int CONTINUE_INTERVAL = 2;
	const int INTERVAL = 10 - loop * 2;
	yield();
	
	WAIT(15);
	while(true){
		for(int i = 0; i < NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos, BLUE, 4.4f, PlayerMng.getAngle(pos)));
			WAIT(CONTINUE_INTERVAL);
		}
		WAIT(INTERVAL);
	}
}

void barrage01Hard03(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	const int HANDLE = ImageMng.get(EB_01R);
	const int WAY1 = 9;
	const float WIDTH1 = 0.05f;
	const int WAY2 = 4;
	const float WIDTH2 = 0.006f;
	yield();

	while(true){
		float angle1 = getNWayAngle(PlayerMng.getAngle(pos), WIDTH1, WAY1) + GetRand(1600) * 0.0001f - 0.08f;
		for(int i = 0; i < WAY1; ++i){
			float angle2 = getNWayAngle(angle1 + WIDTH1 * i, WIDTH2, WAY2);
			for(int j = 0; j < WAY2; ++j){
				EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 3.8f, angle2 + WIDTH2 * j));
			}
		}
		WAIT(20 - loop * 3);
	}
}

void barrage01Hard(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t barrage01(barrage01Hard01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t barrage02(barrage01Hard02, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t barrage03(barrage01Hard03, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(barrage01) barrage01(obj, loop);
		if(barrage02) barrage02(obj, loop);
		if(barrage03) barrage03(obj, loop);
		yield();
	}
}

void barrage02Easy(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	const int HANDLE_YELLOW = ImageMng.get(EB_04Y);
	const int HANDLE_RED = ImageMng.get(EB_04R);
	const float WIDTH = 0.05f - loop * 0.008f;
	const float WAY_NUM = 8 + loop * 2;
	float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, WAY_NUM);
	yield();

	for(int i = 0; i < WAY_NUM; ++i){
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_YELLOW, pos, YELLOW, 4.0f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_RED, pos, RED, 3.5f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_RED, pos, RED, 3.0f, angle + GetRand(1000) * 0.0001f - 0.05f));
		angle += WIDTH;
		WAIT(3);
	}
}

void barrage02Normal(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	const int HANDLE_YELLOW = ImageMng.get(EB_04Y);
	const int HANDLE_RED = ImageMng.get(EB_04R);
	const float WIDTH = 0.05f - loop * 0.008f;
	const float WAY_NUM = 8 + loop * 2;
	float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, WAY_NUM);
	yield();

	for(int i = 0; i < WAY_NUM * 3; ++i){
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_YELLOW, pos, YELLOW, 4.2f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_YELLOW, pos, YELLOW, 4.0f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_RED, pos, RED, 3.7f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_RED, pos, RED, 3.5f, angle + GetRand(1000) * 0.0001f - 0.05f));

		int n = i / WAY_NUM;
		angle += n % 2 ? -WIDTH : WIDTH;
		WAIT(3);
	}
}

void barrage02Hard(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	const int HANDLE_YELLOW = ImageMng.get(EB_04Y);
	const int HANDLE_RED = ImageMng.get(EB_04R);
	const int HANDLE_BLUE = ImageMng.get(EB_04B);
	const float WIDTH = 0.04f - loop * 0.008f;
	const float WAY_NUM = 10 + loop * 2;
	float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, WAY_NUM);
	yield();

	for(int i = 0; i < WAY_NUM * 3; ++i){
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_YELLOW, pos, YELLOW, 4.6f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_YELLOW, pos, YELLOW, 4.4f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_BLUE, pos, BLUE, 4.2f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_BLUE, pos, BLUE, 4.0f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_RED, pos, RED, 3.8f, angle + GetRand(1000) * 0.0001f - 0.05f));
		EnemyBulletMng.set(new EnemyBullet02(HANDLE_RED, pos, RED, 3.6f, angle + GetRand(1000) * 0.0001f - 0.05f));

		int n = i / WAY_NUM;
		angle += n % 2 ? -WIDTH : WIDTH;
		WAIT(3);
	}
}

void barrage03Easy01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(2);
	const int HANDLE = ImageMng.get(EB_01R);
	const float WIDTH = 0.03f;
	const int WAY_NUM = 7;
	yield();

	while(true){
		float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, WAY_NUM) + GetRand(800) * 0.0001f - 0.04f;
		for(int i = 0; i < WAY_NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 4.0f, angle + WIDTH * i));
			WAIT(3);
		}
		WAIT(30 - loop * 5);
	}
}

void barrage03Easy02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(3);
	const int HANDLE = ImageMng.get(EB_01B);
	const float WIDTH = 0.03f;
	const int WAY_NUM = 7;
	yield();

	WAIT(20);
	while(true){
		float angle = getNWayAngle(PlayerMng.getAngle(pos), -WIDTH, WAY_NUM) + GetRand(800) * 0.0001f - 0.04f;
		for(int i = 0; i < WAY_NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, 4.0f, angle - WIDTH * i));
			WAIT(3);
		}
		WAIT(30 - loop * 5);
	}
}

void barrage03Easy(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t colo1 = BarrageCoro_t(barrage03Easy01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t colo2 = BarrageCoro_t(barrage03Easy02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(colo1) colo1(obj, loop);
		if(colo2) colo2(obj, loop);
		yield();
	}
}

void barrage03Normal01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(2);
	const int HANDLE = ImageMng.get(EB_01R);
	const float WIDTH = 0.02f;
	const int WAY_NUM = 9;
	yield();

	while(true){
		float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, WAY_NUM) + GetRand(800) * 0.0001f - 0.04f;
		for(int i = 0; i < WAY_NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 4.2f - 0.1f * i, angle + WIDTH * i));
			WAIT(3);
		}
		WAIT(15 - loop * 3);
	}
}

void barrage03Normal02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(3);
	const int HANDLE = ImageMng.get(EB_01B);
	const float WIDTH = 0.02f;
	const int WAY_NUM = 9;
	yield();

	WAIT(10);
	while(true){
		float angle = getNWayAngle(PlayerMng.getAngle(pos), -WIDTH, WAY_NUM) + GetRand(800) * 0.0001f - 0.04f;
		for(int i = 0; i < WAY_NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, 4.2f - 0.1f * i, angle - WIDTH * i));
			WAIT(3);
		}
		WAIT(15 - loop * 3);
	}
}

void barrage03Normal(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t colo1 = BarrageCoro_t(barrage03Normal01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t colo2 = BarrageCoro_t(barrage03Normal02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(colo1) colo1(obj, loop);
		if(colo2) colo2(obj, loop);
		yield();
	}
}

void barrage03Hard01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(2);
	const int HANDLE = ImageMng.get(EB_01R);
	const float WIDTH = 0.015f;
	const int WAY_NUM = 11;
	yield();

	while(true){
		float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, WAY_NUM) + GetRand(800) * 0.0001f - 0.04f;
		for(int i = 0; i < WAY_NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 4.2f - 0.1f * i, angle + WIDTH * i));
			WAIT(3);
		}
		WAIT(10 - loop * 2);
	}
}

void barrage03Hard02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(3);
	const int HANDLE = ImageMng.get(EB_01B);
	const float WIDTH = 0.015f;
	const int WAY_NUM = 11;
	yield();

	WAIT(10);
	while(true){
		float angle = getNWayAngle(PlayerMng.getAngle(pos), -WIDTH, WAY_NUM) + GetRand(800) * 0.0001f - 0.04f;
		for(int i = 0; i < WAY_NUM; ++i){
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, 4.2f - 0.1f * i, angle - WIDTH * i));
			WAIT(3);
		}
		WAIT(10 - loop * 2);
	}
}

void barrage03Hard(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t colo1 = BarrageCoro_t(barrage03Hard01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t colo2 = BarrageCoro_t(barrage03Hard02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(colo1) colo1(obj, loop);
		if(colo2) colo2(obj, loop);
		yield();
	}
}

void barrage04Easy01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;

	boost::tie(obj, loop) = yield.get();

	Vector& pos = obj->refPosition(1);
	int HANDLE = ImageMng.get(EB_01R);
	int SHOT_NUM1 = 4 + loop;
	int SHOT_NUM2 = 7 + loop;
	float WIDTH = 0.03f - loop * 0.0015f;
	int INTERVAL = 70 - loop * 5; 
	yield();

	while(true){
		WAIT(INTERVAL);

		float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, SHOT_NUM1) + getRandamAngle(0.05f, 100);
		float angle2 = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, SHOT_NUM2) + getRandamAngle(0.05f, 100);

		for (int i = 0; i < SHOT_NUM1; ++i)
		{
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 4.0f, angle + WIDTH * i));
		}
		for (int i = 0; i < SHOT_NUM2; ++i)
		{
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 2.5f, angle2 + WIDTH * i));
		}
	}
}

void barrage04Easy02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	int HANDLE = ImageMng.get(EB_01B);
	int INTERVAL = 70 - loop * 5;
	yield();

	while(true){
		WAIT(INTERVAL);

		float angle = PlayerMng.getAngle(pos) + getRandamAngle(0.05f, 100);

		for (int i = 0; i < 5; ++i)
		{
			float speed = 3.0 + 0.5f * i;

			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, speed, angle));

			WAIT(2);
		}
	}
}

void barrage04Easy(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t colo1 = BarrageCoro_t(barrage04Easy01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t colo2 = BarrageCoro_t(barrage04Easy02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(colo1) colo1(obj, loop);
		if(colo2) colo2(obj, loop);
		yield();
	}
}

void barrage04Normal01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;

	boost::tie(obj, loop) = yield.get();

	Vector& pos = obj->refPosition(1);
	int HANDLE = ImageMng.get(EB_01R);
	int SHOT_NUM1 = 6 + loop;
	int SHOT_NUM2 = 11 + loop;
	float WIDTH = 0.025f - loop * 0.0015f;
	int INTERVAL = 65 - loop * 5; 
	yield();

	while(true){
		WAIT(INTERVAL);

		float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, SHOT_NUM1) + getRandamAngle(0.05f, 100);
		float angle2 = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, SHOT_NUM2) + getRandamAngle(0.05f, 100);

		for (int i = 0; i < SHOT_NUM1; ++i)
		{
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 4.0f, angle + WIDTH * i));
		}
		for (int i = 0; i < SHOT_NUM2; ++i)
		{
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 2.5f, angle2 + WIDTH * i));
		}
	}
}

void barrage04Normal02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	int HANDLE = ImageMng.get(EB_01B);
	int INTERVAL = 65 - loop * 5;
	yield();

	while(true){
		WAIT(INTERVAL);

		float angle = PlayerMng.getAngle(pos) + getRandamAngle(0.05f, 100);

		for (int i = 0; i < 6; ++i)
		{
			float speed = 2.5 + 0.5f * i;

			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, speed, angle - 0.0025f * i));
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, speed, angle + 0.0025f * i));

			WAIT(2);
		}
	}
}

void barrage04Normal(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t colo1 = BarrageCoro_t(barrage04Normal01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t colo2 = BarrageCoro_t(barrage04Normal02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(colo1) colo1(obj, loop);
		if(colo2) colo2(obj, loop);
		yield();
	}
}

void barrage04Hard01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;

	boost::tie(obj, loop) = yield.get();

	Vector& pos = obj->refPosition(1);
	int HANDLE = ImageMng.get(EB_01R);
	int SHOT_NUM1 = 8 + loop;
	int SHOT_NUM2 = 13 + loop;
	float WIDTH = 0.02f - loop * 0.0015f;
	int INTERVAL = 60 - loop * 5; 
	yield();

	while(true){
		WAIT(INTERVAL);

		float angle = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, SHOT_NUM1) + getRandamAngle(0.05f, 100);
		float angle2 = getNWayAngle(PlayerMng.getAngle(pos), WIDTH, SHOT_NUM2) + getRandamAngle(0.05f, 100);

		for (int i = 0; i < SHOT_NUM1; ++i)
		{
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 4.0f, angle + WIDTH * i));
		}
		for (int i = 0; i < SHOT_NUM2; ++i)
		{
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, RED, 2.5f, angle2 + WIDTH * i));
		}
	}
}

void barrage04Hard02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	int HANDLE = ImageMng.get(EB_01B);
	int INTERVAL = 60 - loop * 5;
	yield();

	while(true){
		WAIT(INTERVAL);

		float angle = PlayerMng.getAngle(pos) + getRandamAngle(0.05f, 100);

		for (int i = 0; i < 8; ++i)
		{
			float speed = 2.5 + 0.5f * i;

			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, speed, angle - 0.003f * i));
			EnemyBulletMng.set(new EnemyBullet01(HANDLE, pos, BLUE, speed, angle + 0.003f * i));

			WAIT(2);
		}
	}
}

void barrage04Hard(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	BarrageCoro_t colo1 = BarrageCoro_t(barrage04Hard01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t colo2 = BarrageCoro_t(barrage04Hard02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(colo1) colo1(obj, loop);
		if(colo2) colo2(obj, loop);
		yield();
	}
}

void barrage05Easy01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	const int SHOT_INTERVAL = 2;
	int HANDLE = ImageMng.get(EB_01R);
	float angle = -0.2f;
	int continueNum = 5;
	loop = 0;
	int loopCnt = 0;
	yield();

	WAIT(30);

	while(true){
		if (loop > 5) loop = 5;

		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 10; ++j){
				EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
				angle += 0.03f;
				WAIT(SHOT_INTERVAL);
			}

			angle += 0.16f;
			WAIT(30 - loop);
		}

		WAIT(45 - loop * 2);

		for(int i = 0; i < 5; ++i){
			for(int j = 0; j < 5; ++j){
				EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
				angle += 0.02f;
				WAIT(SHOT_INTERVAL);
			}

			angle += 0.08f;
			WAIT(20 - static_cast<int>(loop / 2));
		}

		WAIT(45 - loop * 2);

		for(int i = 0; i < 25; ++i){
			EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
			angle += 0.02f;
			WAIT(SHOT_INTERVAL);
		}

		WAIT(60 - loop * 5);

		if (loopCnt++ % 1 == 0)
		{
			++loop;
		}
	}
}

void barrage05Easy02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& p1 = obj->refPosition(2);
	Vector& p2 = obj->refPosition(3);
	int HANDLE = ImageMng.get(EB_02B);
	int INTERVAL = 80;
	int SHOT_INTERVAL = 2;
	int SHOT_NUM = 5;

	//auto lambda = [&]()
	//{
	//	for (int i = 0; i < 1; ++i)
	//	{
	//		pos1[i] = getVector(p1.x + static_cast<float>(GetRand(50)) - 25.0f, p1.y + static_cast<float>(GetRand(30)) - 15.0f);
	//		pos2[i] = getVector(p2.x + static_cast<float>(GetRand(50)) - 25.0f, p2.y + static_cast<float>(GetRand(30)) - 15.0f);
	//	}
	//};

	yield();

	while (true)
	{
		WAIT(INTERVAL);

		//lambda();

		Vector pos1 = p1;
		Vector pos2 = p2;

		for (int i = 0; i < SHOT_NUM; ++i)
		{
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos1, BLUE, 5.0f, PlayerMng.getAngle(pos1)));
			EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos2, BLUE, 5.0f, PlayerMng.getAngle(pos2)));

			WAIT(SHOT_INTERVAL);
		}

		SHOT_NUM += 1;

		if (SHOT_NUM > 10) SHOT_NUM = 10;
	}
}

void barrage05Easy(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop)  = yield.get();
	BarrageCoro_t coro1 = BarrageCoro_t(barrage05Easy01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t coro2 = BarrageCoro_t(barrage05Easy02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(coro1) coro1(obj, loop);
		if(coro2) coro2(obj, loop);
		yield();
	}
}

void barrage05Normal01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	const int SHOT_INTERVAL = 2;
	int HANDLE = ImageMng.get(EB_01R);
	float angle = -0.2f;
	int continueNum = 5;
	loop = 0;
	int loopCnt = 0;
	yield();

	WAIT(30);

	while(true){
		if (loop > 5) loop = 5;

		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 10; ++j){
				EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
				angle += 0.03f;
				WAIT(SHOT_INTERVAL);
			}

			angle += 0.16f;
			WAIT(10 - loop);
		}

		WAIT(30 - loop * 2);

		for(int i = 0; i < 5; ++i){
			for(int j = 0; j < 5; ++j){
				EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
				angle += 0.02f;
				WAIT(SHOT_INTERVAL);
			}

			angle += 0.08f;
			WAIT(5 - static_cast<int>(loop / 2));
		}

		WAIT(30 - loop * 2);

		for(int i = 0; i < 50; ++i){
			EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
			angle += 0.02f;
			WAIT(SHOT_INTERVAL);
		}

		WAIT(45 - loop * 5);

		if (loopCnt++ % 1 == 0)
		{
			++loop;
		}
	}
}

void barrage05Normal02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& p1 = obj->refPosition(2);
	Vector& p2 = obj->refPosition(3);
	int HANDLE = ImageMng.get(EB_02B);
	int INTERVAL = 70;
	int SHOT_INTERVAL = 2;
	int SHOT_NUM = 8;

	//auto lambda = [&]()
	//{
	//	for (int i = 0; i < 15; ++i)
	//	{
	//		pos1[i] = getVector(p1.x + static_cast<float>(GetRand(50)) - 25.0f, p1.y + static_cast<float>(GetRand(30)) - 15.0f);
	//		pos2[i] = getVector(p2.x + static_cast<float>(GetRand(50)) - 25.0f, p2.y + static_cast<float>(GetRand(30)) - 15.0f);
	//	}
	//};

	yield();

	while (true)
	{
		WAIT(INTERVAL);

	//	lambda();

		Vector pos1[2] = {getVector(p1.x - 10.0f, p1.y), getVector(p1.x + 10.0f, p2.y)};
		Vector pos2[2] = {getVector(p2.x - 10.0f, p1.y), getVector(p2.x + 10.0f, p2.y)};

		for (int i = 0; i < SHOT_NUM; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos1[j], BLUE, 5.0f, PlayerMng.getAngle(pos1[j]) + getRandamAngle(0.05f, 20)));
				EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos2[j], BLUE, 5.0f, PlayerMng.getAngle(pos2[j]) + getRandamAngle(0.05f, 20)));
			}

			WAIT(SHOT_INTERVAL);
		}

		SHOT_NUM += 1;

		if (SHOT_NUM > 14) SHOT_NUM = 14;
	}
}

void barrage05Normal(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop)  = yield.get();
	BarrageCoro_t coro1 = BarrageCoro_t(barrage05Normal01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t coro2 = BarrageCoro_t(barrage05Normal02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(coro1) coro1(obj, loop);
		if(coro2) coro2(obj, loop);
		yield();
	}
}

void barrage05Hard01(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& pos = obj->refPosition(1);
	const int SHOT_INTERVAL = 2;
	int HANDLE = ImageMng.get(EB_01R);
	float angle = -0.2f;
	int continueNum = 5;
	loop = 0;
	int loopCnt = 0;
	yield();

	WAIT(30);

	while(true){
		if (loop > 5) loop = 5;

		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 10; ++j){
				EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
				angle += 0.03f;
				WAIT(SHOT_INTERVAL);
			}

			angle += 0.16f;
			WAIT(8 - loop);
		}

		WAIT(25 - loop * 2);

		for(int i = 0; i < 5; ++i){
			for(int j = 0; j < 5; ++j){
				EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
				angle += 0.02f;
				WAIT(SHOT_INTERVAL);
			}

			angle += 0.08f;
			WAIT(4 - static_cast<int>(loop / 2));
		}

		WAIT(25 - loop * 2);

		for(int i = 0; i < 50; ++i){
			EnemyBulletMng.set(new EnemyBullet04(HANDLE, pos, RED, 4.3f, angle, PlayerMng.getAngle(pos), 20));
			angle += 0.02f;
			WAIT(SHOT_INTERVAL);
		}

		WAIT(40 - loop * 5);

		if (loopCnt++ % 1 == 0)
		{
			++loop;
		}
	}
}

void barrage05Hard02(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop) = yield.get();
	Vector& p1 = obj->refPosition(2);
	Vector& p2 = obj->refPosition(3);
	int HANDLE = ImageMng.get(EB_02B);
	int INTERVAL = 60;
	int SHOT_INTERVAL = 1;
	int SHOT_NUM = 12;

	//auto lambda = [&]()
	//{
	//	for (int i = 0; i < 20; ++i)
	//	{
	//		pos1[i] = getVector(p1.x + static_cast<float>(GetRand(50)) - 25.0f, p1.y + static_cast<float>(GetRand(30)) - 15.0f);
	//		pos2[i] = getVector(p2.x + static_cast<float>(GetRand(50)) - 25.0f, p2.y + static_cast<float>(GetRand(30)) - 15.0f);
	//	}
	//};

	yield();

	while (true)
	{
		WAIT(INTERVAL);

		//lambda();

		Vector pos1[3];
		Vector pos2[3];

		pos1[0] = getVector(p1.x - 20.0f, p1.y);
		pos2[0] = getVector(p2.x - 20.0f, p2.y);
		pos1[1] = getVector(p1.x, p1.y - 15.0f);
		pos2[1] = getVector(p2.x, p2.y - 15.0f);
		pos1[2] = getVector(p1.x + 20.0f, p1.y);
		pos2[2] = getVector(p2.x + 20.0f, p2.y);

		for (int i = 0; i < SHOT_NUM; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos1[j], BLUE, 5.0f, PlayerMng.getAngle(pos1[j]) + getRandamAngle(0.1f, 20)));
				EnemyBulletMng.set(new EnemyBullet02(HANDLE, pos2[j], BLUE, 5.0f, PlayerMng.getAngle(pos2[j]) + getRandamAngle(0.1f, 20)));
			}

			WAIT(SHOT_INTERVAL);
		}

		SHOT_NUM += 1;

		if (SHOT_NUM > 16) SHOT_NUM = 16;
	}
}

void barrage05Hard(BarrageCoro_t::caller_type& yield){
	Boss01* obj;
	int loop;
	boost::tie(obj, loop)  = yield.get();
	BarrageCoro_t coro1 = BarrageCoro_t(barrage05Hard01, BarrageCoro_t::arguments(obj, loop));
	BarrageCoro_t coro2 = BarrageCoro_t(barrage05Hard02, BarrageCoro_t::arguments(obj, loop));
	yield();

	while(true){
		if(coro1) coro1(obj, loop);
		if(coro2) coro2(obj, loop);
		yield();
	}
}

Boss01::Boss01(int imageHandle, Vector& position, float life, int level) :
EnemyUnit(imageHandle, position, life, false),
fp_update_(&Boss01::update01),
level_(level),
move_(MoveCoro_t(move01))
{
	hitCircle.resize(1);
	hitCircle[0].radius = 35.0f;
	adjustHitCircle();
	adjustPosition();
}

Boss01::~Boss01(){
	EnemyMng.setAlive(false);
	Game::setFinish(true);
}

void Boss01::update(){
	(this->*fp_update_)();
	adjustHitCircle();
	adjustPosition();
	EnemyMng.update(this);

	if(life <= 0.0f && fp_update_ != &Boss01::update07){
		EnemyBulletMng.explosion(false);
		fp_update_ = &Boss01::update07;
		cnt_ = 0;
		collision = false;
	}
}

void Boss01::adjustHitCircle(){
	hitCircle[0].position = position;
}

void Boss01::adjustPosition(){
	position_[0] = position;
	position_[1] = getVector(position.x + 30.0f, position.y - 5.0f);
	position_[2] = getVector(position.x - 30.0f, position.y - 5.0f);
}

void Boss01::update01(){
	if(move_) move_(this);

	if(! move_){
		fp_update_ = &Boss01::update02;
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage01Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage01Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage01Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -45;
		collision = true;
	}
}

void Boss01::update02(){
	if(move_) move_(this);
	if(cnt_++ >= 0 && barrage_) barrage_(this, loop_);

	if(cnt_ >= 180){
		fp_update_ = &Boss01::update03;
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage02Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage02Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage02Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -45;
		return;
	}

	if(life <= 2500){
		EnemyBulletMng.explosion(false);
		fp_update_ = &Boss01::update06;
		move_.swap(MoveCoro_t(move01, this));
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage05Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage05Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage05Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -90;
		return;
	}
}

void Boss01::update03(){
	if(cnt_++ >= 0 && barrage_) barrage_(this, loop_);

	if(cnt_ >= 200){
		fp_update_ = &Boss01::update04;
		move_.swap(MoveCoro_t(move02, this));
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage03Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage03Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage03Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -60;
		return;
	}

	if(life <= 2500){
		EnemyBulletMng.explosion(false);
		fp_update_ = &Boss01::update06;
		move_.swap(MoveCoro_t(move01, this));
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage05Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage05Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage05Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -90;
		return;
	}
}

void Boss01::update04(){
	if(move_) move_(this);
	if(cnt_++ >= 0 && barrage_) barrage_(this, loop_);

	if(cnt_ >= 300){
		fp_update_ = &Boss01::update05;
		move_.swap(MoveCoro_t(move03, this));
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage04Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage04Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage04Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -90;
		return;
	}

	if(life <= 2500){
		EnemyBulletMng.explosion(false);
		fp_update_ = &Boss01::update06;
		move_.swap(MoveCoro_t(move01, this));
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage05Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage05Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage05Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -90;
		return;
	}
}

void Boss01::update05(){
	if(move_) move_(this);
	if(cnt_++ >= 0 && barrage_) barrage_(this, loop_);

	if(cnt_ >= 1000){
		++loop_;
		if(loop_ > 2) loop_ = 2;
		fp_update_ = &Boss01::update02;
		move_.swap(MoveCoro_t(move01, this));
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage01Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage01Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage01Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -90;
		return;
	}

	if(life <= 2500){
		EnemyBulletMng.explosion(false);
		fp_update_ = &Boss01::update06;
		move_.swap(MoveCoro_t(move01, this));
		switch(level_){
		case 1:
			barrage_.swap(BarrageCoro_t(barrage05Easy, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 2:
			barrage_.swap(BarrageCoro_t(barrage05Normal, BarrageCoro_t::arguments(this, loop_)));
			break;
		case 3:
			barrage_.swap(BarrageCoro_t(barrage05Hard, BarrageCoro_t::arguments(this, loop_)));
			break;
		}
		cnt_ = -90;
		return;
	}
}

void Boss01::update06(){
	if(move_) move_(this);
	if(cnt_++ >= 0 && barrage_) barrage_(this, loop_);
}

void Boss01::update07()
{
	if (cnt_ < 180)
	{
		if (cnt_ % 20 == 0)
		{
			ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_01), getVector(position.x + getRandamF(100.0f, 100), position.y + getRandamF(100.0f, 100))));
			PlaySound(SoundMng.get(SE_EXPLOSION01));
		}
	}

	if (cnt_ == 240)
	{
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_02), getVector(position.x + getRandamF(100.0f, 100), position.y + getRandamF(100.0f, 100))));
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_02), getVector(position.x + getRandamF(100.0f, 100), position.y + getRandamF(100.0f, 100))));
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_02), getVector(position.x + getRandamF(100.0f, 100), position.y + getRandamF(100.0f, 100))));
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_02), getVector(position.x + getRandamF(100.0f, 100), position.y + getRandamF(100.0f, 100))));
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_02), getVector(position.x + getRandamF(100.0f, 100), position.y + getRandamF(100.0f, 100))));
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_02), getVector(position.x + getRandamF(100.0f, 100), position.y + getRandamF(100.0f, 100))));
		ScoreMng.addScore(20000);
		PlaySound(SoundMng.get(SE_EXPLOSION03));
		needDelete = true;
	}

	++cnt_;
}