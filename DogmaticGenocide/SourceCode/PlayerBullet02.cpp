#include "PlayerBullet02.h"
#include "Effect.h"
#include "ObjectManager.h"

PlayerBullet02::PlayerBullet02(int imageHandle, Vector& position, float power, float speed, float angle) :
PlayerBulletUnit(imageHandle, position, power, true),
speed(speed),
angle(angle)
{
	image.angle = angle;

	hitCircle.resize(1);
	for(int i = 0; i < 1; ++i){
		hitCircle[i].radius = 10.0f;
	}
	adjustHitCircle();
}

void PlayerBullet02::update(){
	move();

	if(isFrameOut(0)){
		needDelete = true;
		collision = false;
	} else {
		if (! needDelete)
		{
			adjustHitCircle();
			collideJudge();
		}
	}
}

void PlayerBullet02::move(){
	const float rad = angle * TWO_PI;

	position.x += cosf(rad) * speed * 0.5f;
	position.y += sinf(rad) * speed * 0.5f;

	if (! needDelete)
	{
		adjustHitCircle();
		collideJudge();
	}

	if (! needDelete)
	{
		position.x += cosf(rad) * speed * 0.5f;
		position.y += sinf(rad) * speed * 0.5f;
	}
}

void PlayerBullet02::adjustHitCircle(){
	const float rad = angle * TWO_PI;

	hitCircle[0].position.x = position.x + cosf(rad);
	hitCircle[0].position.y = position.y + sinf(rad);
}

void PlayerBullet02::explosion(){
	ObjectMng.set(PLAYER_BULLET_EXPLOSION, new BulletExplosion(ImageMng.get(PBE_01), position));
	needDelete = true;
	collision = false;
}

SupporterBullet02::SupporterBullet02(int imageHandle, Vector& position, float power, float speed, float angle) :
PlayerBulletUnit(imageHandle, position, power, true),
m_speed(speed),
m_angle(angle)
{
	image.angle = angle;

	hitCircle.resize(1);
	for(int i = 0; i < 1; ++i){
		hitCircle[i].radius = 5.0f;
	}
	hitCircleUpdate();
}

void SupporterBullet02::update(){
	move();

	if(isFrameOut(0)){
		needDelete = true;
		collision = false;
	} else {
		if (! needDelete)
		{
			hitCircleUpdate();
			collideJudge();
		}
	}
}

void SupporterBullet02::move(){
	const float rad = m_angle * TWO_PI;

	position.x += cosf(rad) * m_speed * 0.5f;
	position.y += sinf(rad) * m_speed * 0.5f;

	if (! needDelete)
	{
		hitCircleUpdate();
		collideJudge();
	}

	if (! needDelete)
	{
		position.x += cosf(rad) * m_speed * 0.5f;
		position.y += sinf(rad) * m_speed * 0.5f;
	}
}

void SupporterBullet02::hitCircleUpdate(){
	hitCircle[0].position = position;
}

void SupporterBullet02::explosion(){
	ObjectMng.set(PLAYER_BULLET_EXPLOSION, new BulletExplosion(ImageMng.get(SBE_01), position));
	needDelete = true;
	collision = false;
}