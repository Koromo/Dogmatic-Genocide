#pragma once

#include <string>

class Window{
private:
	std::string fileName;

public:
	Window(std::string fileName);
	bool setUp();
};