#pragma once

#include "Object.h"
#include "Common.h"
#include <unordered_map>
#include <map>

#define ObjectMng ObjectManager::getInstance()
#define PlayerMng PlayerManager::getInstance()
#define EnemyMng EnemyManager::getInstance()
#define EnemyBulletMng EnemyBulletManager::getInstance()
#define PlayerBulletMng PlayerBulletManager::getInstance()
#define ItemMng ItemManager::getInstance()

class IObject;
class IObjectMaager;

typedef std::multimap<int, IObject*> ObjectMap;

class ObjectManager{
private:
	static ObjectManager* instance;
	ObjectMap objectMap;

private:
	ObjectManager(){ }
	ObjectManager(const ObjectManager&);
	const ObjectManager& operator=(const ObjectManager&);

public:
	~ObjectManager();
	static bool createInstance();
	static bool deleteInstance();
	static ObjectManager& getInstance();
	void update();
	void draw();
	void set(int id, IObject* obj);
	ObjectMap::iterator get(int id);
	std::pair<ObjectMap::iterator, ObjectMap::iterator> getRange(int id);
	bool hasObject(int id) const;
	void clear();

private:
	ObjectMap::iterator erase(ObjectMap::iterator& it);
};

class PlayerManager{
private:
	static PlayerManager* instance;
	Vector position;
	int stock;
	float energy;
	bool alivePlayer;
	int handle;

private:
	PlayerManager();
	PlayerManager(const PlayerManager&);
	const PlayerManager& operator=(const PlayerManager&);

public:
	static bool createInstance();
	static bool deleteInstance();
	static PlayerManager& getInstance();
	void update(IPlayer* player);
	float getAngle(Vector& position);
	Vector getPosition(){ return position; }
	bool alive(){ return alivePlayer; }
	void drawInfo();
	void setHandle(int a){ handle = a; }
	IPlayer* set(IPlayer* player);
	std::pair<ObjectMap::iterator, ObjectMap::iterator> get() const;
	void setAlive(bool b){ alivePlayer = b; }
	float getEnergy(){ return energy; }
	int getStock(){ return stock; }
};

class EnemyManager{
private:
	static EnemyManager* instance;
	float life;
	bool _aliveBoss;

private:
	EnemyManager();
	EnemyManager(const EnemyManager&);
	const EnemyManager& operator=(const EnemyManager&);

public:
	static bool createInstance();
	static bool deleteInstance();
	static EnemyManager& getInstance();
	void update(IBoss* boss);
	bool aliveBoss();
	void drawBossInfo();
	int getSum();
	IEnemy* set(IEnemy* enemy);
	std::pair<ObjectMap::iterator, ObjectMap::iterator> get() const;
	void setAlive(bool b){ _aliveBoss = b; }
};

class EnemyBulletManager{
private:
	static EnemyBulletManager* instance;
	bool m_create;

private:
	EnemyBulletManager();
	EnemyBulletManager(const EnemyBulletManager&);
	const EnemyBulletManager& operator=(const EnemyBulletManager&);

public:
	static bool createInstance();
	static bool deleteInstance();
	static EnemyBulletManager& getInstance();
	int getSum();
	IEnemyBullet* set(IEnemyBullet* bullet);
	std::pair<ObjectMap::iterator, ObjectMap::iterator> get() const;	
	void setCreate(bool b){ m_create = b; }
	void explosion(bool item);
};

class PlayerBulletManager{
private:
	static PlayerBulletManager* instance;

private:
	PlayerBulletManager(){ }
	PlayerBulletManager(const PlayerBulletManager&);
	const PlayerBulletManager& operator=(const PlayerBulletManager&);

public:
	static bool createInstance();
	static bool deleteInstance();
	static PlayerBulletManager& getInstance();
	int getSum();
	IPlayerBullet* set(IPlayerBullet* bullet);
	std::pair<ObjectMap::iterator, ObjectMap::iterator> get() const;
};

class ItemManager{
private:
	static ItemManager* instance;

private:
	ItemManager(){ }
	ItemManager(const ItemManager&);
	const ItemManager& operator=(const ItemManager&);

public:
	static bool createInstance();
	static bool deleteInstance();
	static ItemManager& getInstance();
	int getSum();
	IItem* set(IItem* item);
	std::pair<ObjectMap::iterator, ObjectMap::iterator> get() const;
};