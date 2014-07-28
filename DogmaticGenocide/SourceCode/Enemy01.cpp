#include "Enemy01.h"
#include "EnemyBullet.h"

const float ENEMY01_LIFE = 60.0f;

Enemy01::Enemy01(int imageHandle, Vector& position, float life) :
EnemyUnit(imageHandle, position, life, false),
active(false),
privActive(false)
{
	animetion();
	hitCircle.resize(1);
	hitCircle[0].radius = 10.0f;
	adjustHitCircle();
}

void Enemy01::update(){
	move();
	adjustHitCircle();
	animetion();

	collision = active = isActive();

	if(active){
		shot();
	}

	needDelete = ! isAlive();

	if(life <= 0.0f){
		deathAction();
	}

	privActive = active;
}

void Enemy01::adjustHitCircle(){
	hitCircle[0].position = position;
}

void Enemy01::animetion(){
	image.angle = PlayerMng.getAngle(position) - 0.25f;
}

void Enemy01::deathAction(){
	ScoreMng.addScore(1000);
	createEnergy(ImageMng.get(ENERGY_S), getVector(position.x - 10.0f, position.y - 5.0f), 1);
	createEnergy(ImageMng.get(ENERGY_S), getVector(position.x + 10.0f, position.y), 1);
	ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_01), position));
	PlaySound(SoundMng.get(SE_EXPLOSION01));
}

bool Enemy01::isActive(){
	return ! isFrameOut(0);
}

bool Enemy01::isAlive(){
	return life > 0.0f && ! (privActive && ! active);
}