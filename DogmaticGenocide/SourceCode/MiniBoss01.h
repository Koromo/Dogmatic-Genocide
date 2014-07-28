#pragma once

#include "Enemy.h"
#include "Object.h"

extern const float MINIBOSS01_LIFE;

class MiniBoss01 : public EnemyUnit, public IBoss{
	struct Move01_t{
		float speed;
	};

protected:
	Vector m_position[3];
	void (MiniBoss01::*m_fp_update)();
	Move01_t* m_move01;
	Counter m_cnt;

public:
	MiniBoss01(int imageHandle, Vector& position, float life);
	~MiniBoss01();
	void update();
	float getLife(){ return life; }

protected:
	void adjustHitCircle();
	void adjustPosition();
	void update01();
	void update02();
	void update03();
	void update04();
	void update05();
	void update06();
	virtual void barrage01() = 0;
	virtual void barrage02() = 0;
	virtual void barrage03() = 0;
	virtual void barrage04() = 0;
};

class MiniBoss01Easy : public MiniBoss01{
private:
	struct Barrage01_t{
		int wayNum;
		float width;
	}m_barrage01;

	struct Barrage02_t{
		int wayNum;
		int shotNum;
	}m_barrage02;

	struct Barrage04_t{
		float angle;
		float angleRate;
	}m_barrage04;

public:
	MiniBoss01Easy(int imageHandle, Vector& position, float life);
	void barrage01();
	void barrage02();
	void barrage03();
	void barrage04();
};

class MiniBoss01Normal : public MiniBoss01{
private:
	struct Barrage01_t{
		int wayNum;
	}m_barrage01;

	struct Barrage02_t{
		int wayNum;
		int shotNum;
	}m_barrage02;

	struct Barrage04_t{
		float angle;
		float angleRate;
	}m_barrage04;

public:
	MiniBoss01Normal(int imageHandle, Vector& position, float life);
	void barrage01();
	void barrage02();
	void barrage03();
	void barrage04();
};

class MiniBoss01Hard : public MiniBoss01{
private:
	struct Barrage01_t{
		int wayNum;
	}m_barrage01;

	struct Barrage02_t{
		int wayNum;
		int shotNum;
	}m_barrage02;

	struct Barrage04_t{
		float angle;
		float angleRate;
	}m_barrage04;

public:
	MiniBoss01Hard(int imageHandle, Vector& position, float life);
	void barrage01();
	void barrage02();
	void barrage03();
	void barrage04();
};

inline void createMiniBoss01(int imageHandle, Vector& position, float life, int level){
	switch(level){
	case 1:
		EnemyMng.set(new MiniBoss01Easy(imageHandle, position, life));
		break;
	case 2:
		EnemyMng.set(new MiniBoss01Normal(imageHandle, position, life));
		break;
	case 3:
		EnemyMng.set(new MiniBoss01Hard(imageHandle, position, life));
		break;
	default:
		break;
	}
}