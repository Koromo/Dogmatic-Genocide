#include "Pause.h"
#include "Title.h"

Pause::Pause(Game* game, IDevice* device) :
game(game),
device(device),
cnt(1)
{ }

void Pause::update(){
	if(device->frameInput(KEY_LEFT)) --cnt;
	if(device->frameInput(KEY_RIGHT)) ++cnt;

	if(cnt < 0) cnt = 0;
	if(cnt > 1) cnt = 1;

	if(device->frameInput(KEY_DECIDE)){
		switch(cnt){
		case 0:
			SceneMng.change(new Title(device));
			break;
		case 1:
			SceneMng.back(1);
			break;
		default:
			break;
		}
	}

	if (device->frameInput(KEY_PAUSE))
	{
		SceneMng.back(1);
		return;
	}
}

void Pause::draw(){
	game->draw();
	DrawString(120, 100, "タイトルにもどる？", GetColor(255, 255, 255));
	DrawCircle(100 * (cnt + 1) + 5, 206, 10, GetColor(255, 0, 0), TRUE);
	DrawString(120, 200, "はい", GetColor(255, 255, 255));
	DrawString(220, 200, "いいえ", GetColor(255, 255, 255));
}