#include "SceneManager.h"
#include <cassert>

SceneManager* SceneManager::instance = nullptr;

SceneManager::~SceneManager(){
	while(! sceneStack.empty()){
		deleteTop();
	}
}

bool SceneManager::createInstance(){
	if(instance){
		return false;
	}

	instance = new SceneManager();

	return true;
}

bool SceneManager::deleteInstance(){
	if(! instance){
		return false;
	}

	delete instance;
	instance = nullptr;

	return true;
}

SceneManager& SceneManager::getInstance(){
	assert(instance);
	return *instance;
}

void SceneManager::update(){
	if(! sceneStack.empty()){
		sceneStack.top()->update();
	}
}

void SceneManager::draw(){
	if(! sceneStack.empty()){
		sceneStack.top()->draw();
	}
}

void SceneManager::change(IScene* scene){
	while(! sceneStack.empty()){
		deleteTop();
	}

	sceneStack.push(scene);
}

void SceneManager::ride(IScene* scene){
	sceneStack.push(scene);
}

void SceneManager::back(int n){
	assert(n <= sceneStack.size());

	for(int i = 0; i < n; ++i){
		deleteTop();
	}
}

void SceneManager::deleteTop(){
	if(! sceneStack.empty()){
		IScene* scene = sceneStack.top();
		delete scene;
		scene = nullptr;
		sceneStack.pop();
	}
}