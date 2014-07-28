#pragma once

#include "Scene.h"
#include "Device.h"
#include "Game.h"
#include "Counter.h"
#include <string>

class GameClear : public IScene
{
	IDevice* device_;
	Game* game_;
	Counter cnt_;
	long long unsigned score_[3];
	std::string str_[3];

public:
	GameClear(IDevice* deivce, Game* game);
	void update();
	void draw();
};