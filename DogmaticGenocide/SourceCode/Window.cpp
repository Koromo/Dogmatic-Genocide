#include "Window.h"
#include "DxLib.h"

Window::Window(std::string fileName) :
fileName(fileName)
{ }

bool Window::setUp(){
	int n;
	int fileHandle = FileRead_open(fileName.c_str());

	if(fileHandle == 0){
		return false;
	}

	FileRead_scanf(fileHandle, "%d", &n);
	FileRead_close(fileHandle);

	if(n == TRUE || n == FALSE){
		ChangeWindowMode(n);
	} else {
		return false;
	}

	SetMainWindowText("DogmaticGenocide ver0.01");
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}