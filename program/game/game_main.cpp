#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"

int scene = 0;
int font16 = 0;
int font32 = 0;
bool init = false;

//プロトタイプ宣言
void debugGame();
void sceneTitle();
void scenePlay();
void sceneBattle();
void sceneMenu();
void sceneShop();
void getSound();

void gameMain(float delta_time) {

	if (!init) {
		debugGame();
		//フォント読み込み
		font16 = LoadFontDataToHandle("font/Novelpop16.dft", 0);
		font32 = LoadFontDataToHandle("font/Novelpop32.dft", 0);
		getSound();
		init = true;
	}
	
	//シーン切り替え
	switch (scene)
	{
	case SCENE_TITLE:
		sceneTitle();
		break;
	case SCENE_PLAY:
		scenePlay();
		break;
	case SCENE_BATTLE:
		sceneBattle();
		break;
	case SCENE_MENU:
		sceneMenu();
		break;
	case SCENE_SHOP:
		sceneShop();
		break;
	default:
		break;
	}

}