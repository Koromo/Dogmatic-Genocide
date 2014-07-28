#include "ResourceContainer.h"
#include <cassert>

ResourceContainer::~ResourceContainer(){
	clear();
}

int ResourceContainer::set(int id, int handle){
	ResourceMap::iterator it = m_resourceMap.find(id);

	if(it != m_resourceMap.end()){
		return -1;
	}

	m_resourceMap.insert(std::pair<int, int>(id, handle));

	return handle;
}

int ResourceContainer::get(int id){
	ResourceMap::iterator it = m_resourceMap.find(id);

	if(it == m_resourceMap.end()){
		assert(false);
		return -1;
	}

	return it->second;
}

int ResourceContainer::remove(int id){
	ResourceMap::iterator it = m_resourceMap.find(id);

	if(it == m_resourceMap.end()){
		return -1;
	}

	int handle = it->second;

	m_resourceMap.erase(it);

	return handle;
}

bool ResourceContainer::have(int id){
	ResourceMap::iterator it = m_resourceMap.find(id);
	return it != m_resourceMap.end();
}

bool ResourceContainer::isEmpty() const{
	return m_resourceMap.empty();
}

void ResourceContainer::clear(){
	m_resourceMap.clear();
}