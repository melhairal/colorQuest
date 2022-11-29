#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

//プロトタイプ宣言
void battlePlayer();
void battleEnemy();
void battleUi();
void gameOver();
void stageClear();
extern bool menu_enter;

bool init_battle = false;

//背景
int img_step = 0;
int img_bg = 0;
const int BG_X = 512;
const int BG_Y = 400;

extern bool delete_ui;

void sceneBattle() {
	if (!init_battle) {
		img_step = LoadGraph("graphics/bg/step.png");
		img_bg = LoadGraph("graphics/bg/forest.png");
		init_battle = true;
	}
	
	//フィールド生成
	DrawRotaGraph(BG_X, BG_Y, 1, 0, img_bg, true);
	DrawExtendGraph(0, 630, 1026, 770, img_step, true);

	//敵動作
	if (play_mode != STAGE_CLEAR)
		battleEnemy();

	switch (play_mode) {
	case STAGE_PLAY:
		//プレイヤー動作
		battlePlayer();
		//メニュー
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			PlaySoundMem(se_menu, DX_PLAYTYPE_BACK);
			menu_enter = false;
			now_scene = SCENE_BATTLE;
			scene = SCENE_MENU;
		}
		break;
	case GAME_OVER:
		//ゲームオーバー
		gameOver();
		break;
	case STAGE_CLEAR:
		//ステージクリア
		stageClear();
		break;
	}

	//UI表示
	if (!delete_ui) {
		battleUi();
	}
}