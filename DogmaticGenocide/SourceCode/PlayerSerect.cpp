#include "PlayerSerect.h"
#include "LevelSerect.h"

PlayerSerect::PlayerSerect(IDevice* device) :
m_device(device)
{
	m_image.handle = ImageMng.get(TITLE_BACKBOARD);
	m_image.scaleRate = 640 / 2400;
}

void PlayerSerect::update(){
	if (m_device->frameInput(KEY_RIGHT) ||
		m_device->frameInput(KEY_LEFT) ||
		m_device->frameInput(KEY_SPECIAL1) ||
		m_device->frameInput(KEY_DECIDE))
	{
		PlaySound(SoundMng.get(SE_CHOISE));
	}

	if(m_device->frameInput(KEY_RIGHT)){
		++m_cnt;
	}
	if(m_device->frameInput(KEY_LEFT)){
		--m_cnt;
	}

	if(m_cnt > 1){
		m_cnt = 1;
	}
	if(m_cnt < 0){
		m_cnt = 0;
	}

	if(m_device->frameInput(KEY_DECIDE)){
		SceneMng.ride(new LevelSerect(m_cnt + 1, m_device));
		return;	
	}
	if(m_device->frameInput(KEY_SPECIAL1)){
		SceneMng.back(1);
		return;
	}
}

void PlayerSerect::draw(){
	DrawExtendGraph(0, 0, 640, 480, m_image.handle, TRUE);

	DrawCircle(100 * (m_cnt) + 40, 110, 10, GetColor(255, 0, 0), TRUE);
	DrawString(50, 100, "‹@‘ÌA", GetColor(0, 0, 255));
	DrawString(150, 100, "‹@‘ÌB", GetColor(255, 0, 0));
}