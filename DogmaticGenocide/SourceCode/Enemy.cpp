#include "Enemy.h"

EnemyUnit::EnemyUnit(int imageHandle, Vector& position, float life, bool collision) :
Object(imageHandle, position),
collision(collision),
life(life)
{ }

void EnemyUnit::draw(){
	DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height,
		image.scaleRate, image.angle * TWO_PI, image.handle, TRUE, FALSE);

#ifdef DRAW_HIT_CIRCLE
	for(int i = 0, size = hitCircle.size(); i < size; ++i){
		DrawCircle(hitCircle[i].position.x, hitCircle[i].position.y, hitCircle[i].radius, GetColor(150, 0, 0), TRUE);
	}
#endif
}

bool EnemyUnit::isCollision(){
	return collision;
}

const Vector& EnemyUnit::getPosition(){
	return position;
}

const std::vector<HitCircle>& EnemyUnit::getHitCircle(){
	return hitCircle;
}

void EnemyUnit::hitAction(IPlayerBullet* playerBullet){
	life -= playerBullet->getPower();
}