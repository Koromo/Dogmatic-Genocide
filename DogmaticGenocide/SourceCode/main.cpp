#include "DxLib.h"
#include "GameMain.h"
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	Window* window = new Window("Window.dat");

	if(window->setUp()){
		if(DxLib_Init() == 0){
			GameMain* gameMain = new GameMain();

			if(gameMain->init()){
				gameMain->run();
			}

			gameMain->end();
		}
		try{
			DxLib_End();
		} catch(...) {

		}
	}

	delete window;
	window = nullptr;

	return 0;
}