#pragma once

#include "ResourceContainer.h"

#define  ImageMng ImageManager::getInstance()

class ImageManager{
private:
	static ImageManager* m_instance;
	ResourceContainer m_resource;

private:
	ImageManager(){ }
	ImageManager(const ImageManager&);
	const ImageManager& operator=(const ImageManager&);

public:
	~ImageManager();
	static bool createInstance();
	static bool destroyInstance();
	static ImageManager& getInstance();
	int set(int id, int handle);
	int set(int id, std::string fileName);
	int get(int id);
	void remove(int id);
	bool have(int id);
};