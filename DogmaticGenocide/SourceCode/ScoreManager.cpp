#include "ScoreManager.h"
#include <fstream>
#include <cassert>

ScoreManager* ScoreManager::instance_ = nullptr;

ScoreManager::ScoreManager(const std::string& fileName) :
score_(0),
fileName_(fileName)
{
	std::ifstream ifs(fileName_);

	ifs >> highScore_;

	ifs.close();
}

bool ScoreManager::createInstance(const std::string& fileName){
	if(! instance_){
		instance_ = new ScoreManager(fileName);
		return true;
	}
	return false;
}

bool ScoreManager::destroyInstance(){
	if(instance_){
		delete instance_;
		instance_ = nullptr;
		return true;
	}
	return false;
}

ScoreManager& ScoreManager::getInstance(){
	return *instance_;
}

void ScoreManager::addScore(long long unsigned score){
	assert(score >= 0);
	score_ += score;
}

void ScoreManager::saveHighScore(){
	std::ofstream ofs(fileName_);

	ofs << highScore_ << std::endl;

	ofs.close();
}