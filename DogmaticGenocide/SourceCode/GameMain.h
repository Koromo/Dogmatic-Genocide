#pragma once

class GameMain{
private:
	static bool running;

public:
	static void setRunning(bool b){ running = b; }
	bool init();
	bool run();
	bool end();
};