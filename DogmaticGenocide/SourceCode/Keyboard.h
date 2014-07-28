#pragma once

#include "Device.h"
#include <string>

class Keyboard : public DeviceBase{
public:
	Keyboard();
	void update();
	int getNumber(){ return 0; }
};