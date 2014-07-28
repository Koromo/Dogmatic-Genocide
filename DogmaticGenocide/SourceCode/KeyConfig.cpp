#include "KeyConfig.h"
#include "ImageManager.h"
#include "ResourceID.h"
#include "SceneManager.h"
#include "Common.h"
#include "SoundManager.h"
#include "DxLib.h"
#include <fstream>
#include <cmath>
#include <sstream>

KeyConfig::KeyConfig(std::string fileName, IDevice* device, bool config) :
m_device(device),
m_fileName(fileName),
m_config(config)
{
	m_board.handle = ImageMng.get(TITLE_BACKBOARD);
	m_board.scaleRate = 640 / 2400;

	std::ifstream ifile(fileName, std::ios::binary);

	for(int i = 0; i < BUTTON_NUM; ++i){
		int n;
		ifile >> n;
		m_keyBuf[i] = n;
	}
	ifile.close();
}

void KeyConfig::update(){
	if (m_device->frameInput(KEY_UP) ||
		m_device->frameInput(KEY_DOWN) ||
		m_device->frameInput(KEY_SHOT))
	{
		PlaySound(SoundMng.get(SE_CHOISE));
	}

	if(m_device->frameInput(KEY_UP)){
		--m_cnt;
	}
	if(m_device->frameInput(KEY_DOWN)){
		++m_cnt;
	}

	if(m_cnt < 0){
		m_cnt = 0;
	}
	if(m_cnt > BUTTON_NUM){
		m_cnt = BUTTON_NUM;
	}

	if(m_cnt == BUTTON_NUM){
		if(m_device->frameInput(KEY_DECIDE)){
			std::ofstream ofile(m_fileName, std::ios::binary);

			for(int i = 0; i < BUTTON_NUM; ++i){
				ofile << m_keyBuf[i] << std::endl;
			}
			ofile.close();

			if(m_config){
				m_device->config(m_fileName);
			}

			SceneMng.back(1);
			return;
		}
	} else {
		int number = m_device->getNumber();

		if(number != 0){
			int state = GetJoypadInputState(number);

			for(int i = 4; i < 32; ++i){
				if(state & 1 << i){
					int n = 1 << i;

					if (m_keyBuf[m_cnt]  != n)
					{
						int ret = fuct(m_cnt, n);
						
						if (ret != -1) m_keyBuf[ret] = m_keyBuf[m_cnt]; 

						m_keyBuf[m_cnt] = n;
						PlaySound(SoundMng.get(SE_CHOISE));
					}
					break;
				}
			}
		}
	}
}

void KeyConfig::draw(){
	DrawExtendGraph(0, 0, 640, 480, m_board.handle, TRUE);
	DrawCircle(20, 85 + m_cnt * 40, 10, GetColor(255, 0, 0), TRUE);
	DrawFormatString(40, 80, GetColor(255, 255, 255), "SHOT:\t%s", convertKeyBuf(m_keyBuf[KEY_SHOT]).c_str());
	DrawFormatString(40, 120, GetColor(255, 255, 255), "SPECIAL1:\t%s", convertKeyBuf(m_keyBuf[KEY_SPECIAL1]).c_str());
	DrawFormatString(40, 160, GetColor(255, 255, 255), "SLOW:\t%s", convertKeyBuf(m_keyBuf[KEY_SLOW]).c_str());
	DrawFormatString(40, 200, GetColor(255, 255, 255), "PAUSE:\t%s", convertKeyBuf(m_keyBuf[KEY_PAUSE]).c_str());
	DrawFormatString(40, 240, GetColor(255, 255, 255), "EXIT");
}

std::string KeyConfig::convertKeyBuf(int keyBuf){
	int n = keyBuf >> 4;
	int cnt = 1;

	while(n > 1){
		n /= 2;
		++cnt;
	}

	std::ostringstream str;
	str << "BUTTON " << cnt;
	return str.str();
}