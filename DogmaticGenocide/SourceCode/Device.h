#pragma once

#include <fstream> 

enum KeyCode{
	KEY_SHOT,
	KEY_SPECIAL1,
	//KEY_SPECIAL2,
	KEY_SLOW,
	KEY_PAUSE,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT, 
	KEY_LEFT,

	KEY_NUM,

	KEY_DECIDE = KEY_SHOT,
	KEY_CANSEL = KEY_SPECIAL1,
	BUTTON_NUM = 4
};

class IDevice{
public:
	virtual ~IDevice(){ }
	virtual void update() = 0;
	virtual bool input(int key) = 0;
	virtual bool frameInput(int key) = 0;
	virtual bool inputSome() = 0;
	virtual bool frameInputSome() = 0;
	virtual int getKeyBuf(int keyCode) = 0;
	virtual void config(std::string fileName) = 0;
	virtual int getNumber() = 0;
};

class DeviceBase : public IDevice{
protected:
	int keyState[KEY_NUM];
	int keyBuf[KEY_NUM];

public:
	bool input(int key);
	bool frameInput(int key);
	bool inputSome();
	bool frameInputSome();
	int getKeyBuf(int keyCode){ return keyBuf[keyCode]; }
	void config(std::string fileName){
		std::ifstream ifile(fileName);

		for(int i = 0; i < BUTTON_NUM; ++i){
			ifile >> keyBuf[i];
		}
		ifile.close();
	}
};