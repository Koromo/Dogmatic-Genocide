#pragma once

#include "Scene.h"
#include "Counter.h"
#include "DeviceManager.h"
#include "Image.h"

class LevelSerect : public IScene{
private:
	Counter m_cnt;
	IDevice* m_device;
	Image m_image;
	int m_player;

public:
	LevelSerect(int player, IDevice* device);
	void update();
	void draw();
};