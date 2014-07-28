#include "Option.h"
#include "ImageManager.h"
#include "ResourceID.h"
#include "SoundManager.h"
#include "KeyConfig.h"
#include "SceneManager.h"
#include "Common.h"
#include "DxLib.h"

Option::Option(IDevice* device) :
device_(device)
{
	back_.handle = ImageMng.get(TITLE_BACKBOARD);
	back_.scaleRate = 640 / 2400;
}

void Option::update()
{
	if (device_->frameInput(KEY_DOWN) ||
		device_->frameInput(KEY_UP) ||
		device_->frameInput(KEY_LEFT) ||
		device_->frameInput(KEY_RIGHT) ||
		device_->frameInput(KEY_SPECIAL1) ||
		device_->frameInput(KEY_SHOT))
	{
		PlaySound(SoundMng.get(SE_CHOISE));
	}

	if (device_->frameInput(KEY_UP)) --cnt_;
	if (device_->frameInput(KEY_DOWN)) ++cnt_;

	if (cnt_ < 0) cnt_ = 0;
	if (cnt_ > 2) cnt_ = 2;

	//if (cnt_ == 0)
	//{
	//	if(device_->frameInput(KEY_RIGHT)){
	//		Volume::getInstance().setSeVolume(Volume::getInstance().getSeVolume() - 25);
	//		Volume::getInstance().save();
	//	}
	//	if(device_->frameInput(KEY_LEFT)){
	//		Volume::getInstance().setSeVolume(Volume::getInstance().getSeVolume() + 25);
	//		Volume::getInstance().save();
	//	}
	//}
	if (cnt_ == 0)
	{
		if(device_->frameInput(KEY_RIGHT)){
			Volume::getInstance().setBgmVolume(Volume::getInstance().getBgmVolume() + 25);
			Volume::getInstance().save();
		}
		if(device_->frameInput(KEY_LEFT)){
			Volume::getInstance().setBgmVolume(Volume::getInstance().getBgmVolume() - 25);
			Volume::getInstance().save();
		}
	}

	if (device_->frameInput(KEY_DECIDE))
	{
		switch (cnt_)
		{
		case 1:
			SceneMng.ride(new KeyConfig("Key.dat", device_, GetJoypadNum() > 0));
			return;
		case 2:
			SceneMng.back(1);
			return;
		default:
			break;
		}
	}

	if (device_->frameInput(KEY_CANSEL))
	{
		SceneMng.back(1);
		return;
	}
}

void Option::draw()
{
	DrawExtendGraph(0, 0, 640, 480, back_.handle, TRUE);

	DrawCircle(25, 105 + cnt_ * 30, 10, GetColor(255, 0, 0), TRUE);
	DrawFormatString(200, 100, GetColor(255, 255, 255), "%d", Volume::getInstance().getBgmVolume() * 10 / 25);

	DrawString(50, 100, "SoundVolume", GetColor(255, 255, 255));
	DrawString(50, 130, "CONFIG", GetColor(255, 255, 255));
	DrawString(50, 160, "EXIT", GetColor(255, 255, 255));
}