#include "Keyboard.h"
#include "Dxlib.h"

Keyboard::Keyboard(){
	keyBuf[KEY_SHOT] = KEY_INPUT_Z;
	keyBuf[KEY_SPECIAL1] = KEY_INPUT_X;
	keyBuf[KEY_SLOW] = KEY_INPUT_LSHIFT;
	keyBuf[KEY_PAUSE] = KEY_INPUT_ESCAPE;
	keyBuf[KEY_UP] = KEY_INPUT_UP;
	keyBuf[KEY_DOWN] = KEY_INPUT_DOWN;
	keyBuf[KEY_RIGHT] = KEY_INPUT_RIGHT;
	keyBuf[KEY_LEFT] = KEY_INPUT_LEFT;
}

void Keyboard::update(){
	for(int i = 0; i < KEY_NUM; ++i){
		if(CheckHitKey(keyBuf[i]) == 1){
			++keyState[i];
		} else {
			keyState[i] = 0;
		}
	}
}