#pragma once

#include "Scene.h"
#include "Device.h"
#include "Counter.h"
#include "Game.h"

class GameOver : public IScene 
{
private:
	Game& game_;
	IDevice* device_;
	Counter cnt_;

public:
	GameOver(Game& game, IDevice* device);
	void update();
	void draw();
};