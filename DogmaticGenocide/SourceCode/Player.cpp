#include "Player.h"
#include "PlayerBullet.h"
#include "PlayerBullet01.h"
#include "PlayerBullet02.h"
#include "ObjectManager.h"
#include "Effect.h"
#include <cassert>

PlayerUnit::PlayerUnit(int imageHandle, Vector& position, float radius, float speed, float energy, int stock, bool collision, IDevice* device) :
Object(imageHandle, position),
speed(speed),
energy(energy),
stock(stock),
device(device),
boost(false),
collision(false)
{
	image.width /= 3;
	image.scaleRate = 0.8;

	hitCircle.resize(1);
	hitCircle[0].position = position;
	hitCircle[0].radius = radius;
	m_move.x = 0.0f;
	m_move.y = 0.0f;
}

void PlayerUnit::update(){
	move();
	exchangeBoost();
	boost ? boostShot() : normalShot();
	if(cnt == 120){ EnemyBulletMng.setCreate(true); }
	cnt >= 180 ? collision = true : ++cnt;
	collideJudge();
	PlayerMng.update(this);
	addEnergy(1.0f / 30.0f);

	if(device->input(KEY_SLOW)){
		if(++m_bcnt > 20){
			addEnergy(1.0f / 45.0f);
		}
	} else {
		m_bcnt = 0;
	}
}

void PlayerUnit::draw(){
	if(collision){
		DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height,
			image.scaleRate, image.angle * TWO_PI, image.handle, TRUE, FALSE);
	} else {
		if(drawCnt % 3 < 2){
			DrawRectRotaGraphF(position.x, position.y, image.left, image.top, image.width, image.height,
				image.scaleRate, image.angle * TWO_PI, image.handle, TRUE, FALSE);
		}
		++drawCnt;
	}

	DrawCircle(hitCircle[0].position.x, hitCircle[0].position.y, 3, GetColor(255, 255, 255), TRUE);

#ifdef DRAW_HIT_CIRCLE
	for(int i = 0, size = hitCircle.size(); i < size; ++i){
		DrawCircle(hitCircle[i].position.x, hitCircle[i].position.y, hitCircle[i].radius, GetColor(0, 0, 150), TRUE);
	}
#endif
}

bool PlayerUnit::isCollision(){
	return collision;
}

const std::vector<HitCircle>& PlayerUnit::getHitCircle(){
	return hitCircle;
}

void PlayerUnit::hitAction(IEnemy* enemy){
	if(collision){
		--stock;
		explosion();
		PlaySound(SoundMng.get(SE_PE01));
	}
}

void PlayerUnit::hitAction(IEnemyBullet* enemyBullet){
	if(collision){
		--stock;
		explosion();
		PlaySound(SoundMng.get(SE_PE01));
	}
}

const Vector& PlayerUnit::getPosition(){
	return position;
}

void PlayerUnit::addEnergy(float energy){ 
	if(! boost){
		this->energy += energy;
	}

	if(this->energy > 100.0f){
		this->energy = 100.0f;
	}
}

void PlayerUnit::addStock(){
	++stock; 
}

float PlayerUnit::getEnergy(){
	return energy;
}

int PlayerUnit::getStock(){
	return stock;
}

void PlayerUnit::exchangeBoost(){
	if(! boost){
		if(device->input(KEY_SPECIAL1) && energy >= 100.0f){
			energy -= 100.0f;

			std::pair<ObjectMap::iterator, ObjectMap::iterator> itPair = ObjectMng.getRange(ENEMY_BULLET);

			while(itPair.first != itPair.second){
				if(IEnemyBullet* bullet = dynamic_cast<IEnemyBullet*>(itPair.first->second)){
					bullet->explosion(true);
				}
				++itPair.first;
			}

			boost = true;
		}
	} else {
		if(boostCnt < 60){
			std::pair<ObjectMap::iterator, ObjectMap::iterator> itPair = ObjectMng.getRange(ENEMY_BULLET);

			while(itPair.first != itPair.second){
				if(IEnemyBullet* bullet = dynamic_cast<IEnemyBullet*>(itPair.first->second)){
					bullet->explosion(false);
				}
				++itPair.first;
			}
		}

		if(boostCnt == 60 * 8){
			boost = false;
			boostCnt = 0;
		}
		++boostCnt;
	}
}

