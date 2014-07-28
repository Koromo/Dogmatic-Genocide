#pragma once

struct Vector;

class BossFactory{
public:
	static void createBoss01(int imageHandle, Vector& position, float life, int level);
};