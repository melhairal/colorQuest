#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

bool init_ui = false;
//hpバーの画像
int img_hp_base = 0;
int img_hp_frame = 0;
int img_hp_gauge = 0;
int img_hp_icon = 0;
//hpバーの座標
const int HP_X = 200;
const int HP_Y = 730;
//hpゲージの幅
const int HP_W = 312;
const int HP_H = 16;
//hpゲージの座標
const int GAUGE_X1 = HP_X - HP_W / 2;
const int GAUGE_Y1 = HP_Y - HP_H / 2;
const int GAUGE_Y2 = HP_Y + HP_H / 2;
int gauge_x2 = 0;
//HP数値の座標
const int HP_NUM_X1 = HP_X + 10;
const int HP_NUM_X2 = HP_X - 40;
const int HP_NUM_Y = HP_Y - 50;

//属性表示
const int COL_X = 512;
const int COL_Y = 700;
int left_col = 0;
const int LR_COL_Y = COL_Y + 20;
const int L_COL_X = COL_X - 60;
int right_col = 0;
const int R_COL_X = COL_X + 60;
//属性キー文字座標
const int LR_KEY_Y = LR_COL_Y - 60;
const int L_KEY_X = L_COL_X - 12;
const int R_KEY_X = R_COL_X - 12;

//スキルボタン表示
const int SKILL_Y = 720;
const int SKILL1_X = 750;
const int SKILL2_X = 850;
const int SKILL3_X = 950;
extern int skill_key[3];
const int SPRINT_X = 660;
const int SPRINT_Y = 730;
//スキルキー文字座標
const int SK_KEY_Y = SKILL_Y - 70;
const int SK1_KEY_X = SKILL1_X - 12;
const int SK2_KEY_X = SKILL2_X - 12;
const int SK3_KEY_X = SKILL3_X - 12;
const int SP_KEY_X = SPRINT_X - 20;
const int SP_KEY_Y = SPRINT_Y - 45;

//スプリントクールタイム表示
const int SP_CD_X = SPRINT_X - 10;
const int SP_CD_Y = SPRINT_Y - 17;

//スキルクールタイム表示
extern int mode_rock;
extern float cd_count[3][3];
const int SK_CD_Y = SKILL_Y - 18;
const int SK1_CD_X = SKILL1_X - 10;
const int SK2_CD_X = SKILL2_X - 10;
const int SK3_CD_X = SKILL3_X - 10;

//敵HPゲージの幅
const int ENEMY_HP_W = 78;
const int ENEMY_HP_H = 4;
//敵HPpゲージの座標
int enemy_hp_x1[3];
int enemy_hp_y1[3];
int enemy_hp_y2[3];
int enemy_hp_x2[3];

//ステージ表示
int stage_title_timer = 60;
//経験値表示
int exp_timer = 0;
extern int clear_exp[7];
extern int img_icon_star;

extern bool damage_cri[3];

