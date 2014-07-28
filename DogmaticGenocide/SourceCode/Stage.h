#pragma once

#include "Counter.h"
#include "Common.h"

class IStage{
public:
	virtual ~IStage(){ }
	virtual void init() = 0;
	virtual void end() = 0;
	virtual void run() = 0;
	virtual bool isFinish() = 0;
	virtual int getLevel() = 0;
};

class Stage1 : public IStage{
private:
	int level;
	Counter stageCnt;
	Counter cnt;

	struct Ary_t{
		Vector position;
		bool flag;
	}ary[9];

public:
	Stage1(int level);
	void init();
	void end();
	void run();
	bool isFinish(){ return false; }
	int getLevel(){ return level; }
};