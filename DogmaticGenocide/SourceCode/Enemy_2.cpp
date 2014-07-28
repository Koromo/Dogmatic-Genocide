//#include "Enemy_2.h"
//#include "DxLib.h"
//#include "ObjectManager.h"
//#include "EnemyBullet.h"
//#include "ImageManager.h"
//
//Enemy_2::Enemy_2(int imageHandle, Vector& position, float life, float angle) :
//Enemy(imageHandle, position, true, life),
//angle(angle),
//active(false),
//privActive(false)
//{
//	animetion();
//	hitCircle.resize(1);
//	hitCircle[0].radius = 20.0f;
//	hitCircleUpdate();
//}
//
//void Enemy_2::update(){
//	move();
//	hitCircleUpdate();
//	animetion();
//
//	collision = active = isActive();	
//
//	if(active){
//		shot();
//	}
//
//	needDelete = ! isAlive();
//
//	privActive = active;
//}
//
//void Enemy_2::draw(){
//	DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height,
//		image.scaleRate, image.angle, image.handle, TRUE, FALSE);
//}
//
//void Enemy_2::hitCircleUpdate(){
//	hitCircle[0].position = position;
//}
//
//void Enemy_2::animetion(){
//	image.angle = angle;
//}
//
//Enemy_2A::Enemy_2A(int imageHandle, Vector& position, float life, float angle) :
//Enemy_2(imageHandle, position, life, angle),
//speed(4.0f)
//{ }
//
//void Enemy_2A::move(){
//	float rad = angle * TWO_PI;
//	float aimRad = rad;
//	const float maxRad = 0.001f * TWO_PI; 
//	float turnRad;
//
//	if(ObjectMng.hasObject(PLAYER)){
//		aimRad = atan2f(position, dynamic_cast<IPlayer*>(ObjectMng.get(PLAYER)->second)->getPosition());
//	}
//
//	turnRad = rad - aimRad;
//
//	if(turnRad > PI) turnRad -= TWO_PI;
//	if(turnRad < -PI) turnRad += TWO_PI;
//	if(turnRad > maxRad) turnRad = maxRad;
//	if(turnRad < -maxRad) turnRad = -maxRad;
//
//	rad -= turnRad;
//	angle = rad / TWO_PI;
//
//	position.x += cosf(rad) * speed;
//	position.y += sinf(rad) * speed;
//}
//
//void Enemy_2A::shot(){
//	if(shotCnt == 30){
//		ObjectMng.set(ENEMY_BULLET, new EnemyBullet_2R(ImageMng.get(EB_1R), position, 4.0f, atan2f(position, dynamic_cast<IPlayer*>(ObjectMng.get(PLAYER)->second)->getPosition()) / TWO_PI));
//	}
//	++shotCnt;
//}
//
//bool Enemy_2A::isActive(){
//	return ! isFrameOut(0);
//}
//
//bool Enemy_2A::isAlive(){
//	return life > 0.0f && ! (privActive && ! active);
//}