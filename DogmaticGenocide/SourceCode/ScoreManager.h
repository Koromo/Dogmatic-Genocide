#pragma once

#include <string>

#define ScoreMng ScoreManager::getInstance()

class ScoreManager{
private:
	static ScoreManager* instance_;
	long long unsigned score_;
	long long unsigned highScore_;
	std::string fileName_;

private:
	ScoreManager(const std::string& fileName);
	ScoreManager(const ScoreManager&);
	const ScoreManager& operator=(const ScoreManager&);

public:
	static bool createInstance(const std::string& fileName);
	static bool destroyInstance();
	static ScoreManager& getInstance();
	void addScore(long long unsigned score);
	void scoreInHighScore(){ highScore_ = score_; }
	void saveHighScore();
	void reset(){ score_ = 0; }

	long long unsigned getScore(){ return score_; }
	long long unsigned getHighScore(){ return highScore_; }
};