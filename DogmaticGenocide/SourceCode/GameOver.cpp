#include "GameOver.h"
#include "SceneManager.h"
#include "Title.h"

GameOver::GameOver(Game& game, IDevice* device) :
game_(game),
device_(device)
{
}

void GameOver::update()
{
	if (device_->frameInput(KEY_LEFT)) --cnt_;
	if (device_->frameInput(KEY_RIGHT)) ++cnt_;

	if (cnt_ < 0) cnt_ = 0;
	if (cnt_ > 1) cnt_ = 1;

	if (device_->frameInput(KEY_DECIDE))
	{
		switch (cnt_)
		{
		case 0:
			game_.keep(2);
			SceneMng.back(1);
			return;
			break;
		case 1:
			if (ScoreMng.getScore() >= ScoreMng.getHighScore()) ScoreMng.saveHighScore();
			SceneMng.change(new Title(device_));
			return;
			break;
		default:
			break;
		}
	}
}

void GameOver::draw()
{
	game_.draw();
	DrawCircle(130 + cnt_ * 60, 210, 5, GetColor(255, 0, 0));
	DrawString(140, 200, "YES", GetColor(255, 255, 255));
	DrawString(200, 200, "NO", GetColor(255, 255, 255));
	DrawString(140, 130, "CONTINUE??", GetColor(255, 255, 255));
}