#include "Joypad.h"
#include "DxLib.h"
#include <fstream>

Joypad::Joypad(int number) :
number(number)
{
	keyBuf[KEY_SHOT] = PAD_INPUT_1;
	keyBuf[KEY_SPECIAL1] = PAD_INPUT_2;
	keyBuf[KEY_SLOW] = PAD_INPUT_4;
	keyBuf[KEY_PAUSE] = KEY_INPUT_5;
	keyBuf[KEY_UP] = PAD_INPUT_UP;
	keyBuf[KEY_DOWN] = PAD_INPUT_DOWN;
	keyBuf[KEY_RIGHT] = PAD_INPUT_RIGHT;
	keyBuf[KEY_LEFT] = PAD_INPUT_LEFT;
}

Joypad::Joypad(int number, std::string fileName) :
number(number)
{
	config(fileName);
	keyBuf[KEY_UP] = PAD_INPUT_UP;
	keyBuf[KEY_DOWN] = PAD_INPUT_DOWN;
	keyBuf[KEY_RIGHT] = PAD_INPUT_RIGHT;
	keyBuf[KEY_LEFT] = PAD_INPUT_LEFT;
}

void Joypad::update(){
	int state = GetJoypadInputState(number);

	for(int i = 0; i < KEY_NUM; ++i){
		if((state & keyBuf[i]) != 0){
			++keyState[i];
		} else {
			keyState[i] = 0;
		}
	}
}