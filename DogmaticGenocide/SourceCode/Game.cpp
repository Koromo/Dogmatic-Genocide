#include "Game.h"
#include "Player.h"
#include "SceneManager.h"
#include "Pause.h"
#include "ScoreManager.h"
#include "GameOver.h"
#include "GameClear.h"

bool Game::finish_ = false;

Game::Game(int player, IStage* stage, IDevice* device) :
stage(nullptr),
player(player),
m_device(device),
score_(0)
{
	ScoreManager::createInstance("Score.dat");
	ObjectManager::createInstance();
	PlayerManager::createInstance();
	EnemyManager::createInstance();
	EnemyBulletManager::createInstance();
	PlayerBulletManager::createInstance();
	ItemManager::createInstance();
	highScore_ = ScoreMng.getHighScore();

	GameLoad load;
	load();

	stage->init();
	this->stage = stage;
	board.handle = ImageMng.get(GAME_BOARD);
	createPlayer(0.0f, 2);
	finish_ = false;
	contin_ = false;
	int id = player == 1 ? ICON_A : ICON_B;
	PlayerMng.setHandle(ImageMng.get(id));
}

Game::~Game(){
	GameDelete del;
	del();
	stage->end();
	ScoreManager::destroyInstance();
	ObjectManager::deleteInstance();
	PlayerManager::deleteInstance();
	EnemyManager::deleteInstance();
	EnemyBulletManager::deleteInstance();
	PlayerBulletManager::deleteInstance();
	ItemManager::deleteInstance();
	delete stage;
}

void Game::update(){
	if (finish_)
	{
		if (++finishCnt_ > 120) SceneMng.ride(new GameClear(DeviceMng.get(0), this));
	}

	if(pauseCnt_++ > 20 && m_device->frameInput(KEY_PAUSE)){
		PlaySound(SoundMng.get(SE_CHOISE));
		SceneMng.ride(new Pause(this, m_device));
		return;
	}

	stage->run();
	ObjectMng.update();

	if(! PlayerMng.alive()){
		++cnt;
		if(cnt == 90){
			if(PlayerMng.getStock() >= 0){
				createPlayer(PlayerMng.getEnergy(), PlayerMng.getStock());
			} else {
				SceneMng.ride(new GameOver(*this, m_device));
				cnt = 0;
				return;
			}
			cnt = 0;
		}
	}
}

void Game::draw(){
	ObjectMng.draw();
	DrawGraph(0, 0, board.handle, TRUE);
	PlayerMng.drawInfo();

	if(EnemyMng.aliveBoss()){
		//EnemyMng.drawBossInfo();
	}

	if (ScoreMng.getScore() >= score_)
	{
		long long unsigned sub = ScoreMng.getScore() - score_;

		score_ += sub > 800 ? 800 : 200;

		if (score_ > ScoreMng.getScore()) score_ = ScoreMng.getScore();
	}

	if(ScoreMng.getScore() > ScoreMng.getHighScore()) ScoreMng.scoreInHighScore();

	if (score_ > highScore_) highScore_ = score_;

	DrawFormatString(430, 0, GetColor(255, 255, 255), "HIGH SCORE");
	DrawFormatString(430, 15, GetColor(255, 255, 255), "%d", highScore_);
	DrawFormatString(110, 0, GetColor(255, 255, 255), "SCORE");
	DrawFormatString(110, 15, GetColor(255, 255, 255), "%d", score_);
}

void Game::change(IStage* stage){
	this->stage->end();
	delete this->stage;

	this->stage = stage;
	this->stage->init();
}

void Game::createPlayer(float energy, int stock){
	switch(player){
	case 1:
		PlayerMng.set(new Player_1(ImageMng.get(P_01), getVector(320.0f, 400.0f), energy, stock, DeviceMng.get(0)));
		break;
	case 2:
		PlayerMng.set(new Player_2(ImageMng.get(P_02), getVector(320.0f, 400.0f), energy, stock, DeviceMng.get(0)));
		break;
	default:
		break;
	}
	PlayerMng.setAlive(true);
}