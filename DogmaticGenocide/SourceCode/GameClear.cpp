#include "GameClear.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include "Title.h"

GameClear::GameClear(IDevice* device, Game* game) :
device_(device),
game_(game)
{
	str_[0] = "難易度ボーナス";
	switch (game_->getLevel())
	{
	case 1:
		score_[0] = 10000;
		break;
	case 2:
		score_[0] = 20000;
		break;
	case 3:
		score_[0] = 50000;
		break;
	default:
		break;
	}

	str_[1] = "残機ボーナス";
	score_[1] = game->contin() ? 0 : PlayerMng.getStock() * 5000;

	str_[2] = "クリアボーナス";
	score_[2] = 100000;

	for (int i = 0; i < 3; ++i)
	{
		ScoreMng.addScore(score_[i]);
	}

	if (ScoreMng.getScore() >= ScoreMng.getHighScore()) ScoreMng.saveHighScore();
}

void GameClear::update()
{
	++cnt_;

	if (cnt_ < 90 && device_->frameInput(KEY_DECIDE)) cnt_ = 90;
	else if (cnt_ < 180 && device_->frameInput(KEY_DECIDE)) cnt_ = 180;
	else if (cnt_ < 270 && device_->frameInput(KEY_DECIDE)) cnt_ = 270;
	else if (cnt_ < 390 && device_->frameInput(KEY_DECIDE)) cnt_ = 390;

	if (cnt_ > 450 && device_->frameInput(KEY_DECIDE))
	{
		SceneMng.change(new Title(device_));
		return;
	}

	std::pair<ObjectMap::iterator, ObjectMap::iterator> itPair = ObjectMng.getRange(PLAYER);

	while(itPair.first != itPair.second){
		IPlayer* ptr = dynamic_cast<IPlayer*>(itPair.first->second);
		
		ptr->move();

		++itPair.first;
	}

	itPair = ObjectMng.getRange(MAP);

	while(itPair.first != itPair.second){
		IObject* ptr = dynamic_cast<IObject*>(itPair.first->second);
		
		ptr->update();

		++itPair.first;
	}

	itPair = ObjectMng.getRange(PLAYER_BULLET);

	while(itPair.first != itPair.second){
		IPlayerBullet* ptr = dynamic_cast<IPlayerBullet*>(itPair.first->second);
		
		ptr->move();

		++itPair.first;
	}
}

void GameClear::draw()
{
	game_->draw();

	if (cnt_ > 60) DrawString(120, 100, str_[0].c_str(), GetColor(255, 255, 255));
	if (cnt_ > 90) DrawFormatString(120, 130, GetColor(255, 255, 255), "%d", score_[0]);
	if (cnt_ > 150) DrawString(120, 170, str_[1].c_str(), GetColor(255, 255, 255));
	if (cnt_ > 180) DrawFormatString(120, 200, GetColor(255, 255, 255), "%d", score_[1]);
	if (cnt_ > 240) DrawString(120, 240, str_[2].c_str(), GetColor(255, 255, 255));
	if (cnt_ > 270) DrawFormatString(120, 270, GetColor(255, 255, 255), "%d", score_[2]);
	if (cnt_ > 330) DrawString(120, 320, "TotalScore", GetColor(255, 255, 255));
	if (cnt_ > 390) DrawFormatString(120, 350, GetColor(255, 255, 255), "%d", ScoreMng.getScore());
	if (cnt_ > 450)
	{
		DrawString(120, 400, "タイトルに戻ります", GetColor(0, 0, 255));
		DrawString(150, 430, "PRESS Z", GetColor(0, 0, 255));
	}
}