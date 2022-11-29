#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

bool init_menu = false;

//プロトタイプ宣言
void menuTuyosa();
void menuSkill();
void menuSoubi();
void menuDougu();
void menuSonota();

void rlvUp();
void glvUp();
void blvUp();

//どこに戻るか
int now_scene = 0;

//背景
extern int img_title;
const int MENU_BG_X = 512;
const int MENU_BG_Y = 350;

//ウィンドウ画像用
int img_menu_window = 0;
const int MENU_WINDOW_X = 512;
const int MENU_WINDOW_Y = 440;

//ウィンドウ画像（つよさ画面項目）
int img_menu_tuyosa[2] = { 0 };
int img_menu_tuyosa_waku = 0;
int img_menu_tuyosa_equip = 0;

//ウィンドウ画面（スキル画面用）
int img_menu_skill[2] = { 0 };

//ウィンドウ画面（装備画面用）
int img_menu_equ1 = 0;
int img_menu_equ2 = 0;
int img_equ_sel = 0;
int img_equ_cur = 0;

//アイコン画像
int img_icon_eq[4] = { 0 };
int img_icon_star = 0;
int img_icon_hart = 0;
int img_icon_item_type[3] = { 0 };

//hpバーの画像
extern int img_hp_base;
extern int img_hp_frame;
extern int img_hp_gauge;

//タブ
int img_menu_tab[2] = { 0 };
const int MENU_TAB_X[5] = { 110,310,510,710,910 };
const int MENU_TAB_Y = 100;
const int MENU_SEL_TAB_Y = 80;
const int MENU_TAB_NAME_X[5] = { MENU_TAB_X[0] - 47,MENU_TAB_X[1] - 47,MENU_TAB_X[2] - 47,MENU_TAB_X[3] - 47,MENU_TAB_X[4] - 47 };
const int MENU_TAB_NAME_Y = MENU_TAB_Y - 25;
const int MENU_SEL_TAB_NAME_Y = MENU_TAB_Y - 35;
int menu_tab_name_y[5] = { 0 };

//メッセージウィンドウ
int img_menu_mes = 0;
const int MENU_MES_X1 = 512;
const int MENU_MES_Y1 = 680;
//説明文座標
const int MENU_MES_X2 = 100;
const int MENU_MES_Y2 = 660;

//メッセージ選択し
int img_menu_cur[2] = { 0 };


//項目数
const int MENU_NUM = 4;
//選択状態
int menu_sel = 0;
bool menu_enter = false;
bool wait_esc = false;
bool wait_enter = false;

void sceneMenu() {

	if (!init_menu) {
		//画像読み込み
		img_menu_window = LoadGraph("graphics/bg/menu_window_01.png");
		img_menu_tab[0] = LoadGraph("graphics/bg/tab_01.png");
		img_menu_tab[1] = LoadGraph("graphics/bg/tab_05.png");

		img_menu_mes = LoadGraph("graphics/bg/message_frame_02_light.png");
		img_menu_cur[0] = LoadGraph("graphics/bg/button_round.png");
		img_menu_cur[1] = LoadGraph("graphics/bg/button_round_active.png");

		img_menu_tuyosa[0] = LoadGraph("graphics/bg/menu_window_05.png");
		img_menu_tuyosa[1] = LoadGraph("graphics/bg/menu_window_03.png");

		img_menu_tuyosa_waku = LoadGraph("graphics/bg/menu_window_05.png");
		img_menu_tuyosa_equip = LoadGraph("graphics/bg/caption_01.png");

		img_menu_skill[0] = LoadGraph("graphics/bg/skill_window_02.png");
		img_menu_skill[1] = LoadGraph("graphics/bg/skill_window_01.png");

		img_menu_equ1 = LoadGraph("graphics/bg/equip_window_01.png");
		img_menu_equ2 = LoadGraph("graphics/bg/equip_window_02.png");
		img_equ_sel = LoadGraph("graphics/bg/toggle_tab_active.png");
		img_equ_cur = LoadGraph("graphics/bg/equip_cursol.png");

		img_icon_eq[RED] = LoadGraph("graphics/icon/icon002.png");
		img_icon_eq[GREEN] = LoadGraph("graphics/icon/icon001-1.png");
		img_icon_eq[BLUE] = LoadGraph("graphics/icon/icon006.png");
		img_icon_eq[ARM] = LoadGraph("graphics/icon/icon015.png");
		img_icon_star = LoadGraph("graphics/icon/sticon4e-3.png");
		img_icon_hart = LoadGraph("graphics/icon/sticon3b-3.png");

		img_icon_item_type[GRASS] = LoadGraph("graphics/icon/icon029.png");
		img_icon_item_type[PORTION] = LoadGraph("graphics/icon/icon030.png");
		img_icon_item_type[KEY] = LoadGraph("graphics/icon/icon019.png");

		img_hp_base = LoadGraph("graphics/hp/gauge_background.png");
		img_hp_frame = LoadGraph("graphics/hp/gauge_frame.png");
		img_hp_gauge = LoadGraph("graphics/hp/gauge_bar_pink.png");

		init_menu = true;
	}

	//座標初期化
	for (int i = 0; i < 5; i++) {
		menu_tab_name_y[i] = MENU_TAB_NAME_Y;
	}
	menu_tab_name_y[menu_sel] = MENU_SEL_TAB_NAME_Y;

	//画像表示
	//背景
	DrawRotaGraph(MENU_BG_X, MENU_BG_Y, 1, 0, img_title, true);
	//タブ
	for (int i = 0; i < 5; i++) {
		DrawRotaGraph(MENU_TAB_X[i], MENU_TAB_Y, 2, 0, img_menu_tab[1], true);
	}
	//選択中タブ
	DrawRotaGraph(MENU_TAB_X[menu_sel], MENU_SEL_TAB_Y, 2, 0, img_menu_tab[0], true);
	//ウィンドウ
	DrawRotaGraph(MENU_WINDOW_X, MENU_WINDOW_Y, 1, 0, img_menu_window, true);

	//タブ文字
	DrawStringToHandle(MENU_TAB_NAME_X[0], menu_tab_name_y[0], "つよさ", -1, font32);
	DrawStringToHandle(MENU_TAB_NAME_X[1], menu_tab_name_y[1], "スキル", -1, font32);
	DrawStringToHandle(MENU_TAB_NAME_X[2], menu_tab_name_y[2], "そうび", -1, font32);
	DrawStringToHandle(MENU_TAB_NAME_X[3], menu_tab_name_y[3], "どうぐ", -1, font32);
	DrawStringToHandle(MENU_TAB_NAME_X[4], menu_tab_name_y[4], "そのた", -1, font32);

	switch (menu_sel)
	{
	case 0:
		menuTuyosa();
		break;
	case 1:
		menuSkill();
		break;
	case 2:
		menuSoubi();
		break;
	case 3:
		menuDougu();
		break;
	case 4:
		menuSonota();
		break;
	}

	if (!menu_enter) {
		//キー入力で状態遷移
		if (menu_sel > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT))
			menu_sel -= 1;
		if (menu_sel < MENU_NUM && tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT))
			menu_sel += 1;

		//エンターキーで決定
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			menu_enter = true;
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
		}

		//戻る
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			scene = now_scene;
		}
	}

	if (menu_enter == true && !wait_esc && tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE))
		menu_enter = false;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		PlaySoundMem(se_esc, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) || tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
		PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
	}

	wait_esc = false;
	wait_enter = false;
}

