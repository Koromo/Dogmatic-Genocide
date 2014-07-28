#include "LevelSerect.h"
#include "ImageManager.h"
#include "ResourceID.h"
#include "SceneManager.h"
#include "Game.h"
#include "DxLib.h"

LevelSerect::LevelSerect(int player, IDevice* device) :
m_device(device),
m_player(player),
m_cnt(1)
{
	m_image.handle = ImageMng.get(TITLE_BACKBOARD);
	m_image.scaleRate = 640 / 2400;
}

void LevelSerect::update(){
	if (m_device->frameInput(KEY_DOWN) ||
		m_device->frameInput(KEY_UP) ||
		m_device->frameInput(KEY_SPECIAL1) ||
		m_device->frameInput(KEY_DECIDE))
	{
		PlaySound(SoundMng.get(SE_CHOISE));
	}

	if(m_device->frameInput(KEY_UP)){
		--m_cnt;
	}
	if(m_device->frameInput(KEY_DOWN)){
		++m_cnt;
	}

	if(m_cnt > 2){
		m_cnt = 2;
	}
	if(m_cnt < 0){
		m_cnt = 0;
	}

	if(m_device->frameInput(KEY_DECIDE)){
		SceneMng.change(new Game(m_player, new Stage1(m_cnt + 1), m_device));
		return;
	}
	if(m_device->frameInput(KEY_SPECIAL1)){
		SceneMng.back(1);
		return;
	}
}

void LevelSerect::draw(){
	DrawExtendGraph(0, 0, 640, 480, m_image.handle, TRUE);

	DrawCircle(80, 110 + 100 * m_cnt, 10, GetColor(255, 0, 0), TRUE);
	DrawString(100, 100, "easy", GetColor(255, 255, 255));
	DrawString(100, 200, "normal", GetColor(255, 255, 255));
	DrawString(100, 300, "hard", GetColor(255, 255, 255));
}