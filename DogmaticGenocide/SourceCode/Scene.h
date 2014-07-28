#pragma once

class IScene{
public:
	virtual ~IScene(){ }
	virtual void update() = 0;
	virtual void draw() = 0;
};