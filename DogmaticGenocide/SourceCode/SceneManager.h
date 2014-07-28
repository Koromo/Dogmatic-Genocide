#pragma once

#include "Scene.h"
#include <stack>

#define SceneMng SceneManager::getInstance()

class SceneManager{
private:
	static SceneManager* instance;
	std::stack<IScene*> sceneStack;

private:
	SceneManager(){ }
	SceneManager(const SceneManager&);
	const SceneManager& operator=(const SceneManager&);

public:
	~SceneManager();
	static bool createInstance();
	static bool deleteInstance();
	static SceneManager& getInstance();
	void update();
	void draw();
	void change(IScene* scene);
	void ride(IScene* scene);
	void back(int n);

private:
	void deleteTop();
};