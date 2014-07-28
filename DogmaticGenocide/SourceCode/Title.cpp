#include "Title.h"
#include "GameMain.h"
#include "SceneManager.h"
#include "LoadAndDelete.h"
#include "PlayerSerect.h"
#include "Option.h"
#include "SoundManager.h"
#include "Common.h"
#include "Dxlib.h"

Title::Title(IDevice* device) :
device_(device)
{	
	TitleLoad load;
	load();
	board_.handle = ImageMng.get(TITLE_BACKBOARD);
	board_.scaleRate = 640 / 2400;
	back_.handle = ImageMng.get(TITLE_BACK);
	mask_.handle = ImageMng.get(TITLE_MASK);
	title_.handle = ImageMng.get(TITLE_TITLE);
	modeHandle_[GAMESTART].handle = ImageMng.get(TITLE_GAMESTART);
	modeHandle_[CONFIG].handle = ImageMng.get(TITLE_OPTION);
	modeHandle_[EXIT].handle = ImageMng.get(TITLE_EXIT);

	PlaySound(SoundMng.get(BGM_TITLE), DX_PLAYTYPE_LOOP);
}

Title::~Title()
{
	TitleDelete del;
	del();
	StopSoundMem(SoundMng.get(BGM_TITLE));
}

// タイトル画面更新
void Title::update(){
	if (device_->frameInput(KEY_DOWN) ||
		device_->frameInput(KEY_UP) ||
		device_->frameInput(KEY_DECIDE))
	{
		PlaySound(SoundMng.get(SE_CHOISE));
	}

	if(device_->frameInput(KEY_DOWN)) ++cnt_;
	if(device_->frameInput(KEY_UP))   --cnt_;

	if(cnt_ < 0) cnt_ = MODE_NUM - 1;
	if(cnt_ == MODE_NUM) cnt_ = 0;

	if(device_->frameInput(KEY_DECIDE)){
		switch(cnt_){
		case GAMESTART:
			SceneMng.ride(new PlayerSerect(device_));
			break;
		case CONFIG:
			SceneMng.ride(new Option(device_));
			break;
		case EXIT:
			GameMain::setRunning(false);
			break;
		default:
			break;
		}

		return;
	}
}

// タイトル画面描画
void Title::draw(){
	DrawExtendGraph(0, 0, 640, 480, board_.handle, TRUE);
	DrawGraph(280, 20, title_.handle, TRUE);
	DrawGraph(0 - 75, 180 - 75, mask_.handle, TRUE);
	DrawGraph(0 - 30, 185 + 45 * cnt_, back_.handle, TRUE);
	for(int i = 0; i < MODE_NUM; ++i){
		DrawGraph(20, 190 + 45 * i, modeHandle_[i].handle, TRUE);
	}
}