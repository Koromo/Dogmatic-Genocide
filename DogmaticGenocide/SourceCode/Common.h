#pragma once

#include "DxLib.h"

// íËêî
extern const float PI;
extern const float TWO_PI;

extern const int RESOLUTION_X;
extern const int RESOLUTION_Y;
extern const int COLOR_BIT;

extern const int GAME_SCREEN_TOP;
extern const int GAME_SCREEN_BOTTOM;
extern const int GAME_SCREEN_LEFT;
extern const int GAME_SCREEN_RIGHT;
extern const int GAME_SCREEN_WIDTH;
extern const int GAME_SCREEN_HEIGHT;

struct Vector{
	float x;
	float y;
};

float atan2f(const Vector& pos_1, const Vector& pos_2);
Vector getVector(float x, float y);
float getNWayAngle(float angle, float width, int wayNum);
int PlaySound(int handle, int type = DX_PLAYTYPE_BACK, int topPositionFlag = TRUE);
float getDistance(const Vector& pos1, const Vector& pos2);
float getRandamAngle(float width, int num);

inline float getRandamF(float width, int num)
{
	return getRandamAngle(width, num);
}

template<typename T>
bool CircleToCircle(T x_1, T y_1, T r_1, T x_2, T y_2, T r_2){
	return ((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2)) <= ((r_1 + r_2) * (r_1 + r_2));
}

template<typename T>
bool BoxToBox(T x_1, T y_1, T width_1, T height_1, T x_2, T y_2, T width_2, T height_2){
	return (x_1 - x_2) <= (width_1 + width_2) && (y_1 - y_2) <= (height_1 + height_2);
}