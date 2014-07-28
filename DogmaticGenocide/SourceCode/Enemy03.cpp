#include "Enemy03.h"
#include "DxLib.h"
#include "ObjectManager.h"
#include "EnemyBullet.h"

const float ENEMY03_LIFE = 200.0f;

Enemy03::Enemy03(int imageHandle, Vector& position, float life) :
EnemyUnit(imageHandle, position, life, false),
active(false),
privActive(false)
{
	hitCircle.resize(1);
	hitCircle[0].radius = 20.0f;
	hitCircleUpdate();
}

void Enemy03::update(){
	move();
	hitCircleUpdate();

	collision = active = isActive();

	if(active){
		shot();
	}

	needDelete = ! isAlive();

	if(life <= 0.0f){
		ScoreMng.addScore(1000);
		PlaySound(SoundMng.get(SE_EXPLOSION02));
		dropItem();
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_01), position));
	}

	privActive = active;
}

void Enemy03::hitCircleUpdate(){
	hitCircle[0].position = position;
}

void Enemy03::dropItem(){
	int handle = ImageMng.get(ENERGY_S);
	createEnergy(handle, getVector(position.x - 20.0f, position.y - 5.0f), 1);
	createEnergy(handle, getVector(position.x + 20.0f, position.y), 1);
	createEnergy(handle, getVector(position.x - 10.0f, position.y + 5.0f), 1);
	createEnergy(handle, getVector(position.x + 10.0f, position.y - 20.0f), 1);
}

bool Enemy03::isActive(){
	return ! isFrameOut(0);
}

bool Enemy03::isAlive(){
	return life > 0.0f && ! (privActive && ! active);
}