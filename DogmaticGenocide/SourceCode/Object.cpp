#include "Object.h"
#include "DxLib.h"

Object::Object(int imageHandle, Vector& position) :
position(position),
needDelete(false)
{
	image.handle = imageHandle;
	GetGraphSize(image.handle, &image.width, &image.height);
}

bool Object::isNeedDelete(){
	return needDelete;
}

bool Object::isFrameOut(int n){
	int width = static_cast<int>(image.width * 0.5) + n;
	int height = static_cast<int>(image.height * 0.5) + n;

	return position.x + width < GAME_SCREEN_LEFT || 
		position.x - width > GAME_SCREEN_RIGHT ||
		position.y + height < GAME_SCREEN_TOP ||
		position.y - height > GAME_SCREEN_BOTTOM;
}

bool Object::isFrameIn(int n){
	int width = static_cast<int>(image.width * 0.5) + n;
	int height = static_cast<int>(image.height * 0.5) + n;

	return position.x + width < GAME_SCREEN_RIGHT &&
		position.x - width > GAME_SCREEN_LEFT &&
		position.y + height < GAME_SCREEN_BOTTOM &&
		position.y - height > GAME_SCREEN_TOP;
}