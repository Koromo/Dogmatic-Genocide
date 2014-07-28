#include "SoundManager.h"
#include "DxLib.h"
#include <assert.h>

SoundManager* SoundManager::m_instance = nullptr;

SoundManager::~SoundManager(){
	InitSoundMem();
}

bool SoundManager::createInstance(){
	if(m_instance){
		return false;
	}

	m_instance = new SoundManager();

	return true;
}

bool SoundManager::destroyInstance(){
	if(! m_instance){
		return false;
	}

	delete m_instance;
	m_instance = nullptr;

	return true;
}

SoundManager& SoundManager::getInstance(){
#ifndef NDEBUG
	assert(m_instance != nullptr);
#endif
	if(! m_instance){
		createInstance();
	}

	return *m_instance;
}

int SoundManager::set(int id, int handle){
	int n = m_resource.set(id, handle);

	if(n == -1){
		DeleteSoundMem(handle);
	}

	return n;
}

int SoundManager::set(int id, std::string fileName){
	return set(id, LoadSoundMem(fileName.c_str()));
}

int SoundManager::get(int id){
	return m_resource.get(id);
}

void SoundManager::remove(int id){
	DeleteSoundMem(m_resource.remove(id));
}

bool SoundManager::have(int id){
	return m_resource.have(id);
}

Volume* Volume::m_instance = nullptr;

bool Volume::createInstance(){
	if(m_instance){
		return false;
	}

	m_instance = new Volume();

	return true;
}

bool Volume::destroyInstance(){
	if(! m_instance){
		return false;
	}

	delete m_instance;
	m_instance = nullptr;

	return true;
}