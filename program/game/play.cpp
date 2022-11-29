#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

bool init_play = false;
void getStatus();
void getEquipStatus();
void getItemStatus();
void getSkillani();
void enemyImg();
void getItem(int TYPE, int ID);
extern bool menu_enter;

//初回起動時のみ操作方法表示
bool sousa_houhou = false;
int img_sousa = 0;

extern bool gameover;
extern bool battle_reset;
extern bool init_stage[7];
extern int stage_title_timer;
extern int clear_num;

int img_play_bg;
const int PLAY_BG_X = 500;
const int PLAY_BG_Y = 500;
int img_play_stage[3];
const int PLAY_STAGE_X = 350;
const int PLAY_STAGE_Y[8] = { 130,210,290,370,450,530,600,670 };
int stage_sel = 0;

const int STAGE_ENEMY1_X = 800;
const int STAGE_ENEMY1_Y = 650;
const int STAGE_ENEMY2_X = 900;
const int STAGE_ENEMY2_Y = 650;
const int STAGE_ENEMY3_X = 850;
const int STAGE_ENEMY3_Y = 600;

int shop_sel = 0;

void scenePlay() {

	if (!init_play) {
		getStatus();
		getEquipStatus();
		getItemStatus();
		getSkillani();
		enemyImg();

		srand(time(0));

		img_play_bg = LoadGraph("graphics/bg/menu_window_01.png");
		img_play_stage[0] = LoadGraph("graphics/bg/button_select_02.png");
		img_play_stage[1] = LoadGraph("graphics/bg/button_select_02_active.png");
		img_play_stage[2] = LoadGraph("graphics/bg/button_select_02_hover.png");
		img_sousa = LoadGraph("graphics/bg/sousa.png");

		for (int i = 0; i < 11; i++) {
			enemy[i].initialize(i);
		}
		init_play = true;
	}

	player.mhp_ = player.default_hp_ + eq_now[RED].hp_ + eq_now[BLUE].hp_ + eq_now[GREEN].hp_ + eq_now[ARM].hp_;
	player.hp_ = player.mhp_;

	//画面表示
	DrawRotaGraph(PLAY_BG_X, PLAY_BG_Y, 2, 0, img_play_bg, true);
	DrawStringToHandle(370, 50, "ステージセレクト", BROWN, font32);
	for (int i = 0; i < 7; i++) {
		DrawRotaGraph(PLAY_STAGE_X, PLAY_STAGE_Y[i], 1, 0, img_play_stage[0], true);
	}
	for (int i = 0; i < clear_num; i++) {
		DrawRotaGraph(PLAY_STAGE_X, PLAY_STAGE_Y[i], 1, 0, img_play_stage[1], true);
		DrawFormatStringToHandle(PLAY_STAGE_X - 70, PLAY_STAGE_Y[i] - 20, -1, font32, "Stage %d", i + 1);
	}
	DrawRotaGraph(PLAY_STAGE_X, PLAY_STAGE_Y[7], 1, 0, img_play_stage[1], true);
	DrawStringToHandle(PLAY_STAGE_X - 50, PLAY_STAGE_Y[7] - 18, "SHOP", -1, font32);
	//選択中
	DrawRotaGraph(PLAY_STAGE_X, PLAY_STAGE_Y[stage_sel], 1, 0, img_play_stage[2], true);
	if (stage_sel < 7) {
		DrawFormatStringToHandle(PLAY_STAGE_X - 70, PLAY_STAGE_Y[stage_sel] - 20, BROWN, font32, "Stage %d", stage_sel + 1);
	}
	else if (stage_sel == 7) {
		DrawStringToHandle(PLAY_STAGE_X - 50, PLAY_STAGE_Y[7] - 18, "SHOP", BROWN, font32);
	}
	switch (stage_sel) {
	case 0:
		DrawRotaGraph(STAGE_ENEMY1_X, STAGE_ENEMY1_Y, 1.5F, 0, enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY2_X, STAGE_ENEMY2_Y, 1.5F, 0, enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY3_X, STAGE_ENEMY3_Y, 1.5F, 0, enemy[Enemy::REDSLIME].img_[ENEMY_STOP][0], true);
		break;
	case 1:
		DrawRotaGraph(STAGE_ENEMY1_X, STAGE_ENEMY1_Y, 1.5F, 0, enemy[Enemy::REDSLIME].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY2_X, STAGE_ENEMY2_Y, 1.5F, 0, enemy[Enemy::REDSLIME].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY3_X, STAGE_ENEMY3_Y, 1.5F, 0, enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][0], true);
		break;
	case 2:
		DrawRotaGraph(STAGE_ENEMY1_X, STAGE_ENEMY1_Y, 1.5F, 0, enemy[Enemy::REDBIRD].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY2_X, STAGE_ENEMY2_Y, 1.5F, 0, enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY3_X, STAGE_ENEMY3_Y, 1.5F, 0, enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][0], true);
		break;
	case 3:
		DrawRotaGraph(STAGE_ENEMY1_X, STAGE_ENEMY1_Y, 1.5F, 0, enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY2_X, STAGE_ENEMY2_Y, 1.5F, 0, enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY3_X, STAGE_ENEMY3_Y, 1.5F, 0, enemy[Enemy::REDBIRD].img_[ENEMY_STOP][0], true);
		break;
	case 4:
		DrawRotaGraph(STAGE_ENEMY1_X, STAGE_ENEMY1_Y, 1.5F, 0, enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY2_X, STAGE_ENEMY2_Y, 1.5F, 0, enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY3_X, STAGE_ENEMY3_Y, 1.5F, 0, enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][0], true);
		break;
	case 5:
		DrawRotaGraph(STAGE_ENEMY1_X, STAGE_ENEMY1_Y, 1.5F, 0, enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][0], true);
		DrawRotaGraph(STAGE_ENEMY2_X, STAGE_ENEMY2_Y, 1.5F, 0, enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][0], true);
		break;
	case 6:
		DrawRotaGraph(STAGE_ENEMY2_X, STAGE_ENEMY2_Y, 1.5F, 0, enemy[Enemy::DRAGON].img_[ENEMY_STOP][0], true);
		break;
	case 7:
		break;

	}

	if (sousa_houhou == true) {
		//キー入力で遷移
		if (stage_sel > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) && stage_sel != 7) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			stage_sel--;
		}
		if (stage_sel < clear_num && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			stage_sel++;
		}
		if (stage_sel == clear_num)
			stage_sel = 7;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) && stage_sel == 7) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			stage_sel = clear_num - 1;
		}

		//HPは常に最大
		player.hp_ = player.mhp_;
		//メニュー
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			PlaySoundMem(se_menu, DX_PLAYTYPE_BACK);
			menu_enter = false;
			now_scene = SCENE_PLAY;
			scene = SCENE_MENU;
		}
		//ステージに入る・いろいろ初期化
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			StopSoundMem(sound_play);
			if (stage_sel != 7) {
				stage = stage_sel + 1;
				play_mode = STAGE_PLAY;
				battle_reset = false;
				init_stage[stage_sel] = false;
				stage_title_timer = 60;
				scene = SCENE_BATTLE;
			}
			if (stage_sel == 7) {
				shop_sel = 0;
				PlaySoundMem(sound_shop, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_SHOP;
			}
		}
	}

	if (!sousa_houhou) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN))
			sousa_houhou = true;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE))
			sousa_houhou = true;
		DrawRotaGraph(512, 370, 1, 0, img_sousa, true);
		DrawStringToHandle(420, 70, "そうさ方法", BROWN, font32);
		DrawStringToHandle(220, 165, "：移動", BROWN, font32);
		DrawStringToHandle(220, 240, "：ジャンプ", BROWN, font32);
		DrawStringToHandle(220, 310, "：ダッシュ", BROWN, font32);
		DrawStringToHandle(220, 397, "：属性の切り替え", BROWN, font32);
		DrawStringToHandle(220, 467, "：攻撃スキル", BROWN, font32);
		DrawStringToHandle(220, 535, "：メニュー / キャンセル", BROWN, font32);
		DrawStringToHandle(220, 605, "：決定", BROWN, font32);

	}
}

