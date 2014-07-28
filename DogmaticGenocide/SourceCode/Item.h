#pragma once

#include "Object.h"
#include "ObjectManager.h"

class ItemUnit : public Object, public IItem{
protected:
	std::vector<HitCircle> hitCircle;

public:
	ItemUnit(int imageHandle, Vector& position);
	bool isCollision();
	const std::vector<HitCircle>& getHitCircle();
	void draw();
};

class Energy : public ItemUnit{
private:
	float energy;
	Counter moveCnt;

public:
	Energy(int imageHandle, Vector& position, float energy);
	void update();
	void hitAction(IPlayer* player);
};

class Point : public ItemUnit{
private:
	int point;
	Counter moveCnt;

public:
	Point(int imageHandle, Vector& position, int point);
	void update();
	void hitAction(IPlayer* player);
};

inline void createEnergy(int imageHandle, Vector& position, int n){
	switch(n){
	case 1:
		ItemMng.set(new Energy(imageHandle, position, 1.5f));
		break;
	case 2:
		ItemMng.set(new Energy(imageHandle, position, 5.0f));
		break;
	default:
		break;
	}
}

inline void createPoint(int imageHandle, Vector& position){
	ItemMng.set(new Point(imageHandle, position, 1000));
}