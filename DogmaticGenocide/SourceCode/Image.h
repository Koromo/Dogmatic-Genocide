#pragma once

struct Image{
	Image();

	int handle;
	int left;
	int top;
	int width;
	int height;
	float angle;
	double scaleRate;
};

struct Sound{
	Sound();
	Sound(float volumeRate);

	int handle;
	float volumeRate;
};