//キャラアニメーション
int menu_count = 0;
int menu_frame = 0;
//枠座標
const int TUYOSA_WAKU_X = 250;
const int TUYOSA_WAKU_Y = 500;
//キャラ画像座標
const int MENU_P_X = 85;
const int MENU_P_Y = 250;
//hpバーの座標
const int MENU_HP_X = 280;
const int MENU_HP_Y = 280;
//hpゲージの横幅
const int MENU_HP_W = 234;
const int MENU_HP_H = 12;
//hpゲージの座標
const int MENU_GAUGE_X1 = MENU_HP_X - MENU_HP_W / 2;
const int MENU_GAUGE_Y1 = MENU_HP_Y - MENU_HP_H / 2;
const int MENU_GAUGE_Y2 = MENU_HP_Y + MENU_HP_H / 2;
int menu_gauge_x2 = 0;
//hp数値表示座標
const int MENU_HP_NUM_X1 = MENU_HP_X - 40;
const int MENU_HP_NUM_X2 = MENU_HP_X - 90;
const int MENU_HP_NUM_Y = MENU_HP_Y - 60;
//EXP座標
const int MENU_EXP_X = 100;
const int MENU_EXP_Y = 680;

//装備枠座標
const int TUYOSA_EQUIP_X = 250;
const int TUYOSA_EQUIP_Y = 400;
const int TUYOSA_EQUIP_NAME_X = 202;
const int TUYOSA_EQUIP_NAME_Y = 382;

//レベルアップ枠座標
const int MENU_LV_FRAME_X = 740;
const int MENU_LV_FRAME_Y[3] = { 230,440,650 };
//属性画像座標
const int MENU_LV_COLOR_X = 600;
const int MENU_LV_COLOR_Y[3] = { 210,420,630 };
//Lv表示座標
const int MENU_LV_NUM_X = 660;
const int MENU_LV_NUM_Y[3] = { 190,400,610 };
//SP表示座標
const int MENU_SP_NUM_X = 660;
const int MENU_SP_NUM_Y[3] = { 220,430,640 };
//必要経験値座標
const int MENU_LV_NEXT_X = 590;
const int MENU_LV_NEXT_Y[3] = { 270,480,690 };

//選択し座標
const int TUYOSA_YES_X[2] = { 720,890 };
const int TUYOSA_YES_Y = 620;

//色
int tuyosa_col[3] = { 0 };
//選択状態
int tuyosa_sel = 0;
int tuyosa_enter_sel = 0;

bool tuyosa_enter = false;
bool tuyosa_husoku = false;
bool tuyosa_enter_wait = false;
bool tuyosa_max = false;

