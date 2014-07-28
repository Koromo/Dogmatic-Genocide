#pragma once

#include "Device.h"
#include <unordered_map>

#define DeviceMng DeviceManager::getInstance()

class DeviceManager{
private:
	static DeviceManager* instance;
	std::unordered_map<int, IDevice*> deviceMap;

private:
	DeviceManager(){ }
	DeviceManager(const DeviceManager&);
	const DeviceManager& operator=(const DeviceManager&);

public:
	~DeviceManager();
	static bool createInstance();
	static bool deleteInstance();
	static DeviceManager& getInstance();
	void set(int n, IDevice* device, bool newRide);
	void remove(int n);
	IDevice* get(int n);
	void update();
};