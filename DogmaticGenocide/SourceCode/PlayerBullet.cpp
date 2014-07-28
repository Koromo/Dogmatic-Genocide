#include "PlayerBullet.h"
#include "Effect.h"
#include "ObjectManager.h"

PlayerBulletUnit::PlayerBulletUnit(int imageHandle, Vector& position, float power, bool collision) :
Object(imageHandle, position),
collision(collision),
power(power)
{ }

void PlayerBulletUnit::draw(){
	if(! needDelete){
		DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height,
			image.scaleRate, image.angle * TWO_PI, image.handle, TRUE, FALSE);

#ifdef DRAW_HIT_CIRCLE
		for(int i = 0, size = hitCircle.size(); i < size; ++i){
			DrawCircle(hitCircle[i].position.x, hitCircle[i].position.y, hitCircle[i].radius, GetColor(0, 150, 150), TRUE);
		}
#endif
	}
}

bool PlayerBulletUnit::isCollision(){
	return collision;
}

const std::vector<HitCircle>& PlayerBulletUnit::getHitCircle(){
	return hitCircle;
}

void PlayerBulletUnit::hitAction(IEnemy* enemy){
	explosion();
	ScoreMng.addScore(5);
}

float PlayerBulletUnit::getPower(){
	return power;
}

void PlayerBulletUnit::collideJudge(){
	std::pair<ObjectMap::iterator, ObjectMap::iterator> itPair = ObjectMng.getRange(ENEMY);

	while(itPair.first != itPair.second){
		IEnemy* ptr = dynamic_cast<IEnemy*>(itPair.first->second);

		if(ptr && collision && ptr->isCollision() && Collision::collision(this, ptr)){
			hitAction(ptr);
			ptr->hitAction(this);
		}

		++itPair.first;
	}
}


PlayerBulletBoost::PlayerBulletBoost(int imageHandle, Vector& position, int color, float power, float speed, float angle) :
PlayerBulletUnit(imageHandle, position, power, true),
m_speed(speed),
m_angle(angle),
m_color(color)
{
	image.angle = angle;

	hitCircle.resize(1);
	for(int i = 0; i < 1; ++i){
		hitCircle[i].radius = 10.0f;
	}
	hitCircleUpdate();
}

void PlayerBulletBoost::update(){
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

void PlayerBulletBoost::collideJudge(){
	PlayerBulletUnit::collideJudge();
	std::pair<ObjectMap::iterator, ObjectMap::iterator> itPair = ObjectMng.getRange(ENEMY_BULLET);

	while(itPair.first != itPair.second){
		IEnemyBullet* ptr = dynamic_cast<IEnemyBullet*>(itPair.first->second);

		if(ptr && ptr->getColor() == m_color && collision && ptr->isCollision() && Collision::collision(this, ptr)){
			ptr->explosion(true);
		}

		++itPair.first;
	}
}

void PlayerBulletBoost::move(){
	const float rad = m_angle * TWO_PI;

	auto f = [this, &rad]()
	{
		position.x += cosf(rad) * m_speed * 0.5f;
		position.y += sinf(rad) * m_speed * 0.5f;
	};
	
	f();

	if (! needDelete)
	{
		hitCircleUpdate();
		collideJudge();
	}

	if (! needDelete)
	{
		f();
	}

	//if (! needDelete)
	//{
	//	hitCircleUpdate();
	//	collideJudge();
	//}

	//if (! needDelete)
	//{
	//	f();
	//}
}

void PlayerBulletBoost::hitCircleUpdate(){
	const float rad = m_angle * TWO_PI;

	hitCircle[0].position.x = position.x + cosf(rad);
	hitCircle[0].position.y = position.y + sinf(rad);
}

void PlayerBulletBoost::explosion(){
	ObjectMng.set(PLAYER_BULLET_EXPLOSION, new BulletExplosion(ImageMng.get(PBE_01), position));
	needDelete = true;
	collision = false;
}