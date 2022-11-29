#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

bool init_title = false;
void titleOption();

//背景画像
int img_title = 0;
const int TITLE_X = 490;
const int TITLE_Y = 390;
//選択し
const int OFF_X = 430;
const int ON_X = OFF_X + 10;
int new_x = 0;
int load_x = 0;
const int NEW_Y = 500;
const int LOAD_Y = 550;
int new_col = 0;
int load_col = 0;
//項目数
const int NUM = 1;
//選択色
const int ON_COL = RGB(10, 52, 134);
const int OFF_COL = RGB(130, 131, 134);
//カーソル
int sel = 0;
const int SEL_X = OFF_X - 33;
int sel_y = 0;
//オプション画面
bool option = false;
bool title_enter_wait = false;
int sel_option = 2;

void sceneTitle() {

	if (!init_title) {
		//背景画像取得
		img_title = LoadGraph("graphics/bg/title.png");
		PlaySoundMem(sound_title, DX_PLAYTYPE_LOOP, 1);
		
		init_title = true;
	}

	//背景
	DrawRotaGraph(TITLE_X, TITLE_Y, 1, 0, img_title, true);

	new_x = OFF_X;
	load_x = OFF_X;
	new_col = OFF_COL;
	load_col = OFF_COL;
	
	//選択状態
	switch (sel)
	{
	case 0:
		sel_y = NEW_Y;
		new_col = ON_COL;
		new_x = ON_X;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !option) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			StopSoundMem(sound_title);
			PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
			scene = SCENE_PLAY;
		}
		break;
	case 1:
		sel_y = LOAD_Y;
		load_col = ON_COL;
		load_x = ON_X;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !option) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			sel_option = 2;
			title_enter_wait = true;
			option = true;
		}
		break;
	default:
		break;
	}

	//キー入力で状態遷移
	if (NUM > sel && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) && !option) {
		PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		sel += 1;
	}
	if (0 < sel && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) && !option) {
		PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		sel -= 1;
	}

	//画面表示
	SetFontSize(30);
	DrawStringToHandle(new_x, NEW_Y, "はじめる", new_col, font32);
	DrawStringToHandle(load_x, LOAD_Y, "オプション", load_col, font32);
	DrawStringEx(SEL_X , sel_y, ON_COL, "●");

	if (option == true) {
		titleOption();
	}
	title_enter_wait = false;
}

bool init_option = false;
int img_option_window;
int img_slider_base;
int img_slider[2];
int img_option_close[2];
const int OPTION_X = 570;
const int OPTION_Y[3] = { 360,410,470 };
const int OPTION_SLIDER_X[11] = {440,466,492,518,544,570,596,622,648,674,690};
//選択状況
int vol[2] = { 10,10 };
int volume[11] = { 0,30,55,80,105,130,155,180,205,230,255 };

extern bool sonota_option;


void titleOption() {
	if (!init_option) {
		img_option_window = LoadGraph("graphics/bg/menu_window_05.png");
		img_slider_base = LoadGraph("graphics/bg/slider_bar.png");
		img_slider[0] = LoadGraph("graphics/bg/slider_handle.png");
		img_slider[1] = LoadGraph("graphics/bg/slider_handle_active.png");
		img_option_close[0] = LoadGraph("graphics/bg/button_round.png");
		img_option_close[1] = LoadGraph("graphics/bg/button_round_active.png");
		init_option = true;
	}

	//枠表示
	DrawRotaGraph(512, 400, 1, 0, img_option_window, true);
	DrawRotaGraph(OPTION_X, OPTION_Y[0], 2, 0, img_slider_base, true);
	DrawRotaGraph(OPTION_X, OPTION_Y[1], 2, 0, img_slider_base, true);
	DrawRotaGraph(512, OPTION_Y[2], 1, 0, img_option_close[0], true);

	//スライダー表示
	DrawRotaGraph(OPTION_SLIDER_X[vol[0]], OPTION_Y[0], 2, 0, img_slider[0], true);
	DrawRotaGraph(OPTION_SLIDER_X[vol[1]], OPTION_Y[1], 2, 0, img_slider[0], true);
	//選択中
	if (sel_option != 2) {
		DrawRotaGraph(OPTION_SLIDER_X[vol[sel_option]], OPTION_Y[sel_option], 2, 0, img_slider[1], true);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) && vol[sel_option] > 0) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			vol[sel_option] -= 1;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) && vol[sel_option] < 10) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			vol[sel_option] += 1;
		}
	}
	else {
		DrawRotaGraph(512, OPTION_Y[2], 1, 0, img_option_close[1], true);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !title_enter_wait) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			option = false;
			sonota_option = false;
		}
	}

	//文字
	DrawStringToHandle(OPTION_X - 260, OPTION_Y[0] - 16, "BGM", BROWN, font32);
	DrawStringToHandle(OPTION_X - 260, OPTION_Y[1] - 16, "SE", BROWN, font32);
	DrawStringToHandle(490, OPTION_Y[2] - 8, "閉じる", -1, font16);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) && sel_option > 0) {
		PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		sel_option -= 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) && sel_option < 2) {
		PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		sel_option += 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		PlaySoundMem(se_esc, DX_PLAYTYPE_BACK);
		option = false;
		sonota_option = false;
	}

	//音量設定
	//BGM
	ChangeVolumeSoundMem(volume[vol[0]], sound_title);
	ChangeVolumeSoundMem(volume[vol[0]], sound_play);
	ChangeVolumeSoundMem(volume[vol[0]], sound_shop);
	ChangeVolumeSoundMem(volume[vol[0]], sound_clear);
	ChangeVolumeSoundMem(volume[vol[0]], sound_gameover);
	ChangeVolumeSoundMem(volume[vol[0]], sound_battle);
	ChangeVolumeSoundMem(volume[vol[0]], sound_battle_magician);
	ChangeVolumeSoundMem(volume[vol[0]], sound_battle_fairy);
	ChangeVolumeSoundMem(volume[vol[0]], sound_battle_doragon);
	//SE
	ChangeVolumeSoundMem(volume[vol[1]], se_enter);
	ChangeVolumeSoundMem(volume[vol[1]], se_esc);
	ChangeVolumeSoundMem(volume[vol[1]], se_select);
	ChangeVolumeSoundMem(volume[vol[1]], se_menu);
	ChangeVolumeSoundMem(volume[vol[1]], se_buy);
	ChangeVolumeSoundMem(volume[vol[1]], se_damage);
	ChangeVolumeSoundMem(volume[vol[1]], se_sowrd);
	ChangeVolumeSoundMem(volume[vol[1]], se_bomb);
	ChangeVolumeSoundMem(volume[vol[1]], se_beam);
	ChangeVolumeSoundMem(volume[vol[1]], se_warp);
	ChangeVolumeSoundMem(volume[vol[1]], se_change);
	ChangeVolumeSoundMem(volume[vol[1]], se_sprint);
}