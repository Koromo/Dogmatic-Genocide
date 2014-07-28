#include "Device.h"

bool DeviceBase::input(int key){
	return keyState[key] > 0;
}

bool DeviceBase::frameInput(int key){
	return keyState[key] == 1;
}

bool DeviceBase::inputSome(){
	for(int i = 0; i < KEY_NUM; ++i){
		if(input(static_cast<KeyCode>(i))){
			return true;
		}
	}
	return false;
}

bool DeviceBase::frameInputSome(){
	for(int i = 0; i < KEY_NUM; ++i){
		if(frameInput(static_cast<KeyCode>(i))){
			return true;
		}
	}
	return false;
}