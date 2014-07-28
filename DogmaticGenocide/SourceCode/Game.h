#pragma once

#include "Scene.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "LoadAndDelete.h"
#include "DeviceManager.h"

class Game : public IScene{
private:
	IStage* stage;
	Image board;
	int player;
	long long unsigned score_;
	long long unsigned highScore_;
	Counter cnt;
	Counter finishCnt_;
	IDevice* m_device;
	static bool finish_;
	bool contin_;
	Counter pauseCnt_;

public:
	Game(int player, IStage* stage, IDevice* device);
	~Game();
	static void setFinish(bool val){ finish_ = val; }
	void update();
	void draw();
	void change(IStage* stage);
	void createPlayer(float energy, int stock);
	void keep(int stock)
	{
		createPlayer(PlayerMng.getEnergy(), stock);
		ScoreManager::getInstance().reset();
		score_ = 0;
		contin_ = true;
	}
	int getLevel(){ return stage->getLevel(); }
	bool contin(){ return contin_; }
};