#pragma once

#include "Scene.h"
#include "Counter.h"
#include "DeviceManager.h"
#include "Image.h"
#include <string>

class KeyConfig : public IScene{
private:
	Image m_board;
	Counter m_cnt;
	IDevice* m_device;
	int m_keyBuf[BUTTON_NUM];
	std::string m_fileName;
	bool m_config;

public:
	KeyConfig(std::string fileName, IDevice* device, bool config);
	void update();
	void draw();

private:
	std::string convertKeyBuf(int keyBuf);
	int fuct(int my, int n)
	{
		for (int i = 0; i < BUTTON_NUM; ++i)
		{
			if (i == my) continue;
			if (m_keyBuf[i] == n) return i;
		}

		return -1;
	}
};