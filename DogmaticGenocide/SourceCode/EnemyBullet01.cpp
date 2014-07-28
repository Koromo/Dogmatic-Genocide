#include "EnemyBullet01.h"

EnemyBullet01::EnemyBullet01(int imageHandle, Vector& position, int color, float speed, float angle) :
EnemyBulletUnit(imageHandle, position, color, speed, angle, true)
{
	image.angle = angle;
	hitCircle.resize(1);
	hitCircle[0].position = position;
	hitCircle[0].radius = 3.0f;
}

void EnemyBullet01::update(){
	const float rad = angle * TWO_PI;

	position.x += cosf(rad) * speed;
	position.y += sinf(rad) * speed;

	hitCircle[0].position = position;

	if(isFrameOut(0)){
		needDelete = true;
	}
}