void menuTuyosa() {
	menu_count = (menu_count + 1) % 20;
	if (menu_count == 19)
		menu_frame = (menu_frame + 1) % 3;

	//色の初期化
	for (int i = 0; i < 3; i++) {
		tuyosa_col[i] = BROWN;
	}

	//枠表示
	DrawRotaGraph(TUYOSA_WAKU_X, TUYOSA_WAKU_Y, 1, 0, img_menu_tuyosa_waku, true);

	//キャラ表示
	DrawRotaGraph(MENU_P_X, MENU_P_Y, 3, 0, player.img_[player.mode_][menu_frame], true);
	//HPゲージの横幅計算
	menu_gauge_x2 = MENU_GAUGE_X1 + MENU_HP_W * ((double)player.hp_ / (double)player.mhp_);
	//HPバー表示
	DrawRotaGraph(MENU_HP_X, MENU_HP_Y, 1.5f, 0, img_hp_base, true);
	DrawExtendGraph(MENU_GAUGE_X1, MENU_GAUGE_Y1, menu_gauge_x2, MENU_GAUGE_Y2, img_hp_gauge, true);
	DrawRotaGraph(MENU_HP_X, MENU_HP_Y, 1.5f, 0, img_hp_frame, true);
	//HP数値表示
	DrawFormatStringToHandle(MENU_HP_NUM_X1, MENU_HP_NUM_Y, BROWN, font32, "%d", player.hp_);
	DrawFormatStringToHandle(MENU_HP_NUM_X2, MENU_HP_NUM_Y, BROWN, font32, "HP        / %d", player.mhp_);
	DrawRotaGraph(MENU_HP_NUM_X2 - 20, MENU_HP_NUM_Y + 18, 1.5F, 0, img_icon_hart, true);
	//装備変更による最大HP更新
	player.mhp_ = player.default_hp_ + eq_now[RED].hp_ + eq_now[BLUE].hp_ + eq_now[GREEN].hp_ + eq_now[ARM].hp_;

	//EXP表示
	DrawFormatStringToHandle(MENU_EXP_X, MENU_EXP_Y, BROWN, font32, "EXP %d", player.exp_);
	DrawRotaGraph(MENU_EXP_X - 30, MENU_EXP_Y + 15, 1.5F, 0, img_icon_star, true);

	//装備枠表示
	DrawRotaGraph(TUYOSA_EQUIP_X, TUYOSA_EQUIP_Y, 1, 0, img_menu_tuyosa_equip, true);
	DrawFormatStringToHandle(TUYOSA_EQUIP_NAME_X, TUYOSA_EQUIP_NAME_Y, -1, font32, "そうび");

	//装備中の装備表示
	DrawFormatStringToHandle(TUYOSA_EQUIP_NAME_X - 100, TUYOSA_EQUIP_NAME_Y + 50, BROWN, font32, "%s", eq_now[RED].name_.c_str());
	DrawFormatStringToHandle(TUYOSA_EQUIP_NAME_X - 100, TUYOSA_EQUIP_NAME_Y + 90, BROWN, font32, "%s", eq_now[GREEN].name_.c_str());
	DrawFormatStringToHandle(TUYOSA_EQUIP_NAME_X - 100, TUYOSA_EQUIP_NAME_Y + 130, BROWN, font32, "%s", eq_now[BLUE].name_.c_str());
	DrawFormatStringToHandle(TUYOSA_EQUIP_NAME_X - 100, TUYOSA_EQUIP_NAME_Y + 170, BROWN, font32, "%s", eq_now[ARM].name_.c_str());

	//アイコン表示
	DrawRotaGraph(TUYOSA_EQUIP_NAME_X - 130, TUYOSA_EQUIP_NAME_Y + 65, 1.5F, 0, img_icon_eq[RED], true);
	DrawRotaGraph(TUYOSA_EQUIP_NAME_X - 130, TUYOSA_EQUIP_NAME_Y + 105, 1.5F, 0, img_icon_eq[GREEN], true);
	DrawRotaGraph(TUYOSA_EQUIP_NAME_X - 130, TUYOSA_EQUIP_NAME_Y + 145, 1.5F, 0, img_icon_eq[BLUE], true);
	DrawRotaGraph(TUYOSA_EQUIP_NAME_X - 130, TUYOSA_EQUIP_NAME_Y + 185, 1.5F, 0, img_icon_eq[ARM], true);

	//スキルレベルアップ
	//枠表示
	DrawRotaGraph(MENU_LV_FRAME_X, MENU_LV_FRAME_Y[0], 1, 0, img_menu_tuyosa[0], true);
	DrawRotaGraph(MENU_LV_FRAME_X, MENU_LV_FRAME_Y[1], 1, 0, img_menu_tuyosa[0], true);
	DrawRotaGraph(MENU_LV_FRAME_X, MENU_LV_FRAME_Y[2], 1, 0, img_menu_tuyosa[0], true);

	if (menu_enter == true) {
		//選択枠表示
		DrawRotaGraph(MENU_LV_FRAME_X, MENU_LV_FRAME_Y[tuyosa_sel], 1, 0, img_menu_tuyosa[1], true);
		//選択中の色を変える
		tuyosa_col[tuyosa_sel] = -1;
	}

	//属性画像表示
	DrawRotaGraph(MENU_LV_COLOR_X, MENU_LV_COLOR_Y[0], 0.2F, 0, color[RED], true);
	DrawRotaGraph(MENU_LV_COLOR_X, MENU_LV_COLOR_Y[1], 0.2F, 0, color[GREEN], true);
	DrawRotaGraph(MENU_LV_COLOR_X, MENU_LV_COLOR_Y[2], 0.2F, 0, color[BLUE], true);

	//Lv表示
	if (player.r_lv_ == 20) {
		DrawFormatStringToHandle(MENU_LV_NUM_X, MENU_LV_NUM_Y[0], YELLOW, font32, "Lv MAX");
	}
	else {
		DrawFormatStringToHandle(MENU_LV_NUM_X, MENU_LV_NUM_Y[0], tuyosa_col[RED], font32, "Lv %d", player.r_lv_);
	}
	if (player.g_lv_ == 20) {
		DrawFormatStringToHandle(MENU_LV_NUM_X, MENU_LV_NUM_Y[1], YELLOW, font32, "Lv MAX");
	}
	else {
		DrawFormatStringToHandle(MENU_LV_NUM_X, MENU_LV_NUM_Y[1], tuyosa_col[GREEN], font32, "Lv %d", player.g_lv_);
	}
	if (player.b_lv_ == 20) {
		DrawFormatStringToHandle(MENU_LV_NUM_X, MENU_LV_NUM_Y[2], YELLOW, font32, "Lv MAX");
	}
	else {
		DrawFormatStringToHandle(MENU_LV_NUM_X, MENU_LV_NUM_Y[2], tuyosa_col[BLUE], font32, "Lv %d", player.b_lv_);
	}

	//スキルポイント表示
	DrawFormatStringToHandle(MENU_SP_NUM_X, MENU_SP_NUM_Y[0], tuyosa_col[RED], font32, "SP %d", player.r_sp_);
	DrawFormatStringToHandle(MENU_SP_NUM_X, MENU_SP_NUM_Y[1], tuyosa_col[GREEN], font32, "SP %d", player.g_sp_);
	DrawFormatStringToHandle(MENU_SP_NUM_X, MENU_SP_NUM_Y[2], tuyosa_col[BLUE], font32, "SP %d", player.b_sp_);

	//必要経験値
	DrawFormatStringToHandle(MENU_LV_NEXT_X, MENU_LV_NEXT_Y[0], tuyosa_col[RED], font32, "次のレベルまで  %d", maxexp[player.r_lv_ - 1]);
	DrawFormatStringToHandle(MENU_LV_NEXT_X, MENU_LV_NEXT_Y[1], tuyosa_col[GREEN], font32, "次のレベルまで  %d", maxexp[player.g_lv_ - 1]);
	DrawFormatStringToHandle(MENU_LV_NEXT_X, MENU_LV_NEXT_Y[2], tuyosa_col[BLUE], font32, "次のレベルまで  %d", maxexp[player.b_lv_ - 1]);

	//レベルマックス処理
	if (tuyosa_max == true) {
		wait_esc = true;
		//メッセージ表示
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawStringToHandle(MENU_MES_X2, MENU_MES_Y2, "レベルが上限に達しています", BROWN, font32);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			tuyosa_enter_wait = true;
			tuyosa_max = false;
		}
	}
	//経験値不足の処理
	if (tuyosa_husoku == true) {
		wait_esc = true;
		//メッセージ表示
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawStringToHandle(MENU_MES_X2, MENU_MES_Y2, "経験値が足りません", BROWN, font32);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			tuyosa_enter_wait = true;
			tuyosa_husoku = false;
		}
	}
	if (tuyosa_enter == true) {

		//キー入力で遷移
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT))
			tuyosa_enter_sel = 0;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT))
			tuyosa_enter_sel = 1;

		//メッセージ表示
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawStringToHandle(MENU_MES_X2, MENU_MES_Y2, "経験値を消費してレベルを上げますか？", BROWN, font32);

		//選択し表示
		DrawRotaGraph(TUYOSA_YES_X[0], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[0], true);
		DrawRotaGraph(TUYOSA_YES_X[1], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[0], true);
		DrawRotaGraph(TUYOSA_YES_X[tuyosa_enter_sel], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[1], true);

		DrawStringToHandle(TUYOSA_YES_X[0] - 30, TUYOSA_YES_Y - 18, "はい", -1, font32);
		DrawStringToHandle(TUYOSA_YES_X[1] - 45, TUYOSA_YES_Y - 18, "いいえ", -1, font32);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			switch (tuyosa_enter_sel) {
			case 0:
				switch (tuyosa_sel)
				{
				case 0:
					if (player.r_lv_ == 20) {
						tuyosa_max = true;
					}
					else if (player.exp_ < maxexp[player.r_lv_ - 1]) {
						tuyosa_husoku = true;
					}
					else if (player.exp_ >= maxexp[player.r_lv_ - 1] && player.r_lv_ < 20) {
						player.exp_ = player.exp_ - maxexp[player.r_lv_ - 1];
						player.r_lv_++;
						rlvUp();
					}
					break;
				case 1:
					if (player.g_lv_ == 20) {
						tuyosa_max = true;
					}
					else if (player.exp_ < maxexp[player.g_lv_ - 1]) {
						tuyosa_husoku = true;
					}
					else if (player.exp_ >= maxexp[player.g_lv_ - 1] && player.g_lv_ < 20) {
						player.exp_ = player.exp_ - maxexp[player.g_lv_ - 1];
						player.g_lv_++;
						glvUp();
					}
					break;
				case 2:
					if (player.b_lv_ == 20) {
						tuyosa_max = true;
					}
					else if (player.exp_ < maxexp[player.b_lv_ - 1]) {
						tuyosa_husoku = true;
					}
					else if (player.exp_ >= maxexp[player.b_lv_ - 1] && player.b_lv_ < 20) {
						player.exp_ = player.exp_ - maxexp[player.b_lv_ - 1];
						player.b_lv_++;
						blvUp();
					}
					break;
				}
				tuyosa_enter_wait = true;
				tuyosa_enter = false;
				break;
			case 1:
				tuyosa_enter_wait = true;
				tuyosa_enter = false;
				break;
			}
		}
		//戻る
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			tuyosa_enter = false;
			wait_esc = true;
		}
	}
	if (menu_enter == true && !tuyosa_enter && !tuyosa_husoku && !tuyosa_max) {

		//キー入力で遷移
		if (tuyosa_sel > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
			tuyosa_sel--;
		if (tuyosa_sel < 2 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))
			tuyosa_sel++;

		//レベルアップ
		if (!tuyosa_enter_wait && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			tuyosa_enter_sel = 1;
			tuyosa_enter = true;
		}
	}
	tuyosa_enter_wait = false;
}

