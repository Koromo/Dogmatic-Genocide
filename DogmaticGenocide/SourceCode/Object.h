#pragma once

#if(0)
#define DRAW_HIT_CIRCLE
#endif

#include "ImageManager.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include "Image.h"
#include "Common.h"
#include "Counter.h"
#include "ScoreManager.h"
#include "DxLib.h"
#include <vector>

class IPlayer;
class IEnemy;
class IPlayerBullet;
class IEnemyBullet;
class IItem;
class IBoss;

enum ObjectID{
	MAP,
	ITEM,
	ENEMY,
	ENEMY_EXPLOSION,
	PLAYER_BULLET,
	PLAYER_BULLET_EXPLOSION,
	PLAYER,
	PLAYER_EXPLOSION,
	ENEMY_BULLET,
	ENEMY_BULLET_EXPLOSION
};

struct HitCircle{
	Vector position;
	float radius;
};

class IObject{
public:
	virtual ~IObject(){ }
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual bool isNeedDelete() = 0;
};

class ICollideObject{
public:
	virtual ~ICollideObject(){ }
	virtual bool isCollision() = 0;
	virtual const std::vector<HitCircle>& getHitCircle() = 0;
};

class IPlayer : public ICollideObject{
public:
	virtual ~IPlayer(){ }
	virtual const Vector& getPosition() = 0;
	virtual void hitAction(IEnemy* enemy) = 0;
	virtual void hitAction(IEnemyBullet* enemyBullet) = 0;
	virtual void addEnergy(float energy) = 0;
	virtual void addStock() = 0;
	virtual float getEnergy() = 0;
	virtual int getStock() = 0;
	virtual void move() = 0;
};

class IEnemy : public ICollideObject{
public:
	virtual ~IEnemy(){ }
	virtual const Vector& getPosition() = 0;
	virtual void hitAction(IPlayerBullet* playerBullet) = 0;
};

class IEnemyBullet : public ICollideObject{
public:
	virtual ~IEnemyBullet(){ }
	virtual void hitAction(IPlayer* player) = 0;
	virtual void explosion(bool itemCreate) = 0;
	virtual int getColor() = 0;
};

class IPlayerBullet : public ICollideObject{
public:
	virtual ~IPlayerBullet(){ }
	virtual void hitAction(IEnemy* enemy) = 0;
	virtual float getPower() = 0;
	virtual void move() = 0;
};

class IItem : public ICollideObject{
public:
	virtual ~IItem(){ }
	virtual void hitAction(IPlayer* player) = 0;
};

class IBoss{
public:
	virtual ~IBoss(){ }
	virtual float getLife() = 0;
};

class Object : public IObject{
protected:
	Image image;
	Vector position;
	bool needDelete;

public:
	Object(int imageHandle, Vector& position);
	bool isNeedDelete();

protected:
	bool isFrameIn(int n);
	bool isFrameOut(int n);
};

class Collision{
public:
	template<typename TYPE1, typename TYPE2>
	static bool collision(TYPE1* obj1, TYPE2* obj2){
		const std::vector<HitCircle>& hitCircle1 = obj1->getHitCircle();
		const std::vector<HitCircle>& hitCircle2 = obj2->getHitCircle();
		int size1 = hitCircle1.size();
		int size2 = hitCircle2.size();

		for(int i = 0; i < size1; ++i){
			for(int j = 0; j < size2; ++j){
				if(CircleToCircle<float>(hitCircle1[i].position.x, hitCircle1[i].position.y, hitCircle1[i].radius, hitCircle2[j].position.x, hitCircle2[j].position.y, hitCircle2[j].radius)){
					return true;
				}
			}
		}
		return false;
	}
};