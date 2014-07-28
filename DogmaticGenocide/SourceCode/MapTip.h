#pragma once

#include "Object.h"

class MapTip : public Object
{
public:
	MapTip(int imageHandle, Vector& position) :
	  Object(imageHandle, position)
	  {
	  }
	void update()
	{
		position.y += 2.5f;

		if (position.y > GAME_SCREEN_BOTTOM) needDelete = true;
	}
	void draw()
	{
		DrawGraphF(position.x, position.y, image.handle, TRUE);
	}
};