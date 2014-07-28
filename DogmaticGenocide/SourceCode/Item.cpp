#include "Item.h"
#include "ObjectManager.h"

ItemUnit::ItemUnit(int imageHandle, Vector& position) :
Object(imageHandle, position)
{ }

bool ItemUnit::isCollision(){
	return true;
}

const std::vector<HitCircle>& ItemUnit::getHitCircle(){
	return hitCircle;
}

void ItemUnit::draw(){
	DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height,
		image.scaleRate, image.angle * TWO_PI, image.handle, TRUE, FALSE);

#ifdef DRAW_HIT_CIRCLE
	for(int i = 0, size = hitCircle.size(); i < size; ++i){
		DrawCircle(hitCircle[i].position.x, hitCircle[i].position.y, hitCircle[i].radius, GetColor(0, 150, 0), TRUE);
	}
#endif
}

Energy::Energy(int imageHandle, Vector& position, float energy) :
ItemUnit(imageHandle, position),
energy(energy)
{
	image.scaleRate = 0.5;
	hitCircle.resize(1);
	hitCircle[0].radius = 20.0f;
	hitCircle[0].position = position;
}

void Energy::update(){
	image.scaleRate += 0.1;

	if(image.scaleRate > 1.0){
		image.scaleRate = 1.0;
	}

	if(moveCnt > 10){
		float speed = 2.0f;
		float rad = 0.25f * TWO_PI;

		if(PlayerMng.alive()){
			speed = 7.0f;
			rad = PlayerMng.getAngle(position) * TWO_PI;
		}

		position.x += cosf(rad) * speed;
		position.y += sinf(rad) * speed;
	}

	++moveCnt;

	if(position.y > 520.0f){
		needDelete = true;
	}

	hitCircle[0].position = position;
}

void Energy::hitAction(IPlayer* player){
	player->addEnergy(energy);
	PlaySound(SoundMng.get(SE_GETITEM));
	ScoreMng.addScore(500);
	needDelete = true;
}

Point::Point(int imageHandle, Vector& position, int point) :
ItemUnit(imageHandle, position),
point(point)
{
	image.scaleRate = 0.5;
	hitCircle.resize(1);
	hitCircle[0].radius = 20.0f;
	hitCircle[0].position = position;
}

void Point::update(){
	image.scaleRate += 0.1;

	if(image.scaleRate > 1.0){
		image.scaleRate = 1.0;
	}
	if(moveCnt > 10){
		float speed = 2.0f;
		float rad = 0.25f * TWO_PI;

		if(PlayerMng.alive()){
			speed = 7.0f;
			rad = PlayerMng.getAngle(position) * TWO_PI;
		}

		position.x += cosf(rad) * speed;
		position.y += sinf(rad) * speed;
	}

	++moveCnt;

	if(position.y > 520.0f){
		needDelete = true;
	}

	hitCircle[0].position = position;
}

void Point::hitAction(IPlayer* player){
	ScoreMng.addScore(point);
	PlaySound(SoundMng.get(SE_GETITEM));
	needDelete= true;
}