void PlayerUnit::hitCircleUpdate(){
	hitCircle[0].position = position;
}

void PlayerUnit::move(){
	Vector move = {0.0f, 0.0f};
	Vector pos = position;

	if(device->input(KEY_UP)){
		move.y = -speed;
	}
	if(device->input(KEY_DOWN)){
		move.y = speed;
	}
	if(device->input(KEY_LEFT)){
		move.x = -speed;
		--animeCnt;
	}
	if(device->input(KEY_RIGHT)){
		move.x = speed;
		++animeCnt;
	}
	if(! device->input(KEY_LEFT) && ! device->input(KEY_RIGHT)){
		if(animeCnt > 0){
			--animeCnt;
		} if(animeCnt < 0){
			++animeCnt;
		}
	}

	if(move.x != 0.0f && move.y != 0.0f){
		move.x /= sqrtf(2.0f);
		move.y /= sqrtf(2.0f);
	}

	if(device->input(KEY_SLOW)){
		move.x *= 0.5f;
		move.y *= 0.5f;
	}

	position.x += move.x;
	position.y += move.y;

	const int hoge = 10;

	if(position.x + hoge >= GAME_SCREEN_RIGHT || position.x - hoge <= GAME_SCREEN_LEFT){
		position.x -= move.x;
	}
	if(position.y + hoge >= GAME_SCREEN_BOTTOM || position.y - hoge <= GAME_SCREEN_TOP){
		position.y -= move.y;
	}

	m_move.x = position.x - pos.x;
	m_move.y = position.y - pos.y;

	hitCircleUpdate();
	animetion();
}

void PlayerUnit::animetion(){
	if(animeCnt >= 2){
		image.left = image.width;
		animeCnt = 2;
	}else if(animeCnt <= -2){
		image.left = image.width * 2;
		animeCnt = -2;
	} else {
		image.left = 0;
	}
}

void PlayerUnit::collideJudge(){
	std::pair<ObjectMap::iterator, ObjectMap::iterator> itPair = ObjectMng.getRange(ENEMY);

	while(itPair.first != itPair.second){
		IEnemy* ptr = dynamic_cast<IEnemy*>(itPair.first->second);

		if(ptr && ptr->isCollision() && Collision::collision(this, ptr)){
			hitAction(ptr);
		}

		++itPair.first;
	}

	itPair = ObjectMng.getRange(ENEMY_BULLET);

	while(itPair.first != itPair.second){
		IEnemyBullet* ptr = dynamic_cast<IEnemyBullet*>(itPair.first->second);

		if(ptr && ptr->isCollision() && Collision::collision(this, ptr)){
			hitAction(ptr);
			ptr->hitAction(this);
		}

		++itPair.first;
	}

	itPair = ObjectMng.getRange(ITEM);

	while(itPair.first != itPair.second){
		IItem* ptr = dynamic_cast<IItem*>(itPair.first->second);

		if(ptr && ptr->isCollision() && Collision::collision(this, ptr)){
			ptr->hitAction(this);
		}

		++itPair.first;
	}
}

Player_1::Player_1(int imageHandle, Vector& position, float energy, int stock, IDevice* device) :
PlayerUnit(imageHandle, position, 0.5f, 6.0f, energy, stock, true, device)
{
	for(int i = 0; i < 2; ++i){
		supporter[i] = new Player01Supporter(ImageMng.get(S_01), position);
	}
	adjustSupporterPosition();
	supporter[0]->setAngle(-0.28f);
	supporter[1]->setAngle(-0.22f);
}

