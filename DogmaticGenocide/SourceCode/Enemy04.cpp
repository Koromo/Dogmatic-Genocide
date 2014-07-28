#include "Enemy04.h"
#include "DxLib.h"
#include "ObjectManager.h"
#include "EnemyBullet.h"

const float ENEMY04_LIFE = 250.0f;

Enemy04::Enemy04(int imageHandle, Vector& position, float life) :
EnemyUnit(imageHandle, position, life, false),
active(false),
privActive(false)
{
	hitCircle.resize(1);
	hitCircle[0].radius = 20.0f;
	hitCircleUpdate();
}

void Enemy04::update(){
	move();
	hitCircleUpdate();

	collision = active = isActive();

	if(active){
		shot();
	}

	needDelete = ! isAlive();

	if(life <= 0.0f){
		EnemyBulletMng.explosion(true);
		PlaySound(SoundMng.get(SE_EXPLOSION02));
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_01), position));
		ScoreMng.addScore(1000);
		dropItem();
	}

	privActive = active;
}

void Enemy04::hitCircleUpdate(){
	hitCircle[0].position = position;
}

void Enemy04::dropItem(){
	int handle = ImageMng.get(ENERGY_S);
	createEnergy(handle, getVector(position.x - 20.0f, position.y - 5.0f), 1);
	createEnergy(handle, getVector(position.x + 20.0f, position.y), 1);
	createEnergy(handle, getVector(position.x - 10.0f, position.y + 5.0f), 1);
	createEnergy(handle, getVector(position.x + 10.0f, position.y - 20.0f), 1);
}

bool Enemy04::isActive(){
	return ! isFrameOut(0);
}

bool Enemy04::isAlive(){
	return life > 0.0f && ! (privActive && ! active);
}