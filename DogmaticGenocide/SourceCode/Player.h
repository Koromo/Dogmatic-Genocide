#pragma once

#include "Object.h"
#include "ObjectManager.h"
#include "DeviceManager.h"

class Player01Supporter{
private:
	Image m_image;
	Vector m_position;
	float m_angle;

public:
	Player01Supporter(int imageHandle, Vector& position);
	void setPosition(Vector& position){ m_position = position; }
	void setAngle(float angle){ m_image.angle = m_angle = angle; }
	void draw();
	void normalFire(float speed, float power);
	void boostFire(float speed, float power);
};

class Player02Supporter{
private:
	Image m_image;
	Vector m_position;
	float m_angle;

public:
	Player02Supporter(int imageHandle, Vector& position);
	void setPosition(Vector& position){ m_position = position; }
	void setAngle(float angle){ m_image.angle = m_angle = angle; }
	void draw();
	void normalFire(float speed, float power);
	void boostFire(float speed, float power);
};

class PlayerUnit : public Object, public IPlayer{
protected:
	bool collision;
	std::vector<HitCircle> hitCircle;
	float speed;
	float energy;
	int stock;
	IDevice* device;
	bool boost;
	Counter boostCnt;
	Counter cnt;
	Counter drawCnt;
	Counter animeCnt;
	Counter m_bcnt;
	Vector m_move;

public:
	PlayerUnit(int imageHandle, Vector& position, float radius, float speed, float energy, int stock, bool collision, IDevice* device);
	~PlayerUnit(){ EnemyBulletMng.setCreate(false); }
	void update();
	void draw();
	bool isCollision();
	const std::vector<HitCircle>& getHitCircle();
	void hitAction(IEnemy* enemy);
	void hitAction(IEnemyBullet* enemyBullet);
	void addEnergy(float energy);
	const Vector& getPosition();
	void addStock();
	float getEnergy();
	int getStock();
	void move();

protected:
	void exchangeBoost();
	void hitCircleUpdate();
	void collideJudge();
	void animetion();
	virtual void normalShot() = 0;
	virtual void boostShot() = 0;
	virtual void explosion() = 0;
};

class Player_1 : public PlayerUnit{
private:
	Counter shotCnt;
	Player01Supporter* supporter[2];

public:
	Player_1(int imageHandle, Vector& position, float energy, int stock, IDevice* device);
	~Player_1(){
		for(int i = 0; i < 2; ++i){
			delete supporter[i];
			supporter[i] = nullptr;
		}
	}
	void draw(){
		PlayerUnit::draw();
		for(int i = 0; i < 2; ++i){
			supporter[i]->draw();
		}
	}

protected:
	void move();
	void normalShot();
	void boostShot();
	void explosion();
	void adjustSupporterPosition();
};

class Player_2 : public PlayerUnit{
private:
	Counter shotCnt;
	Player02Supporter* supporter[4];

public:
	Player_2(int imageHandle, Vector& position, float energy, int stock, IDevice* device);
	~Player_2(){
		for(int i = 0; i < 4; ++i){
			delete supporter[i];
			supporter[i] = nullptr;
		}
	}
	void draw(){
		PlayerUnit::draw();
		for(int i = 0; i < 4; ++i){
			supporter[i]->draw();
		}
	}
protected:
	void move();
	void normalShot();
	void boostShot();
	void explosion();
	void adjustSupporterPosition();
};