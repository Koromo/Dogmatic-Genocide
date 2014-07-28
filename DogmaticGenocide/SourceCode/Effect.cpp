#include "Effect.h"
#include "DxLib.h"
#include "ObjectManager.h"

BulletExplosion::BulletExplosion(int imageHandle, Vector& position) :
Object(imageHandle, position)
{
	image.width /= 3;
}

void BulletExplosion::update(){
	Counter chengeCnt = 5;

	++animeCnt;
	if(animeCnt % chengeCnt == 4){
		image.left += image.width;
	}
	if(animeCnt == chengeCnt * 3){
		needDelete = true;
	}
}

void BulletExplosion::draw(){
	DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height, image.scaleRate, image.angle, image.handle, TRUE, FALSE);
}

EnemyExplosion::EnemyExplosion(int imageHandle, Vector& position) :
Object(imageHandle, position)
{
	image.width /= 3;
}

void EnemyExplosion::update(){
	Counter chengeCnt = 5;

	if(animeCnt % chengeCnt == 4){
		image.left += image.width;
	}
	if(animeCnt == chengeCnt * 3){
		needDelete = true;
	}

	++animeCnt;
}

void EnemyExplosion::draw(){
	DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height, image.scaleRate, image.angle, image.handle, TRUE, FALSE);
}

PlayerExplosion::PlayerExplosion(int imageHandle, Vector& position) :
Object(imageHandle, position)
{
	image.width /= 3;
}

void PlayerExplosion::update(){
	Counter chengeCnt = 8;

	++animeCnt;
	if(animeCnt % chengeCnt == 7){
		image.left += image.width;
	}
	if(animeCnt == chengeCnt * 3){
		needDelete = true;
	}
}

void PlayerExplosion::draw(){
	DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height, image.scaleRate, image.angle, image.handle, TRUE, FALSE);
}