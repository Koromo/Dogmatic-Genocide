#include "DualDevice.h"

DualDevice::DualDevice(IDevice* device1, IDevice* device2){
	device[0] = device1;
	device[1] = device2;

	for(int i = 0; i < KEY_NUM; ++i){
		keyBuf[i] = device[0]->getKeyBuf(i);
	}
}

DualDevice::~DualDevice(){
	for(int i = 0; i < 2; ++i){
		delete device[i];
		device[i] = nullptr;
	}
}

void DualDevice::update(){
	device[0]->update();
	device[1]->update();

	for(int i = 0; i < KEY_NUM; ++i){
		if(device[0]->input(i) || device[1]->input(i)){
			++keyState[i];
		} else {
			keyState[i] = 0;
		}
	}
}

void DualDevice::config(std::string fileName){
	DeviceBase::config(fileName);
	device[0]->config(fileName);
}