#pragma once

#include "ResourceContainer.h"
#include "Dxlib.h"
#include <fstream>

#define SoundMng SoundManager::getInstance()

class SoundManager{
private:
	static SoundManager* m_instance;
	ResourceContainer m_resource;

private:
	SoundManager(){ }
	SoundManager(const SoundManager&);
	const SoundManager& operator=(const SoundManager&);

public:
	~SoundManager();
	static bool createInstance();
	static SoundManager& getInstance();
	static bool destroyInstance();
	int set(int id, int handle);
	int set(int id, std::string fileName);
	int get(int id);
	void remove(int id);
	bool have(int id);
	ResourceMap::iterator begin()
	{
		return m_resource.begin();
	}
	ResourceMap::iterator end()
	{
		return m_resource.end();
	}
};

class Volume{
private:
	static Volume* m_instance;
	int seVolume_;
	int bgmVolume_;

private:
	Volume()
	{
		std::ifstream ifile("Volume.dat", std::ios::binary);

		ifile >> seVolume_;
		ifile >> bgmVolume_;

		ifile.close();

		fit();
	}

public:
	static bool createInstance();
	static bool destroyInstance();
	static Volume& getInstance()
	{
		return *m_instance;
	}
	int getSeVolume(){
		//return seVolume_;
		return getBgmVolume();
	}
	int getBgmVolume(){ return bgmVolume_; }
	void setSeVolume(int volume){
		//seVolume_ = adjust(volume);
		setBgmVolume(volume);
	}
	void setBgmVolume(int volume){
		bgmVolume_ = adjust(volume);
		fit();
	}
	int adjust(int volume){
		if(volume < 0){ volume = 0; }
		if(250 < volume){ volume = 250; }
		return volume;
	}
	void save(){
		std::ofstream ofile("Volume.dat", std::ios::binary);

		ofile << seVolume_ << std::endl;
		ofile << bgmVolume_ << std::endl;

		ofile.close();
	}
	void fit()
	{
		ResourceMap::iterator it = SoundMng.begin();

		while (it != SoundMng.end())
		{
			ChangeVolumeSoundMem(bgmVolume_, it->second);
			++it;
		}
	}
};