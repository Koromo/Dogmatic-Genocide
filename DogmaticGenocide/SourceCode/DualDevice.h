#pragma once

#include "Device.h"
#include "Keyboard.h"
#include "Joypad.h"

class DualDevice : public DeviceBase{
private:
	IDevice* device[2];

public:
	DualDevice(IDevice* device1, IDevice* device2);
	~DualDevice();
	void update();
	void config(std::string fileName);
	int getNumber(){ return device[0]->getNumber(); }
};