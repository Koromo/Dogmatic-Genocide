#include "DeviceManager.h"
#include "Keyboard.h"
#include "Joypad.h"
#include "DualDevice.h"
#include "Dxlib.h"
#include <cassert>

DeviceManager* DeviceManager::instance = nullptr;

DeviceManager::~DeviceManager(){
	for(std::unordered_map<int, IDevice*>::iterator& it = deviceMap.begin(), end = deviceMap.end(); it != end; ){
		delete it->second;
		it->second = nullptr;
		it = deviceMap.erase(it);
	}
}

bool DeviceManager::createInstance(){
	if(instance){
		return false;
	}

	instance = new DeviceManager();

	return true;
}

bool DeviceManager::deleteInstance(){
	if(! instance){
		return false;
	}

	delete instance;
	instance = nullptr;

	return true;
}

DeviceManager& DeviceManager::getInstance(){
	return *instance;
}

void DeviceManager::set(int n, IDevice* device, bool newRide){
	std::unordered_map<int, IDevice*>::iterator& it = deviceMap.find(n);

	if(it == deviceMap.end()){
		deviceMap.insert(std::pair<int, IDevice*>(n, device));
	} else {
		if(newRide){
			remove(n);
			deviceMap.insert(std::pair<int, IDevice*>(n, device));
		}
	}
}

void DeviceManager::remove(int n){
	std::unordered_map<int, IDevice*>::iterator& it = deviceMap.find(n);

	if(it != deviceMap.end()){
		IDevice* ptr = it->second;

		delete ptr;
		ptr = nullptr;
		deviceMap.erase(it);
	} 
}

IDevice* DeviceManager::get(int n){
	std::unordered_map<int, IDevice*>::iterator it = deviceMap.find(n);

	if(it == deviceMap.end()){
		return nullptr;
	}

	return it->second;
}

void DeviceManager::update(){
	for(std::unordered_map<int, IDevice*>::iterator& it = deviceMap.begin(), end = deviceMap.end(); it != end; ++it){
		it->second->update();
	}
}