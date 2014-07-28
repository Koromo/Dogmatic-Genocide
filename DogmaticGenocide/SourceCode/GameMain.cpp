#include "GameMain.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "DeviceManager.h"
#include "Keyboard.h"
#include "Joypad.h"
#include "DualDevice.h"
#include "Title.h"
#include "DxLib.h"

void set_60hz(){
	static int term = 0.0f;
	static int t = 0.0f;

	term = GetNowCount() - t;

	if(16 - term> 0.0){
		Sleep(16 - term);
	}

	t = GetNowCount();
}

bool GameMain::running = false;

bool GameMain::init(){
	SceneManager::createInstance();
	ImageManager::createInstance();
	SoundManager::createInstance();
	DeviceManager::createInstance();
	Volume::createInstance();

	running = true;

	return true;
}

bool GameMain::run(){
	int n = GetJoypadNum();

	if(n > 0){
		DeviceMng.set(0, new DualDevice(new Joypad(1, "Key.dat"), new Keyboard()), true);
	} else {
		DeviceMng.set(0, new Keyboard(), true);
	}

	SceneMng.change(new Title(DeviceMng.get(0)));

	while(ProcessMessage() == 0 && running){
		ClearDrawScreen();
		DeviceMng.update();
		SceneMng.update();
		SceneMng.draw();
		ScreenFlip();
		set_60hz();
	}

	return true;
}

bool GameMain::end(){
	SceneManager::deleteInstance();
	DeviceManager::deleteInstance();
	ImageManager::destroyInstance();
	SoundManager::destroyInstance();
	Volume::destroyInstance();

	return true;
}