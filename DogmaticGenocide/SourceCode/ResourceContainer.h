#pragma once

#include <unordered_map>

typedef std::unordered_map<int, int> ResourceMap;

class ResourceContainer{
private:
	ResourceMap m_resourceMap;

public:
	~ResourceContainer();
	int set(int id, int handle);
	int get(int id);
	int remove(int id);
	bool have(int id);
	bool isEmpty() const;
	void clear();
	ResourceMap::iterator begin()
	{
		return m_resourceMap.begin();
	}
	ResourceMap::iterator end()
	{
		return m_resourceMap.end();
	}
};