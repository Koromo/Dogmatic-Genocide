#include "Common.h"
#include "SoundManager.h"
#include <cmath>

const float PI = PHI_F;
const float TWO_PI = TWO_PHI_F;

const int RESOLUTION_X = 640;
const int RESOLUTION_Y = 480;
const int COLOR_BIT = 16;

const int GAME_SCREEN_TOP = 0;
const int GAME_SCREEN_BOTTOM = 480;
const int GAME_SCREEN_LEFT = 112 - 2;
const int GAME_SCREEN_RIGHT = 528 + 2;
const int GAME_SCREEN_WIDTH = GAME_SCREEN_RIGHT - GAME_SCREEN_LEFT;
const int GAME_SCREEN_HEIGHT = GAME_SCREEN_BOTTOM - GAME_SCREEN_TOP;

float atan2f(const Vector& pos_1, const Vector& pos_2){
	return atan2f(pos_2.y - pos_1.y, pos_2.x - pos_1.x);
}

Vector getVector(float x, float y){
	Vector vct = {x, y};
	return vct;
}

float getNWayAngle(float angle, float width, int wayNum){
	if(wayNum % 2 == 0){
		return angle - width / 2 - ((wayNum / 2 - 1) * width);
	} else {
		return angle - (wayNum - 1) / 2 * width;
	}
}

int PlaySound(int handle, int type, int topPositionFlag){
	return PlaySoundMem(handle, type, topPositionFlag);
}

float getDistance(const Vector& pos1, const Vector& pos2){
	return sqrtf(powf(pos1.x - pos2.x, 2) + powf(pos1.y - pos2.y, 2));
}

float getRandamAngle(float width, int num)
{
	float w = width / static_cast<float>(num);

	w *= GetRand(num);

	return width / 2.0f - w;
}