//ショップ画面
bool init_shop = false;
int img_shop_bg = 0;
int img_shop_frame1 = 0;
int img_shop_frame2 = 0;
int img_shop_exp = 0;
int img_shop_star = 0;
int img_shop_sel = 0;
int img_shop_cur = 0;
int img_shop_mes = 0;
int img_shop_yes[2] = { 0,0 };
//枠座標
const int SHOP_FRAME1_X = 150;
const int SHOP_FRAME1_Y = 220;
const int SHOP_FRAME2_X = 600;
const int SHOP_FRAME2_Y = 365;
const int SHOP_EXP_X = 800;
const int SHOP_EXP_Y = 80;
const int SHOP_STAR_X = 720;
const int SHOP_STAR_Y = 80;
const int SHOP_YES_X[2] = { 720,890 };
const int SHOP_YES_Y = 620;
//アイテム名座標
const int SHOP_NAME_X = 400;
const int SHOP_NAME_Y[10] = { 160,220,280,340,400,460,520,580,640,700 };
int shop_col[10];
int img_shop_icon_type[2];
//文字座標
const int SHOP_TYPE_X = SHOP_FRAME1_X - 50;
const int SHOP_TYPE_Y[3] = {160,205,250};
//選択状況
bool shop_buy = false;
bool shop_sold = false;

