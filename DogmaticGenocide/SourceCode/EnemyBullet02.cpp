#include "EnemyBullet02.h"


EnemyBullet02::EnemyBullet02(int imageHandle, Vector& position, int color, float speed, float angle) :
EnemyBulletUnit(imageHandle, position, color, speed, angle, true)
{
	image.width /= 3;
	image.angle = angle;

	hitCircle.resize(1);
	hitCircle[0].position = position;
	hitCircle[0].radius = 3.0f;
}

void EnemyBullet02::update(){
	const float rad = angle * TWO_PI;

	position.x += cosf(rad) * speed;
	position.y += sinf(rad) * speed;

	image.angle = angle;
	if(animeCnt % 4 == 0){
		image.left += image.width;
	}
	if(animeCnt% 8 == 0){
		image.left = 0;
	}
	++animeCnt;

	hitCircle[0].position = position;

	if(isFrameOut(0)){
		needDelete = true;
	}
}