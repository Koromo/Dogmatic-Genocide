#include "ImageManager.h"
#include "DxLib.h"
#include <cassert>

ImageManager* ImageManager::m_instance = nullptr;

ImageManager::~ImageManager(){
	InitGraph();
}

bool ImageManager::createInstance(){
	if(m_instance){
		return false;
	}

	m_instance = new ImageManager();

	return true;
}

bool ImageManager::destroyInstance(){
	if(! m_instance){
		return false;
	}

	delete m_instance;
	m_instance = nullptr;

	return true;
}

ImageManager& ImageManager::getInstance(){
#ifndef NDEBUG
	assert(m_instance);
#endif
	if(! m_instance){
		createInstance();
	}

	return *m_instance;
}

int ImageManager::set(int id, int handle){
	int n = m_resource.set(id, handle);

	if(n == -1){
		DeleteGraph(handle);
	}

	return n;
}

int ImageManager::set(int id, std::string fileName){
	return set(id, LoadGraph(fileName.c_str()));
}

int ImageManager::get(int id){
	return m_resource.get(id);
}

void ImageManager::remove(int id){
	DeleteGraph(m_resource.remove(id));
}

bool ImageManager::have(int id){
	return m_resource.have(id);
}