void Player_1::normalShot(){
	if(device->input(KEY_SHOT)){
		if(shotCnt % 1 == 0){
			const float power = 1.0f;
			int handle = ImageMng.get(PB_01);

			PlayerBulletMng.set(new PlayerBullet01(handle, getVector(position.x + 3.5f, position.y - 25.0f), power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBullet01(handle, getVector(position.x - 3.5f, position.y - 25.0f), power, 25.0f - m_move.y, -0.25f));

			PlayerBulletMng.set(new PlayerBullet01(handle, getVector(position.x - 13.0f, position.y - 20.0f), power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBullet01(handle, getVector(position.x - 20.0f, position.y - 20.0f), power, 25.0f - m_move.y, -0.25f));

			PlayerBulletMng.set(new PlayerBullet01(handle, getVector(position.x + 13.0f, position.y - 20.0f), power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBullet01(handle, getVector(position.x + 20.0f, position.y - 20.0f), power, 25.0f - m_move.y, -0.25f));

			for(int i = 0; i < 2; ++i){
				supporter[i]->normalFire(25.0f - m_move.y, power);
			}
		}
		++shotCnt;
	}
}

void Player_1::boostShot(){
	if(device->input(KEY_SHOT)){
		if(shotCnt % 1 == 0){
			const float power = 1.5f;
			int handle = ImageMng.get(PB_B01);

			PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(position.x + 3.5f, position.y - 25.0f), BLUE, power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(position.x - 3.5f, position.y - 25.0f), BLUE, power, 25.0f - m_move.y, -0.25f));

			PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(position.x - 13.0f, position.y - 20.0f), BLUE, power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(position.x - 20.0f, position.y - 20.0f), BLUE, power, 25.0f - m_move.y, -0.25f));

			PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(position.x + 13.0f, position.y - 20.0f), BLUE, power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(position.x + 20.0f, position.y - 20.0f), BLUE, power, 25.0f - m_move.y, -0.25f));

			for(int i = 0; i < 2; ++i){
				supporter[i]->boostFire(25.0f - m_move.y, power);
			}
		}
		++shotCnt;
	}
}

void Player_1::move(){
	PlayerUnit::move();
	adjustSupporterPosition();
}

void Player_1::explosion(){
	ObjectMng.set(PLAYER_EXPLOSION, new PlayerExplosion(ImageMng.get(PE_B), position));
	PlayerMng.setAlive(false);
	needDelete = true;
}

void Player_1::adjustSupporterPosition(){
	supporter[0]->setPosition(getVector(position.x - 35.0f, position.y + 15.0f));
	supporter[1]->setPosition(getVector(position.x + 35.0f, position.y + 15.0f));
}

Player_2::Player_2(int imageHandle, Vector& position, float energy, int stock, IDevice* device) :
PlayerUnit(imageHandle, position, 0.5f, 6.0f, energy, stock, true, device)
{
	for(int i = 0; i < 4; ++i){
		supporter[i] = new Player02Supporter(ImageMng.get(S_02), position);
		supporter[i]->setAngle(-0.25f);
	}
	adjustSupporterPosition();
}

