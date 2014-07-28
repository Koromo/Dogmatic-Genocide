#include "ObjectManager.h"
#include <cassert>

ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::~ObjectManager(){
	ObjectMap::iterator it = objectMap.begin();
	ObjectMap::iterator end = objectMap.end();

	while(it != end){
		it = erase(it);
	}
}

bool ObjectManager::createInstance(){
	if(instance){
		return false;
	}

	instance = new ObjectManager();

	return true;
}

bool ObjectManager::deleteInstance(){
	if(! instance){
		return false;
	}

	delete instance;
	instance = nullptr;

	return true;
}

ObjectManager& ObjectManager::getInstance(){
	assert(instance);
	return *instance;
}

void ObjectManager::update(){
	ObjectMap::iterator it = objectMap.begin();
	ObjectMap::iterator end = objectMap.end();

	while(it != end){
		it->second->update();
		++it;
	}
}

void ObjectManager::draw(){
	ObjectMap::iterator it = objectMap.begin();
	ObjectMap::iterator end = objectMap.end();

	while(it != end){
		it->second->draw();
		if(it->second->isNeedDelete()){
			it = erase(it);
		} else {
			++it;
		}
	}
}

void ObjectManager::set(int id, IObject* obj){
	objectMap.insert(std::pair<int, IObject*>(id, obj));
}

ObjectMap::iterator ObjectManager::get(int id){
	return objectMap.find(id); 
}

std::pair<ObjectMap::iterator, ObjectMap::iterator> ObjectManager::getRange(int id){
	return objectMap.equal_range(id);
}

bool ObjectManager::hasObject(int id) const{
	return objectMap.find(id) != objectMap.end();
}

void ObjectManager::clear(){
	ObjectMap::iterator it = objectMap.begin();
	ObjectMap::iterator end = objectMap.end();

	while(it != end){
		it = erase(it);
	}
}

ObjectMap::iterator ObjectManager::erase(ObjectMap::iterator& it){
	delete it->second;
	it->second = nullptr;
	return objectMap.erase(it);
}

PlayerManager* PlayerManager::instance = nullptr;

bool PlayerManager::createInstance(){
	if(instance){
		return false;
	}

	instance = new PlayerManager();
	return true;
}

bool PlayerManager::deleteInstance(){
	if(instance){
		delete instance;
		instance = nullptr;
		return true;
	}
	return false;
}

PlayerManager& PlayerManager::getInstance(){
	return *instance;
}

PlayerManager::PlayerManager() :
position(getVector(0.0f, 0.0f)),
stock(0),
energy(0.0f),
alivePlayer(false)
{ }

void PlayerManager::update(IPlayer* player){
	if(player){
		position = player->getPosition();
		stock = player->getStock();
		energy = player->getEnergy();
	}
}

float PlayerManager::getAngle(Vector& position){
	return atan2f(position, this->position) / TWO_PI;
}

void PlayerManager::drawInfo(){
	if (energy < 100.0f)
	{
		DrawFormatString(110, 460, GetColor(255, 255, 255), "ÉGÉlÉãÉMÅ[è[ìUó¶:%d%%", static_cast<int>(energy));
	}
	else
	{
		DrawFormatString(110, 460, GetColor(255, 255, 255), "ÉGÉlÉãÉMÅ[è[ìUó¶:FULL");
	}
	
	for (int i = 0; i < stock; ++i)
	{
		DrawGraph(110 + i * 30, 30, handle, TRUE);
	}
}

IPlayer* PlayerManager::set(IPlayer* player){
	ObjectMng.set(PLAYER, dynamic_cast<IObject*>(player));
	return player;
}

std::pair<ObjectMap::iterator, ObjectMap::iterator> PlayerManager::get() const{
	return ObjectMng.getRange(PLAYER);
}

EnemyManager* EnemyManager::instance = nullptr;

EnemyManager::EnemyManager() :
life(0.0f),
_aliveBoss(false)
{ }

bool EnemyManager::createInstance(){
	if(instance){
		return false;
	}
	instance = new EnemyManager();
	return true;
}

bool EnemyManager::deleteInstance(){
	if(instance){
		delete instance;
		instance = nullptr;
		return true;
	}
	return false;
}

EnemyManager& EnemyManager::getInstance(){
	return *instance;
}

void EnemyManager::update(IBoss* boss){
	life = boss->getLife();
}

bool EnemyManager::aliveBoss(){
	return _aliveBoss;
}