//スキルウィンドウ座標
const int MENU_SKILL_X[3] = { 230,540,850 };
const int MENU_SKILL_Y[3] = { 200,360,520 };
//属性座標
const int MENU_SKILL_COLOR_X = 40;
const int MENU_SKILL_COLOR_Y[3] = { 200,360,520 };
//色
int menu_skill_col[3][3] = { 0 };

//選択状態
int skill_sel_x = 0;
int skill_sel_y = 0;
int skill_enter_sel = 0;

bool skill_enter = false;
bool skill_enter_wait = false;
bool skill_husoku = false;
bool skill_max = false;

void menuSkill() {

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			//枠表示
			DrawRotaGraph(MENU_SKILL_X[k], MENU_SKILL_Y[i], 1, 0, img_menu_skill[0], true);
			//色初期化
			menu_skill_col[i][k] = BROWN;
		}
	}
	if (menu_enter == true) {
		//選択中の枠表示
		DrawRotaGraph(MENU_SKILL_X[skill_sel_x], MENU_SKILL_Y[skill_sel_y], 1, 0, img_menu_skill[1], true);
		//選択中の色変更
		menu_skill_col[skill_sel_y][skill_sel_x] = -1;
	}
	//属性表示
	DrawRotaGraph(MENU_SKILL_COLOR_X, MENU_SKILL_COLOR_Y[0], 0.1F, 0, color[RED], true);
	DrawRotaGraph(MENU_SKILL_COLOR_X, MENU_SKILL_COLOR_Y[1], 0.1F, 0, color[GREEN], true);
	DrawRotaGraph(MENU_SKILL_COLOR_X, MENU_SKILL_COLOR_Y[2], 0.1F, 0, color[BLUE], true);
	//スキルポイント表示
	DrawFormatStringToHandle(MENU_SKILL_COLOR_X - 17, MENU_SKILL_COLOR_Y[0] + 30, BROWN, font16, "SP %d", player.r_sp_);
	DrawFormatStringToHandle(MENU_SKILL_COLOR_X - 17, MENU_SKILL_COLOR_Y[1] + 30, BROWN, font16, "SP %d", player.g_sp_);
	DrawFormatStringToHandle(MENU_SKILL_COLOR_X - 17, MENU_SKILL_COLOR_Y[2] + 30, BROWN, font16, "SP %d", player.b_sp_);

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			//スキル画像表示
			DrawRotaGraph(MENU_SKILL_X[k] - 80, MENU_SKILL_Y[i], 0.2F, 0, skill[i][k].img_[0], true);
			//スキルベル表示
			if (skill[i][k].slv_ == 5) {
				DrawFormatStringToHandle(MENU_SKILL_X[k] - 20, MENU_SKILL_Y[i] - 50, YELLOW, font32, "SLv  MAX");
			}
			else {
				DrawFormatStringToHandle(MENU_SKILL_X[k] - 20, MENU_SKILL_Y[i] - 50, menu_skill_col[i][k], font32, "SLv     %d", skill[i][k].slv_ + 1);
			}
			//ステータス表示
			DrawFormatStringToHandle(MENU_SKILL_X[k] - 20, MENU_SKILL_Y[i] - 20, menu_skill_col[i][k], font32, "ATK  %d", skill[i][k].atk_[skill[i][k].slv_]);
			DrawFormatStringToHandle(MENU_SKILL_X[k] - 20, MENU_SKILL_Y[i] + 10, menu_skill_col[i][k], font32, "CD   %1.1f秒", skill[i][k].cd_[skill[i][k].slv_]);
		}
	}
	//レベルマックス
	if (skill_max == true) {
		wait_esc = true;
		//メッセージ表示
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawStringToHandle(MENU_MES_X2, MENU_MES_Y2, "レベルが上限に達しています", BROWN, font32);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			skill_enter_wait = true;
			skill_max = false;
		}
	}
	//SP不足
	if (skill_husoku == true) {
		wait_esc = true;
		//メッセージ表示
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawStringToHandle(MENU_MES_X2, MENU_MES_Y2, "SPが足りません", BROWN, font32);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			skill_enter_wait = true;
			skill_husoku = false;
		}
	}
	//スキルレベルアップ処理
	if (skill_enter == true) {
		//キー入力で遷移
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT))
			skill_enter_sel = 0;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT))
			skill_enter_sel = 1;

		//メッセージ表示
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawStringToHandle(MENU_MES_X2, MENU_MES_Y2, "SPを消費してスキルレベルを上げますか？", BROWN, font32);

		//選択し表示
		DrawRotaGraph(TUYOSA_YES_X[0], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[0], true);
		DrawRotaGraph(TUYOSA_YES_X[1], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[0], true);
		DrawRotaGraph(TUYOSA_YES_X[skill_enter_sel], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[1], true);

		DrawStringToHandle(TUYOSA_YES_X[0] - 30, TUYOSA_YES_Y - 18, "はい", -1, font32);
		DrawStringToHandle(TUYOSA_YES_X[1] - 45, TUYOSA_YES_Y - 18, "いいえ", -1, font32);

		//スキルレベルアップ処理
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			switch (skill_enter_sel) {
			case 0:
				switch (skill_sel_y) {
				case RED:
					if (skill[skill_sel_y][skill_sel_x].slv_ == 5) {
						skill_max = true;
					}
					else if (player.r_sp_ == 0) {
						skill_husoku = true;
					}
					else if (player.r_sp_ > 0 && skill[skill_sel_y][skill_sel_x].slv_ < 5) {
						player.r_sp_--;
						skill[skill_sel_y][skill_sel_x].slv_++;
					}
					break;
				case GREEN:
					if (skill[skill_sel_y][skill_sel_x].slv_ == 5) {
						skill_max = true;
					}
					else if (player.g_sp_ == 0) {
						skill_husoku = true;
					}
					else if (player.g_sp_ > 0 && skill[skill_sel_y][skill_sel_x].slv_ < 5) {
						player.g_sp_--;
						skill[skill_sel_y][skill_sel_x].slv_++;
					}
					break;
				case BLUE:
					if (skill[skill_sel_y][skill_sel_x].slv_ == 5) {
						skill_max = true;
					}
					else if (player.b_sp_ == 0) {
						skill_husoku = true;
					}
					else if (player.b_sp_ > 0 && skill[skill_sel_y][skill_sel_x].slv_ < 5) {
						player.b_sp_--;
						skill[skill_sel_y][skill_sel_x].slv_++;
					}
					break;
				}
				skill_enter_wait = true;
				skill_enter = false;
				break;
			case 1:
				skill_enter_wait = true;
				skill_enter = false;
				break;
			}
		}
		//戻る
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			skill_enter = false;
			wait_esc = true;
		}
	}
	if (!skill_enter && !skill_husoku && !skill_max && menu_enter == true) {
		//キー入力で遷移
		if (skill_sel_x > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT))
			skill_sel_x--;
		if (skill_sel_x < 2 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT))
			skill_sel_x++;
		if (skill_sel_y > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
			skill_sel_y--;
		if (skill_sel_y < 2 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))
			skill_sel_y++;

		//メッセージウィンドウ
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawFormatStringToHandle(MENU_MES_X2, MENU_MES_Y2, BROWN, font32, "%s", skill[skill_sel_y][skill_sel_x].message_.c_str());

		//スキルレベルアップ処理
		if (!skill_enter_wait && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			skill_enter_sel = 1;
			skill_enter = true;
		}
	}
	skill_enter_wait = false;
}

