#pragma once

#include "Device.h"
#include <string>

class Joypad : public DeviceBase{
private:
	int number;

public:
	Joypad(int number);
	Joypad(int number, std::string fileName);
	void update();
	int getNumber(){ return number; }
};