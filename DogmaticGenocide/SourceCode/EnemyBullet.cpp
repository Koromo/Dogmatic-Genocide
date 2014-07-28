#include "EnemyBullet.h"
#include "Effect.h"
#include "Item.h"
#include "ObjectManager.h"

EnemyBulletUnit::EnemyBulletUnit(int imageHandle, Vector& position, int color, float speed, float angle, bool collision) :
Object(imageHandle, position),
collision(collision),
color(color),
speed(speed),
angle(angle)
{ }

void EnemyBulletUnit::draw(){
	DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height,
		image.scaleRate, image.angle * TWO_PI, image.handle, TRUE, FALSE);

#ifdef DRAW_HIT_CIRCLE
	for(int i = 0, size = hitCircle.size(); i < size; ++i){
		DrawCircle(hitCircle[i].position.x, hitCircle[i].position.y, hitCircle[i].radius, GetColor(150, 150, 0), TRUE);
	}
#endif
}

bool EnemyBulletUnit::isCollision(){
	return collision;
}

const std::vector<HitCircle>& EnemyBulletUnit::getHitCircle(){
	return hitCircle;
}

void EnemyBulletUnit::hitAction(IPlayer* player){
	explosion(false);
}

int EnemyBulletUnit::getColor(){
	return color;
}

void EnemyBulletUnit::explosion(bool itemCreate){
	int handle;

	switch(color){
	case RED:
		handle = ImageMng.get(EBE_R);
		break;
	case BLUE:
		handle = ImageMng.get(EBE_B);
		break;
	case YELLOW:
		handle = ImageMng.get(EBE_B);
		break;
	default:
		break;
	}
	needDelete = true;
	ObjectMng.set(ENEMY_BULLET_EXPLOSION, new EnemyBulletExplosion(handle, position, speed, angle, itemCreate));
}