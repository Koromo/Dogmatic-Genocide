#include "EnemyBullet03.h"

EnemyBullet03::EnemyBullet03(int imageHandle, Vector& position, int color, float speed, float angle) :
EnemyBulletUnit(imageHandle, position, color, speed, angle, true)
{
	hitCircle.resize(1);
	hitCircle[0].position = position;
	hitCircle[0].radius = 3.0f;
}

void EnemyBullet03::update(){
	const float rad = angle * TWO_PI;

	position.x += cosf(rad) * speed;
	position.y += sinf(rad) * speed;

	image.angle += 0.015f;

	hitCircle[0].position = position;

	if(isFrameOut(0)){
		needDelete = true;
	}
}