#pragma once

#include "Scene.h"
#include "Image.h"
#include "DeviceManager.h"
#include "Counter.h"

class Option : public IScene
{
private:
	Image back_;
	IDevice* device_;
	Counter cnt_;

public:
	Option(IDevice* device);
	void update();
	void draw();
};