//枠座標
const int MENU_EQU1_X = 150;
const int MENU_EQU1_Y = 220;
const int MENU_EQU2_X = 600;
const int MENU_EQU2_Y = 365;
//項目座標
const int EQU_TYPE_X = MENU_EQU1_X - 30;
const int EQU_TYPE_Y[4] = { 160,190,220,250 };
//項目座標2
const int EQU_NAME_X = 400;
const int EQU_NAME_Y[10] = { 160,220,280,340,400,460,520,580,640,700 };
//色
int equ_col[10] = { 0 };

//選択状態
bool equ_enter = false;
int equ_sel1 = 0;
int equ_sel2 = 0;

void menuSoubi() {
	//色初期化
	for (int i = 0; i < 10; i++) {
		equ_col[i] = BROWN;
	}

	//枠表示
	DrawRotaGraph(MENU_EQU1_X, MENU_EQU1_Y, 1, 0, img_menu_equ1, true);
	DrawRotaGraph(MENU_EQU2_X, MENU_EQU2_Y, 1, 0, img_menu_equ2, true);
	//種類表示
	DrawStringToHandle(EQU_TYPE_X, EQU_TYPE_Y[0], "直剣", BROWN, font32);
	DrawStringToHandle(EQU_TYPE_X, EQU_TYPE_Y[1], "双剣", BROWN, font32);
	DrawStringToHandle(EQU_TYPE_X, EQU_TYPE_Y[2], "杖", BROWN, font32);
	DrawStringToHandle(EQU_TYPE_X, EQU_TYPE_Y[3], "防具", BROWN, font32);

	if (equ_enter == true) {
		//キー入力で状態遷移
		if (equ_sel2 > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
			equ_sel2--;
		if (equ_sel2 < eq_num[equ_sel1] - 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))
			equ_sel2++;

		//選択中の色変更
		equ_col[equ_sel2] = -1;
		//カーソル
		DrawRotaGraph(EQU_NAME_X + 200, EQU_NAME_Y[equ_sel2] + 17, 1, 0, img_equ_cur, true);
		DrawRotaGraph(EQU_NAME_X - 60, EQU_NAME_Y[equ_sel2] + 16, 1, 0, img_equ_sel, true);
		//メッセージウィンドウ
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		//装備説明文
		DrawFormatStringToHandle(MENU_MES_X2, MENU_MES_Y2, BROWN, font32, "%s", eq_have[equ_sel1][equ_sel2].message_.c_str());
		//装備装着処理
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
			eq_now[equ_sel1] = eq_have[equ_sel1][equ_sel2];
		//戻る
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			equ_enter = false;
			wait_esc = true;
		}
	}
	if (menu_enter == true && !equ_enter) {
		//キー入力で遷移
		if (equ_sel1 > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
			equ_sel1--;
		if (equ_sel1 < 3 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))
			equ_sel1++;
		//カーソル
		DrawRotaGraph(EQU_TYPE_X - 40, EQU_TYPE_Y[equ_sel1] + 16, 1, 0, img_equ_sel, true);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			equ_enter = true;
			equ_sel2 = 0;
		}
	}

	//装備名表示
	for (int i = 0; i < eq_num[equ_sel1]; i++) {
		DrawFormatStringToHandle(EQU_NAME_X, EQU_NAME_Y[i], equ_col[i], font32, "%s", eq_have[equ_sel1][i].name_.c_str());
		DrawRotaGraph(EQU_NAME_X - 21, EQU_NAME_Y[i] + 18, 1.5F, 0, img_icon_eq[equ_sel1], true);
		if (eq_now[equ_sel1].name_ == eq_have[equ_sel1][i].name_)
			DrawStringToHandle(EQU_NAME_X + 400, EQU_NAME_Y[i], "装備中", YELLOW, font32);
	}

}

