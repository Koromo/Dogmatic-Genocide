#include "EnemyBullet04.h"
#include "ObjectManager.h"

EnemyBullet04::EnemyBullet04(int imageHandle, Vector& position, int color, float speed, float angle, float angle2, Counter cnt) :
EnemyBulletUnit(imageHandle, position, color, speed, angle, true),
CNT_(cnt),
angle2_(angle2)
{
	image.angle = angle;
	hitCircle.resize(1);
	hitCircle[0].position = position;
	hitCircle[0].radius = 3.0f;
}

void EnemyBullet04::update(){
	if(cnt_ < CNT_){
		const float rad = angle * TWO_PI;

		position.x += cosf(rad) * speed;
		position.y += sinf(rad) * speed;
	}

	if(cnt_ == CNT_) angle = angle2_;

	if(cnt_ > CNT_ + 20){
		const float rad = angle * TWO_PI;

		position.x += cosf(rad) * speed;
		position.y += sinf(rad) * speed;
	}
	++cnt_;

	image.angle = angle;
	hitCircle[0].position = position;

	if(isFrameOut(0)){
		needDelete = true;
	}
}