#include "Enemy02.h"
#include "Effect.h"

const float ENEMY02_LIFE = 30.0f;

Enemy02::Enemy02(int imageHandle, Vector& position, float life) :
EnemyUnit(imageHandle, position, life, false),
active_(false),
privActive_(false)
{
	hitCircle.resize(1);
	hitCircle[0].radius = 12.0f;
	adjustHitCircle();
}

void Enemy02::update(){
	move();
	image.angle += 0.01f;
	adjustHitCircle();

	if(active_) shot();

	active_ = collision = ! isFrameOut(0);

	if(! active_ && privActive_) needDelete = true;

	if(life <= 0.0f){
		ScoreMng.addScore(1000);
		ObjectMng.set(ENEMY_EXPLOSION, new EnemyExplosion(ImageMng.get(EE_01), position));
		createEnergy(ImageMng.get(ENERGY_S), getVector(position.x - 10.0f, position.y - 5.0f), 1);
		createEnergy(ImageMng.get(ENERGY_S), getVector(position.x + 10.0f, position.y), 1);
		PlaySound(SoundMng.get(SE_EXPLOSION01));
		needDelete = true;
	}

	privActive_ = active_;
}

void Enemy02::adjustHitCircle(){
	hitCircle[0].position = position;
}