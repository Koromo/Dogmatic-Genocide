#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Game.h"
#include "Stage.h"
#include "Counter.h"
#include "DeviceManager.h"

class PlayerSerect : public IScene{
private:
	Counter m_cnt;
	IDevice* m_device;
	Image m_image;

public:
	PlayerSerect(IDevice* device);
	void update();
	void draw();
};