//枠座標
const int MENU_DOUGU1_X = 150;
const int MENU_DOUGU1_Y = 220;
const int MENU_DOUGU2_X = 600;
const int MENU_DOUGU2_Y = 365;
const int DOUGU_TYPE_X = MENU_DOUGU1_X - 40;
const int DOUGU_TYPE_Y[2] = { 180,230 };
//項目座標2
const int DOUGU_NAME_X = 400;
const int DOUGU_NAME_Y[10] = { 160,220,280,340,400,460,520,580,640,700 };

//色
int dou_col[10] = {0};

//回復量
int heal = 0;

//選択状態
int dou_sel1 = 0;
int dou_sel2 = 0;
int dou_tukau_sel = 0;

bool dou_enter = false;
bool dou_tukau = false;
bool dou_yes = false;
bool dou_no = false;

bool init_dougu = true;
bool dontmax = false;

void menuDougu() {
	//色初期化
	for (int i = 0; i < 10; i++) {
		dou_col[i] = BROWN;
	}

	//枠表示
	DrawRotaGraph(MENU_DOUGU1_X, MENU_DOUGU1_Y, 1, 0, img_menu_equ1, true);
	DrawRotaGraph(MENU_DOUGU2_X, MENU_DOUGU2_Y, 1, 0, img_menu_equ2, true);
	DrawStringToHandle(DOUGU_TYPE_X, DOUGU_TYPE_Y[0], "使うもの", BROWN, font32);
	DrawStringToHandle(DOUGU_TYPE_X, DOUGU_TYPE_Y[1], "大事な物", BROWN, font32);

	if (dou_enter == true || dou_tukau == true) {
		//選択中の色変更
		dou_col[dou_sel2] = -1;
		//カーソル
		DrawRotaGraph(DOUGU_NAME_X + 200, DOUGU_NAME_Y[dou_sel2] + 17, 1, 0, img_equ_cur, true);
		DrawRotaGraph(DOUGU_NAME_X - 60, DOUGU_NAME_Y[dou_sel2] + 16, 1, 0, img_equ_sel, true);
		//メッセージウィンドウ
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		//アイテム説明文
		DrawFormatStringToHandle(MENU_MES_X2, MENU_MES_Y2, BROWN, font32, "%s", item_have[dou_sel1][dou_sel2].message_.c_str());
	}

	//使う処理
	if (dou_yes == true) {
		wait_esc = true;
		wait_enter = true;
		if (player.hp_ == player.mhp_ && !dontmax) {
			//メッセージウィンドウ
			DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
			DrawFormatStringToHandle(MENU_MES_X2, MENU_MES_Y2, BROWN, font32, "HPが 満タンです。");
			init_dougu = true;
		}
		else {
			if (!init_dougu) {
				//回復量
				heal = item_have[dou_sel1][dou_sel2].heal_;
				if (player.hp_ + heal > player.mhp_) {
					heal = player.mhp_ - player.hp_;
				}
				//回復
				player.hp_ = player.hp_ + heal;
				//個数を減らす処理
				item_have[dou_sel1][dou_sel2].num_--;
				//個数が0になった時の処理
				if (item_have[dou_sel1][dou_sel2].num_ == 0) {
					if (dou_sel2 != item_num[dou_sel1] - 1) {
						//アイテム繰り上げ処理
						for (int i = dou_sel2; i < (item_num[dou_sel1] - 1); i++) {
							item_have[dou_sel1][i] = item_have[dou_sel1][i + 1];
						}
					}
					item_num[dou_sel1] --;
				}
				dontmax = true;
				init_dougu = true;
			}
			//メッセージウィンドウ
			DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
			DrawFormatStringToHandle(MENU_MES_X2, MENU_MES_Y2, BROWN, font32, "HPが %d 回復した。", heal);
		}
		//終了処理
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			if (item_num[dou_sel1] > 0)
				dou_enter = true;
			dou_yes = false;
			dontmax = false;
		}
	}

	//捨てる処理
	if (dou_no == true) {
		wait_esc = true;
		wait_enter = true;
		//個数を減らす処理
		if (!init_dougu) {
			item_have[dou_sel1][dou_sel2].num_--;
			//個数が0になった時の処理
			if (item_have[dou_sel1][dou_sel2].num_ == 0) {
				if (dou_sel2 != item_num[dou_sel1] - 1) {
					//アイテム繰り上げ処理
					for (int i = dou_sel2; i < (item_num[dou_sel1] - 1); i++) {
						item_have[dou_sel1][i] = item_have[dou_sel1][i + 1];
					}
				}
				item_num[dou_sel1] --;
			}
			init_dougu = true;
		}
		//メッセージウィンドウ
		DrawRotaGraph(MENU_MES_X1, MENU_MES_Y1, 0.8F, 0, img_menu_mes, true);
		DrawFormatStringToHandle(MENU_MES_X2, MENU_MES_Y2, BROWN, font32, "%sを　捨てた。", item_have[dou_sel1][dou_sel2].name_.c_str());
		//終了処理
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			if(item_num[dou_sel1] > 0)
				dou_enter = true;
			dou_no = false;
		}
	}

	if (dou_tukau == true) {
		//キー入力で遷移
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT))
			dou_tukau_sel = 0;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT))
			dou_tukau_sel = 1;

		//選択し表示
		DrawRotaGraph(TUYOSA_YES_X[0], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[0], true);
		DrawRotaGraph(TUYOSA_YES_X[1], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[0], true);
		DrawRotaGraph(TUYOSA_YES_X[dou_tukau_sel], TUYOSA_YES_Y, 1.2F, 0, img_menu_cur[1], true);

		DrawStringToHandle(TUYOSA_YES_X[0] - 45, TUYOSA_YES_Y - 18, "つかう", -1, font32);
		DrawStringToHandle(TUYOSA_YES_X[1] - 45, TUYOSA_YES_Y - 18, "すてる", -1, font32);

		//使うor捨てる
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			switch (dou_tukau_sel) {
			case 0:
				dou_yes = true;
				init_dougu = false;
				break;
			case 1:
				dou_no = true;
				init_dougu = false;
				break;
			}
			dou_tukau = false;
		}

		//戻る
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			dou_tukau = false;
			dou_enter = true;
			wait_esc = true;
		}
	}

	if (dou_enter == true) {
		//キー入力で状態遷移
		if (dou_sel2 > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
			dou_sel2--;
		if (dou_sel2 < item_num[dou_sel1] - 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))
			dou_sel2++;
		if (dou_sel2 > item_num[dou_sel1] - 1)
			dou_sel2 = item_num[dou_sel1] - 1;

		//アイテム使用処理
		if (dou_sel1 == 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !wait_enter) {
			dou_tukau_sel = 0;
			dou_tukau = true;
			dou_enter = false;
		}
		//戻る
		if (!wait_esc && tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			dou_enter = false;
			wait_esc = true;
		}
	}

	if (menu_enter == true && !dou_enter && !dou_tukau && !dou_yes && !dou_no) {
		//キー入力で遷移
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
			dou_sel1 = 0;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))
			dou_sel1 = 1;
		//カーソル
		DrawRotaGraph(DOUGU_TYPE_X - 30, DOUGU_TYPE_Y[dou_sel1] + 16, 1, 0, img_equ_sel, true);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && item_num[dou_sel1] > 0) {
			dou_enter = true;
			dou_sel2 = 0;
		}
	}

	//アイテム名表示
	for (int i = 0; i < item_num[dou_sel1]; i++) {
		DrawFormatStringToHandle(DOUGU_NAME_X, DOUGU_NAME_Y[i], dou_col[i], font32, "%s", item_have[dou_sel1][i].name_.c_str());
		DrawFormatStringToHandle(DOUGU_NAME_X + 400, DOUGU_NAME_Y[i], dou_col[i], font32, "%d 個", item_have[dou_sel1][i].num_);
		DrawRotaGraph(DOUGU_NAME_X - 21, DOUGU_NAME_Y[i] + 18, 1.5F, 0, img_icon_item_type[item_have[dou_sel1][i].type_], true);
	}

}

