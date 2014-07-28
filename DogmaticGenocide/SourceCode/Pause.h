#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Game.h"
#include "Counter.h"
#include "DeviceManager.h"

class Pause : public IScene{
private:
	Counter cnt;
	Game* game;
	IDevice* device;

public:
	Pause(Game* game, IDevice* device);
	void update();
	void draw();
};