void battleUi() {

	if (!init_ui) {
		//画像ファイル読み込み
		img_hp_base = LoadGraph("graphics/hp/gauge_background.png");
		img_hp_frame = LoadGraph("graphics/hp/gauge_frame.png");
		img_hp_gauge = LoadGraph("graphics/hp/gauge_bar_pink.png");
		img_hp_icon = LoadGraph("graphics/icon/sticon3b-3.png");
		img_icon_star = LoadGraph("graphics/icon/sticon4e-3.png");

		init_ui = true;
	}

	//HPゲージの横幅計算
	gauge_x2 = GAUGE_X1 + HP_W * ( (double) player.hp_ / (double) player.mhp_ );

	//HPバー表示
	DrawRotaGraph(HP_X, HP_Y, 2, 0, img_hp_base, true);
	DrawExtendGraph(GAUGE_X1, GAUGE_Y1, gauge_x2, GAUGE_Y2, img_hp_gauge, true);
	DrawRotaGraph(HP_X, HP_Y, 2, 0, img_hp_frame, true);
	DrawRotaGraph(HP_X - 60, HP_Y - 33, 1.5F, 0, img_hp_icon, true);

	//HP数値表示
	DrawFormatStringToHandle(HP_NUM_X1, HP_NUM_Y, BROWN, font32, "%d", player.hp_);
	DrawFormatStringToHandle(HP_NUM_X2, HP_NUM_Y, BROWN, font32, "HP        / %d", player.mhp_);
	
	//属性表示
	left_col = player.mode_ - 1;
	if (left_col == -1)
		left_col = 2;
	right_col = (player.mode_ + 1) % 3;

	DrawRotaGraph(COL_X, COL_Y, 0.2, 0, color[player.mode_], true);
	DrawRotaGraph(L_COL_X, LR_COL_Y, 0.1, 0, color[left_col], true);
	DrawRotaGraph(R_COL_X, LR_COL_Y, 0.1, 0, color[right_col], true);

	//属性ボタン表示
	DrawStringToHandle(L_KEY_X, LR_KEY_Y, "A", BROWN, font32);
	DrawStringToHandle(R_KEY_X, LR_KEY_Y, "D", BROWN, font32);

	//スキル表示
	DrawRotaGraph(SKILL1_X, SKILL_Y, 0.15, 0, skill[player.mode_][SK_Z].img_[skill_key[SK_Z]], true);
	DrawRotaGraph(SKILL2_X, SKILL_Y, 0.15, 0, skill[player.mode_][SK_X].img_[skill_key[SK_X]], true);
	DrawRotaGraph(SKILL3_X, SKILL_Y, 0.15, 0, skill[player.mode_][SK_C].img_[skill_key[SK_C]], true);
	DrawRotaGraph(SPRINT_X, SPRINT_Y, 0.10, 0, img_sprint, true);

	//スキルボタン表示
	DrawStringToHandle(SK1_KEY_X, SK_KEY_Y, "Z", BROWN, font32);
	DrawStringToHandle(SK2_KEY_X, SK_KEY_Y, "X", BROWN, font32);
	DrawStringToHandle(SK3_KEY_X, SK_KEY_Y, "C", BROWN, font32);
	DrawStringToHandle(SP_KEY_X, SP_KEY_Y, "Shift", BROWN, font16);

	//クールタイム表示
	if (mode_rock != 0)
		DrawFormatStringToHandle(COL_X - 10, COL_Y - 17, 0, font32, "%d", mode_rock / 60);
	if (sprint_cd != 0)
		DrawFormatStringToHandle(SP_CD_X, SP_CD_Y, 0, font32, "%d", sprint_cd / 60);
	//if (cd_count[player.mode_][SK_Z] != 0)
	//	DrawFormatStringToHandle(SK1_CD_X, SK_CD_Y, 0, font32, "%d", (int)(cd_count[player.mode_][SK_Z] / 60));
	if (cd_count[player.mode_][SK_X] != 0)
		DrawFormatStringToHandle(SK2_CD_X, SK_CD_Y, 0, font32, "%d", (int)(cd_count[player.mode_][SK_X] / 60));
	if (cd_count[player.mode_][SK_C] != 0)
		DrawFormatStringToHandle(SK3_CD_X, SK_CD_Y, 0, font32, "%d", (int)(cd_count[player.mode_][SK_C] / 60));


	//敵ダメージ表記
	for (int i = 0; i < enemy_num[stage - 1]; i++) {
		if (enemy_damage_count[i] != 0) {
			enemy_damage_count[i]--;
			if (!damage_cri[i]) {
				DrawFormatStringToHandle(battle_enemy[i].pos_x_ - 15, battle_enemy[i].pos_y_ - (battle_enemy[i].r_ * 3), C_RED, font32, "%d", enemy_damage[i]);
			}
			else {
				DrawFormatStringToHandle(battle_enemy[i].pos_x_ - 15, battle_enemy[i].pos_y_ - (battle_enemy[i].r_ * 3), C_RED, font32, "%d!!", enemy_damage[i]);
			}

			//HPゲージ座標計算
			enemy_hp_x1[i] = battle_enemy[i].pos_x_ - ENEMY_HP_W / 2;
			enemy_hp_y1[i] = battle_enemy[i].pos_y_ - battle_enemy[i].r_ - ENEMY_HP_H / 2;
			enemy_hp_y2[i] = battle_enemy[i].pos_y_ - battle_enemy[i].r_ + ENEMY_HP_H / 2;
			enemy_hp_x2[i] = enemy_hp_x1[i] + ENEMY_HP_W * ((double)battle_enemy[i].hp_ / (double)battle_enemy[i].mhp_);
			if (enemy_hp_x2[i] < enemy_hp_x1[i]) {
				enemy_hp_x2[i] = enemy_hp_x1[i];
			}
			//HPバー表示
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_ - battle_enemy[i].r_, 0.5f, 0, img_hp_base, true);
			DrawExtendGraph(enemy_hp_x1[i], enemy_hp_y1[i], enemy_hp_x2[i], enemy_hp_y2[i], img_hp_gauge, true);
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_ - battle_enemy[i].r_, 0.5f, 0, img_hp_frame, true);
		}
		if (enemy_damage_count[i] == 0) {
			damage_cri[i] = false;
		}
	}
	if (stage_title_timer != 0) {
		stage_title_timer--;
		DrawFormatStringToHandle(450, 300, -1, font32, "Stage %d", stage);
	}
	if (exp_timer != 0) {
		exp_timer--;
		DrawFormatStringToHandle(player.pos_x_ - 30, player.pos_y_ - 100, 0, font16, "EXP + %d", clear_exp[stage - 1]);
		DrawRotaGraph(player.pos_x_ - 50, player.pos_y_ - 90, 1.5F, 0, img_icon_star, true);
	}
}