void Player_2::normalShot(){
	if(device->input(KEY_SHOT)){
		if(shotCnt % 1 == 0){
			const float power = 1.0f;

			PlayerBulletMng.set(new PlayerBullet02(ImageMng.get(PB_02), getVector(position.x + 8.0f, position.y - 25.0f), power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBullet02(ImageMng.get(PB_02), getVector(position.x - 8.0f, position.y - 25.0f), power, 25.0f - m_move.y, -0.25f));
			for(int i = 0; i < 4; ++i){
				supporter[i]->normalFire(25.0f - m_move.y, power + 0.2f);
			}
		}
		++shotCnt;
	}
}

void Player_2::boostShot(){
	if(device->input(KEY_SHOT)){
		if(shotCnt % 1 == 0){
			const float power = 1.5f;

			PlayerBulletMng.set(new PlayerBulletBoost(ImageMng.get(PB_B02), getVector(position.x + 8.0f, position.y - 25.0f), RED, power, 25.0f - m_move.y, -0.25f));
			PlayerBulletMng.set(new PlayerBulletBoost(ImageMng.get(PB_B02), getVector(position.x - 8.0f, position.y - 25.0f), RED, power, 25.0f - m_move.y, -0.25f));
			for(int i = 0; i < 4; ++i){
				supporter[i]->boostFire(25.0f - m_move.y, power + 0.3f);
			}
		}
		++shotCnt;
	}
}

void Player_2::move(){
	PlayerUnit::move();
	adjustSupporterPosition();
}

void Player_2::explosion(){
	ObjectMng.set(PLAYER_EXPLOSION, new PlayerExplosion(ImageMng.get(PE_R), position));
	PlayerMng.setAlive(false);
	needDelete = true;
}

void Player_2::adjustSupporterPosition(){
	supporter[0]->setPosition(getVector(position.x - 27.0f, position.y - 15.0f));
	supporter[1]->setPosition(getVector(position.x + 27.0f, position.y - 15.0f));
	supporter[2]->setPosition(getVector(position.x - 40.0f, position.y - 15.0f));
	supporter[3]->setPosition(getVector(position.x + 40.0f, position.y - 15.0f));
}

Player01Supporter::Player01Supporter(int imageHandle, Vector& position) :
m_position(position),
m_angle(0.0f)
{
	m_image.handle = imageHandle;
	GetGraphSize(m_image.handle, &m_image.width, &m_image.height);
	m_image.scaleRate = 0.6;
}

void Player01Supporter::draw(){
	DrawRectRotaGraphF(m_position.x, m_position.y, m_image.left, m_image.top, m_image.width, m_image.height,
		m_image.scaleRate, m_image.angle * TWO_PI, m_image.handle, TRUE, FALSE);
}

void Player01Supporter::normalFire(float speed, float power){
	int handle = ImageMng.get(SB_01);
	const float rad = m_angle * TWO_PI;
	PlayerBulletMng.set(new SupporterBullet01(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), power, speed, m_angle - 0.005f));
	PlayerBulletMng.set(new SupporterBullet01(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), power, speed, m_angle + 0.005f));
}

void Player01Supporter::boostFire(float speed, float power){
	int handle = ImageMng.get(PB_B01);
	const float rad = m_angle * TWO_PI;
	PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), BLUE, power, speed, m_angle - 0.005f));
	PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), BLUE, power, speed, m_angle + 0.005f));
}

Player02Supporter::Player02Supporter(int imageHandle, Vector& position) :
m_position(position),
m_angle(0.0f)
{
	m_image.handle = imageHandle;
	GetGraphSize(m_image.handle, &m_image.width, &m_image.height);
	m_image.scaleRate = 0.6;
}

void Player02Supporter::draw(){
	DrawRectRotaGraphF(m_position.x, m_position.y, m_image.left, m_image.top, m_image.width, m_image.height,
		m_image.scaleRate, m_image.angle * TWO_PI, m_image.handle, TRUE, FALSE);
}

void Player02Supporter::normalFire(float speed, float power){
	int handle = ImageMng.get(SB_02);
	const float rad = m_angle * TWO_PI;
	PlayerBulletMng.set(new SupporterBullet02(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), power, speed, m_angle));
	PlayerBulletMng.set(new SupporterBullet02(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), power, speed, m_angle));
}

void Player02Supporter::boostFire(float speed, float power){
	int handle = ImageMng.get(PB_B02);
	const float rad = m_angle * TWO_PI;
	PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), RED, power, speed, m_angle));
	PlayerBulletMng.set(new PlayerBulletBoost(handle, getVector(m_position.x + cosf(rad) * 15.0f, m_position.y + sinf(rad) * 15.0f), RED, power, speed, m_angle));
}