bool shop_buy_enter = false;
bool shop_sold_enter = false;
bool buy_error = false;

int buy_sel = 0;
int shop_buy_yes = 0;

bool shop_enter_wait = false;
bool shop_esc_wait = false;

void sceneShop() {
	if (!init_shop) {
		img_shop_bg = LoadGraph("graphics/bg/shop.jpg");
		img_shop_frame1 = LoadGraph("graphics/bg/equip_window_01.png");
		img_shop_frame2 = LoadGraph("graphics/bg/equip_window_02.png");
		img_shop_exp = LoadGraph("graphics/bg/caption_01.png");
		img_shop_star = LoadGraph("graphics/icon/sticon4e-3.png");
		img_shop_sel = LoadGraph("graphics/bg/toggle_tab_active.png");
		img_shop_cur = LoadGraph("graphics/bg/equip_cursol.png");
		img_shop_mes = LoadGraph("graphics/bg/message_frame_02_light.png");
		img_shop_yes[0] = LoadGraph("graphics/bg/button_round.png");
		img_shop_yes[1] = LoadGraph("graphics/bg/button_round_active.png");

		img_shop_icon_type[GRASS] = LoadGraph("graphics/icon/icon029.png");
		img_shop_icon_type[PORTION] = LoadGraph("graphics/icon/icon030.png");

		init_shop = true;
	}
	//色初期化
	for (int i = 0; i < 10; i++) {
		shop_col[i] = BROWN;
	}
	//枠表示
	DrawRotaGraph(512, 350, 1.5F, 0, img_shop_bg, true);
	DrawRotaGraph(SHOP_FRAME1_X, SHOP_FRAME1_Y, 1, 0, img_shop_frame1,true);
	DrawRotaGraph(SHOP_FRAME2_X, SHOP_FRAME2_Y, 1, 0, img_shop_frame2, true);
	DrawRotaGraph(SHOP_EXP_X, SHOP_EXP_Y, 1, 0, img_shop_exp, true);
	DrawRotaGraph(SHOP_STAR_X, SHOP_STAR_Y, 1, 0, img_shop_star, true);
	DrawFormatStringToHandle(SHOP_EXP_X - 30, SHOP_EXP_Y - 16, -1, font32, "%d", player.exp_);
	DrawStringToHandle(SHOP_TYPE_X, SHOP_TYPE_Y[0], "買う", BROWN, font32);
	DrawStringToHandle(SHOP_TYPE_X, SHOP_TYPE_Y[1], "売る", BROWN, font32);
	DrawStringToHandle(SHOP_TYPE_X, SHOP_TYPE_Y[2], "出る", BROWN, font32);
	DrawRotaGraph(SHOP_TYPE_X - 20, SHOP_TYPE_Y[shop_sel] + 16, 1, 0, img_shop_sel, true);

	if (shop_buy == true || shop_sold == true || shop_buy_enter == true || shop_sold_enter == true || buy_error == true) {
		//選択中の色変更
		shop_col[buy_sel] = -1;
		//カーソル
		DrawRotaGraph(SHOP_NAME_X + 200, SHOP_NAME_Y[buy_sel] + 17, 1, 0, img_shop_cur, true);
		DrawRotaGraph(SHOP_NAME_X - 60, SHOP_NAME_Y[buy_sel] + 16, 1, 0, img_shop_sel, true);
		//メッセージウィンドウ
		DrawRotaGraph(512, 680, 0.8F, 0, img_shop_mes, true);
		//アイテム説明文
		if (shop_buy == true)
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s", item_date[ITEM][buy_sel].message_.c_str());
		if (shop_sold == true)
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s", item_have[ITEM][buy_sel].message_.c_str());
	}



	//購入
	if (shop_buy_enter == true) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			shop_buy_yes = 0;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			shop_buy_yes = 1;
		}

		//選択し表示
		DrawRotaGraph(SHOP_YES_X[0], SHOP_YES_Y, 1.2F, 0, img_shop_yes[0], true);
		DrawRotaGraph(SHOP_YES_X[1], SHOP_YES_Y, 1.2F, 0, img_shop_yes[0], true);
		DrawRotaGraph(SHOP_YES_X[shop_buy_yes], SHOP_YES_Y, 1.2F, 0, img_shop_yes[1], true);
		DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を購入しますか？", item_date[ITEM][buy_sel].name_.c_str());
		DrawStringToHandle(SHOP_YES_X[0] - 30, SHOP_YES_Y - 18, "はい", -1, font32);
		DrawStringToHandle(SHOP_YES_X[1] - 45, SHOP_YES_Y - 18, "いいえ", -1, font32);

		
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			shop_enter_wait = true;
			switch (shop_buy_yes) {
			case 0:
				if (player.exp_ >= item_date[ITEM][buy_sel].buy_) {
					player.exp_ -= item_date[ITEM][buy_sel].buy_;
					PlaySoundMem(se_buy, DX_PLAYTYPE_BACK);
					getItem(ITEM, buy_sel);
					shop_buy_enter = false;
					shop_buy = true;
				}
				else {
					PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
					buy_error = true;
					shop_buy_enter = false;
				}
				break;
			case 1:
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				shop_buy_enter = false;
				shop_buy = true;
				break;
			}
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			PlaySoundMem(se_esc, DX_PLAYTYPE_BACK);
			shop_buy_enter = false;
			shop_buy = true;
			shop_esc_wait = true;
		}
	}
	//所持金不足
	if (buy_error == true) {
		DrawStringToHandle(100, 660, "ポイントが足りません。", BROWN, font32);
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !shop_enter_wait) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			buy_error = false;
			shop_buy = true;
			shop_enter_wait = true;
		}
	}
	//選択
	if (shop_buy == true) {
		if (buy_sel > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			buy_sel -= 1;
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
		}
		if (buy_sel < 4 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			buy_sel += 1;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE) && !shop_esc_wait) {
			PlaySoundMem(se_esc, DX_PLAYTYPE_BACK);
			shop_buy = false;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !shop_enter_wait) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			shop_buy_enter = true;
			shop_buy = false;
			shop_buy_yes = 1;
		}
	}

	//売却
	if (shop_sold_enter == true) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			shop_buy_yes = 0;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			shop_buy_yes = 1;
		}

		//選択し表示
		DrawRotaGraph(SHOP_YES_X[0], SHOP_YES_Y, 1.2F, 0, img_shop_yes[0], true);
		DrawRotaGraph(SHOP_YES_X[1], SHOP_YES_Y, 1.2F, 0, img_shop_yes[0], true);
		DrawRotaGraph(SHOP_YES_X[shop_buy_yes], SHOP_YES_Y, 1.2F, 0, img_shop_yes[1], true);
		DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を売りますか？", item_have[ITEM][buy_sel].name_.c_str());
		DrawStringToHandle(SHOP_YES_X[0] - 30, SHOP_YES_Y - 18, "はい", -1, font32);
		DrawStringToHandle(SHOP_YES_X[1] - 45, SHOP_YES_Y - 18, "いいえ", -1, font32);


		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			shop_enter_wait = true;
			switch (shop_buy_yes) {
			case 0:
				PlaySoundMem(se_buy, DX_PLAYTYPE_BACK);
				//個数を減らす処理
				item_have[ITEM][buy_sel].num_--;
				//個数が0になった時の処理
				if (item_have[ITEM][buy_sel].num_ == 0) {
					if (buy_sel != item_num[ITEM] - 1) {
						//アイテム繰り上げ処理
						for (int i = buy_sel; i < (item_num[ITEM] - 1); i++) {
							item_have[ITEM][i] = item_have[ITEM][i + 1];
						}
					}
					item_num[ITEM] --;
				}
				//ポイント増やす処理
				player.exp_ += item_have[ITEM][buy_sel].sold_;
				shop_sold_enter = false;
				if (item_num[ITEM] != 0) {
					shop_sold = true;
				}
				break;
			case 1:
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				shop_sold_enter = false;
				shop_sold = true;
				break;
			}
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
			PlaySoundMem(se_esc, DX_PLAYTYPE_BACK);
			shop_sold_enter = false;
			shop_sold = true;
			shop_esc_wait = true;
		}
	}
	//選択
	if (shop_sold == true) {
		if (buy_sel > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			buy_sel -= 1;
		}
		if (buy_sel < item_num[ITEM] - 1 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			buy_sel += 1;
		}
		if (buy_sel > item_num[ITEM] - 1) {
			buy_sel = item_num[ITEM] - 1;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE) && !shop_esc_wait) {
			PlaySoundMem(se_esc, DX_PLAYTYPE_BACK);
			shop_sold = false;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !shop_enter_wait) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			shop_sold_enter = true;
			shop_sold = false;
			shop_buy_yes = 1;
		}

	}

	//キー入力で状態遷移
	if (!shop_buy && !shop_sold && !shop_buy_enter && !shop_sold_enter && !buy_error) {
		if (shop_sel > 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			shop_sel -= 1;
		}
		if (shop_sel < 2 && tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			PlaySoundMem(se_select, DX_PLAYTYPE_BACK);
			shop_sel += 1;
		}
		//エンターキー
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			switch (shop_sel) {
			case 0:
				buy_sel = 0;
				shop_buy = true;
				break;
			case 1:
				if (item_num[ITEM] > 0) {
					buy_sel = 0;
					shop_sold = true;
				}
				break;
			case 2:
				buy_sel = 0;
				StopSoundMem(sound_shop);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
				break;
			}
		}
	}

	//アイテム名表示
	switch (shop_sel) {
	case 0:
		for (int i = 0; i < 5; i++) {
			DrawFormatStringToHandle(SHOP_NAME_X, SHOP_NAME_Y[i], shop_col[i], font32, "%s", item_date[ITEM][i].name_.c_str());
			DrawFormatStringToHandle(SHOP_NAME_X + 400, SHOP_NAME_Y[i], shop_col[i], font32, "%dP", item_date[ITEM][i].buy_);
			DrawRotaGraph(SHOP_NAME_X - 21, SHOP_NAME_Y[i] + 18, 1.5F, 0, img_shop_icon_type[item_date[ITEM][i].type_], true);
		}
		break;
	case 1:
		for (int i = 0; i < item_num[ITEM]; i++) {
			DrawFormatStringToHandle(SHOP_NAME_X, SHOP_NAME_Y[i], shop_col[i], font32, "%s", item_have[ITEM][i].name_.c_str());
			DrawFormatStringToHandle(SHOP_NAME_X + 300, SHOP_NAME_Y[i], shop_col[i], font32, "%d 個", item_have[ITEM][i].num_);
			DrawFormatStringToHandle(SHOP_NAME_X + 400, SHOP_NAME_Y[i], shop_col[i], font32, "%dP", item_date[ITEM][i].sold_);
			DrawRotaGraph(SHOP_NAME_X - 21, SHOP_NAME_Y[i] + 18, 1.5F, 0, img_shop_icon_type[item_have[ITEM][i].type_], true);
		}
		break;
	}
	shop_enter_wait = false;
	shop_esc_wait = false;
}