#pragma once

#include "Scene.h"
#include "DeviceManager.h"
#include "Image.h"
#include "ImageManager.h"
#include "Counter.h"

class Title : public IScene{
	enum Mode{
		GAMESTART, CONFIG, EXIT, MODE_NUM
	};

private:
	Image board_;
	Image back_;
	Image mask_;
	Image title_;
	Image modeHandle_[MODE_NUM];
	IDevice* device_;
	Counter cnt_;

public:
	Title(IDevice* device);
	~Title();
	void update();
	void draw();
};