void EnemyManager::drawBossInfo(){
	printfDx("LIFE : %.2f\n", life);
}

int EnemyManager::getSum(){
	int cnt = 0;

	std::pair<ObjectMap::iterator, ObjectMap::iterator> it = get();

	while(it.first != it.second){
		++cnt;
		++it.first;
	}

	return cnt;
}

IEnemy* EnemyManager::set(IEnemy* enemy){
	ObjectMng.set(ENEMY, dynamic_cast<IObject*>(enemy));
	return enemy;
}

std::pair<ObjectMap::iterator, ObjectMap::iterator> EnemyManager::get() const{
	return ObjectMng.getRange(ENEMY);
}

EnemyBulletManager* EnemyBulletManager::instance = nullptr;

EnemyBulletManager::EnemyBulletManager() :
m_create(false)
{ }

bool EnemyBulletManager::createInstance(){
	if(instance){
		return false;
	}
	instance = new EnemyBulletManager();
	return true;
}

bool EnemyBulletManager::deleteInstance(){
	if(instance){
		delete instance;
		instance = nullptr;
		return true;
	}
	return false;
}

EnemyBulletManager& EnemyBulletManager::getInstance(){
	return *instance;
}

int EnemyBulletManager::getSum(){
	int cnt = 0;

	std::pair<ObjectMap::iterator, ObjectMap::iterator> it = get();

	while(it.first != it.second){
		++cnt;
		++it.first;
	}

	return cnt;
}

IEnemyBullet* EnemyBulletManager::set(IEnemyBullet* bullet){
	if(m_create){
		ObjectMng.set(ENEMY_BULLET, dynamic_cast<IObject*>(bullet));
	} else {
		delete bullet;
		bullet = nullptr;
	}
	return bullet;
}

std::pair<ObjectMap::iterator, ObjectMap::iterator> EnemyBulletManager::get() const{
	return ObjectMng.getRange(ENEMY_BULLET);
}

void EnemyBulletManager::explosion(bool item){
			std::pair<ObjectMap::iterator, ObjectMap::iterator> itPair = ObjectMng.getRange(ENEMY_BULLET);

			while(itPair.first != itPair.second){
				if(IEnemyBullet* bullet = dynamic_cast<IEnemyBullet*>(itPair.first->second)){
					bullet->explosion(item);
				}
				++itPair.first;
			}
}

PlayerBulletManager* PlayerBulletManager::instance = nullptr;

bool PlayerBulletManager::createInstance(){
	if(instance){
		return false;
	}
	instance = new PlayerBulletManager();
	return true;
}

bool PlayerBulletManager::deleteInstance(){
	if(instance){
		delete instance;
		instance = nullptr;
		return true;
	}
	return false;
}

PlayerBulletManager& PlayerBulletManager::getInstance(){
	return *instance;
}

int PlayerBulletManager::getSum(){
	int cnt = 0;

	std::pair<ObjectMap::iterator, ObjectMap::iterator> it = get();

	while(it.first != it.second){
		++cnt;
		++it.first;
	}

	return cnt;
}

IPlayerBullet* PlayerBulletManager::set(IPlayerBullet* bullet){
	ObjectMng.set(PLAYER_BULLET, dynamic_cast<IObject*>(bullet));
	return bullet;
}

std::pair<ObjectMap::iterator, ObjectMap::iterator> PlayerBulletManager::get() const{
	return ObjectMng.getRange(PLAYER_BULLET);
}

ItemManager* ItemManager::instance = nullptr;

bool ItemManager::createInstance(){
	if(instance){
		return false;
	}
	instance = new ItemManager();
	return true;
}

bool ItemManager::deleteInstance(){
	if(instance){
		delete instance;
		instance = nullptr;
		return true;
	}
	return false;
}

ItemManager& ItemManager::getInstance(){
	return *instance;
}

int ItemManager::getSum(){
	int cnt = 0;

	std::pair<ObjectMap::iterator, ObjectMap::iterator> it = ObjectMng.getRange(ITEM);

	while(it.first != it.second){
		++cnt;
		++it.first;
	}

	return cnt;
}

IItem* ItemManager::set(IItem* item){
	ObjectMng.set(ITEM, dynamic_cast<IObject*>(item));
	return item;
}

std::pair<ObjectMap::iterator, ObjectMap::iterator> ItemManager::get() const{
	return ObjectMng.getRange(ITEM);
}