void titleOption();
extern bool option;
extern int sel_option;

extern int img_play_stage[3];
int sonota_sel = 0;
//選択し座標
const int SONOTA_X1 = 300;
const int SONOTA_X2 = 700;
const int SONOTA_Y1[3] = { 300,420,540 };
const int SONOTA_Y2[3] = { 350,470,590 };
int sonota_col[3] = { -1,-1,-1 };
int back_scene = 0;

//操作説明表示
bool sonota_enter = false;
bool sonota_option = false;
bool sonota_enter_wait = false;
extern int img_sousa;

void menuSonota() {
	//色の初期化
	sonota_col[0] = -1;
	sonota_col[1] = -1;
	sonota_col[2] = -1;
	//選択し表示
	DrawExtendGraph(SONOTA_X1, SONOTA_Y1[0], SONOTA_X2, SONOTA_Y2[0], img_play_stage[1], true);
	DrawExtendGraph(SONOTA_X1, SONOTA_Y1[1], SONOTA_X2, SONOTA_Y2[1], img_play_stage[1], true);
	DrawExtendGraph(SONOTA_X1, SONOTA_Y1[2], SONOTA_X2, SONOTA_Y2[2], img_play_stage[1], true);
	//選択中の枠
	if (menu_enter == true) {
		DrawExtendGraph(SONOTA_X1, SONOTA_Y1[sonota_sel], SONOTA_X2, SONOTA_Y2[sonota_sel], img_play_stage[2], true);
		sonota_col[sonota_sel] = BROWN;
	}
	//文字表示
	DrawStringToHandle(SONOTA_X1 + 120, SONOTA_Y1[0] + 12, "オプション", sonota_col[0], font32);
	DrawStringToHandle(SONOTA_X1 + 120, SONOTA_Y1[1] + 12, "そうさ方法", sonota_col[1], font32);
	switch (now_scene) {
	case SCENE_PLAY:
		DrawStringToHandle(SONOTA_X1 + 95, SONOTA_Y1[2] + 12, "タイトルに戻る", sonota_col[2], font32);
		back_scene = SCENE_TITLE;
		break;
	case SCENE_BATTLE:
		DrawStringToHandle(SONOTA_X1 + 60, SONOTA_Y1[2] + 12, "ステージ選択に戻る", sonota_col[2], font32);
		back_scene = SCENE_PLAY;
		break;
	}

	if (sonota_option == true) {
		titleOption();
		wait_esc = true;
		sonota_enter_wait = true;
	}

	if (sonota_enter == true) {
		DrawRotaGraph(512, 370, 1, 0, img_sousa, true);
		DrawStringToHandle(420, 70, "そうさ方法", BROWN, font32);
		DrawStringToHandle(220, 165, "：移動", BROWN, font32);
		DrawStringToHandle(220, 240, "：ジャンプ", BROWN, font32);
		DrawStringToHandle(220, 310, "：ダッシュ", BROWN, font32);
		DrawStringToHandle(220, 397, "：属性の切り替え", BROWN, font32);
		DrawStringToHandle(220, 467, "：攻撃スキル", BROWN, font32);
		DrawStringToHandle(220, 535, "：メニュー / キャンセル", BROWN, font32);
		DrawStringToHandle(220, 605, "：決定", BROWN, font32);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			sonota_enter_wait = true;
			sonota_enter = false;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			wait_esc = true;
			sonota_enter = false;
		}
	}
	if (!menu_enter)
		sonota_sel = 0;

	if (menu_enter == true && !sonota_enter && !sonota_option) {
		//キー入力で遷移
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) && sonota_sel > 0)
			sonota_sel -= 1;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) && sonota_sel < 2)
			sonota_sel += 1;

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !sonota_enter_wait) {
			switch (sonota_sel) {
			case 0:
				sel_option = 2;
				sonota_option = true;
				break;
			case 1:
				sonota_enter = true;
				break;
			case 2:
				menu_sel = 0;
				StopSoundMem(sound_battle);
				StopSoundMem(sound_battle_magician);
				StopSoundMem(sound_battle_fairy);
				StopSoundMem(sound_battle_doragon);
				StopSoundMem(sound_play);
				if (back_scene == SCENE_PLAY) {
					PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				}
				if (back_scene == SCENE_TITLE) {
					PlaySoundMem(sound_title, DX_PLAYTYPE_LOOP, 1);
				}
				scene = back_scene;
				break;
			}
		}

	}
	sonota_enter_wait = false;
}