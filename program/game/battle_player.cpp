#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

//プロトタイプ宣言
void playSkill();
void getEquipment(int TYPE, int ID);
void getItem(int TYPE, int ID);
void playerDamage(int damage, int enemy_color);
void playerDamagemotion();
void enemyDamage(int id, int MODE, int SKILL);

//ゲームクリアorゲームオーバーorプレイ
int play_mode = 0;

//初期座標
const int BATTLE_X = 400;
const int BATTLE_Y = 600;
bool battle_reset = false;

//移動速度
const int PLAYER_SPEED = 6;

//ジャンプ処理用の変数
float jump_s = 0;
int jump_power = 0;

//属性切り替えロック
int mode_rock = 0;

//スキルボタン
int skill_key[3] = { 0 };
int on_sk[3] = { 0 };

//スプリントアニメーション
bool st_sprint[2];
int sprint_x[2] = { 0 };
int sprint_y[2] = { 0 };

//スキル処理に入る
bool st_skill[3][3];

//スキルクールダウン
float cd_count[3][3] = { 0 };

//ダメージを受けたときの動作
//無敵時間
int damage_no = 0;
bool player_damage = false;
int damage_num = 0;
int damage_num_count = 0;

//ゲームオーバー時プレイヤーの回転
float player_rota = 0;

//スキル
const int COUNT = 8;
int sk_ani_frame = COUNT;

//スプリントアニメーション
int sprint_ani[2][10] = { 0 };
int sprint_frame[2] = { 0,9 };

//スキル処理
int skill_ani[3][3][2][50] = { 0 };
int skill_x[3][3] = { 0 };
int skill_y[3][3] = { 0 };
int skill_frame[3][3] = { 0 };
int skill_dir[3][3] = { 0,9 };

//敵がダメージを一回だけ受ける
bool enemy_damage_rock[3][3][3];

extern int exp_timer;

void battlePlayer() {

	//バトル開始時の初期設定
	if (!battle_reset) {
		player.pos_x_ = BATTLE_X;
		player.pos_y_ = BATTLE_Y;
		player.mhp_ = player.default_hp_ + eq_now[RED].hp_ + eq_now[BLUE].hp_ + eq_now[GREEN].hp_ + eq_now[ARM].hp_;
		player.hp_ = player.mhp_;
		player_rota = 0;
		player_damage = false;
		damage_num_count = 0;
		exp_timer = 0;
		player.battle_ani_ = 7;
		mode_rock = 0;
		damage_no = 0;

		//スキル処理初期設定
		for (int i = 0; i < 2; i++) {
			st_sprint[i] = true;
		}
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				st_skill[i][k] = true;
				cd_count[i][k] = 0;
				for (int n = 0; n < 3; n++) {
					enemy_damage_rock[n][i][k] = false;
				}
			}
		}

		battle_reset = true;
	}

	//プレイヤー表示
	if (damage_no == 0 || (damage_no >= 10 && damage_no < 20) || (damage_no >= 30 && damage_no < 40) || (damage_no >= 50))
		DrawRotaGraph(player.pos_x_, player.pos_y_, 2, 0, player.img_[player.mode_][player.battle_ani_], true);

	//ステータス計算
	for (int i = 0; i < 3; i++) {
		player.color_atk_[i] = player.atk_ * eq_now[i].atk_ * eq_now[ARM].atk_;
		player.color_cd_[i] = player.cd_ * eq_now[i].cd_ * eq_now[ARM].cd_;
		player.color_cri_[i] = player.cri_ + eq_now[i].cri_ + eq_now[ARM].cri_;
	}
	player.mhp_ = player.default_hp_ + eq_now[RED].hp_ + eq_now[BLUE].hp_ + eq_now[GREEN].hp_ + eq_now[ARM].hp_;

	//プレイヤー動作
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT))
		player.battle_ani_ = 7;
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) && player.pos_x_ < MAX_X) {
		player.pos_x_ += PLAYER_SPEED;
		ani_frame--;
		if (ani_frame == 0) {
			player.battle_ani_++;
			ani_frame = 20;
			if (player.battle_ani_ == 9)
				player.battle_ani_ = 6;
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT))
		player.battle_ani_ = 4;
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) && player.pos_x_ > MIN_X) {
		player.pos_x_ -= PLAYER_SPEED;
		ani_frame--;
		if (ani_frame == 0) {
			player.battle_ani_++;
			ani_frame = 20;
			if (player.battle_ani_ == 6)
				player.battle_ani_ = 3;
		}
	}
	if (player.battle_ani_ < 3 || player.battle_ani_ > 8)
		player.battle_ani_ = 4;

	//画面外にいかない
	if (player.pos_x_ > MAX_X)
		player.pos_x_ = MAX_X;
	if (player.pos_x_ < MIN_X)
		player.pos_x_ = MIN_X;

	//ジャンプ処理
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && player.pos_y_ == BATTLE_Y) {
		jump_power = 24;
		player.pos_y_ -= 1;
	}
	//空中にいたら落下する
	if (player.pos_y_ < BATTLE_Y) {
		player.pos_y_ += 1.5F * jump_s - jump_power;
		jump_s++;
	}
	//着地
	if (player.pos_y_ >= BATTLE_Y) {
		player.pos_y_ = BATTLE_Y;
		jump_s = 0;
		jump_power = 0;
	}

	//属性切り替え処理
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A) && mode_rock == 0) {
		PlaySoundMem(se_change, DX_PLAYTYPE_BACK);
		player.mode_ -= 1;
		mode_rock = 300;
		if (player.mode_ == -1)
			player.mode_ = 2;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D) && mode_rock == 0) {
		PlaySoundMem(se_change, DX_PLAYTYPE_BACK);
		player.mode_ += 1;
		mode_rock = 300;
		if (player.mode_ == 3)
			player.mode_ = 0;
	}
	if (mode_rock != 0)
		mode_rock--;

	//向きを取得
	switch (player.battle_ani_)
	{
	case 3:
	case 4:
	case 5:
		player.dir_ = LEFT;
		break;
	case 6:
	case 7:
	case 8:
		player.dir_ = RIGHT;
		break;
	default:
		break;
	}

	//スプリント
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LSHIFT) && sprint_cd == 0) {
		PlaySoundMem(se_sprint, DX_PLAYTYPE_BACK);
		switch (player.dir_)
		{
		case LEFT:
			sprint_x[LEFT] = player.pos_x_;
			sprint_y[LEFT] = player.pos_y_;
			player.pos_x_ -= 200;
			sprint_cd = 600;
			st_sprint[LEFT] = false;
			if (player.pos_x_ < MIN_X)
				player.pos_x_ = MIN_X;
			break;
		case RIGHT:
			sprint_x[RIGHT] = player.pos_x_;
			sprint_y[RIGHT] = player.pos_y_;
			player.pos_x_ += 200;
			sprint_cd = 600;
			st_sprint[RIGHT] = false;
			if (player.pos_x_ > MAX_X)
				player.pos_x_ = MAX_X;
			break;
		default:
			break;
		}
	}
	if (sprint_cd != 0)
		sprint_cd--;


	//スキル処理
	//スキル1
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z) && cd_count[player.mode_][SK_Z] == 0) {
		PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
		skill_key[SK_Z] = 1;
		on_sk[SK_Z] = 10;
		skill_frame[player.mode_][SK_Z] = 0;
		st_skill[player.mode_][SK_Z] = false;
		cd_count[player.mode_][SK_Z] = skill[player.mode_][SK_Z].cd_[skill[player.mode_][SK_Z].slv_] * player.color_cd_[player.mode_] * 60;
	}
	if (on_sk[SK_Z] != 0) {
		on_sk[SK_Z]--;
		if (on_sk[SK_Z] == 0)
			skill_key[SK_Z] = 0;
	}

	//スキル2
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_X) && cd_count[player.mode_][SK_X] == 0) {
		PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
		skill_key[SK_X] = 1;
		on_sk[SK_X] = 10;
		skill_frame[player.mode_][SK_X] = 0;
		st_skill[player.mode_][SK_X] = false;
		cd_count[player.mode_][SK_X] = skill[player.mode_][SK_X].cd_[skill[player.mode_][SK_X].slv_] * player.color_cd_[player.mode_] * 60;
	}
	if (on_sk[SK_X] != 0) {
		on_sk[SK_X]--;
		if (on_sk[SK_X] == 0)
			skill_key[SK_X] = 0;
	}

	//スキル3
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C) && cd_count[player.mode_][SK_C] == 0) {
		PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
		skill_key[SK_C] = 1;
		on_sk[SK_C] = 10;
		skill_frame[player.mode_][SK_C] = 0;
		st_skill[player.mode_][SK_C] = false;
		cd_count[player.mode_][SK_C] = skill[player.mode_][SK_C].cd_[skill[player.mode_][SK_C].slv_] * player.color_cd_[player.mode_] * 60;
	}
	if (on_sk[SK_C] != 0) {
		on_sk[SK_C]--;
		if (on_sk[SK_C] == 0)
			skill_key[SK_C] = 0;
	}

	//スキルクールダウン進行
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			if (cd_count[i][k] > 0)
				cd_count[i][k]--;
			if (cd_count[i][k] < 0)
				cd_count[i][k] = 0;
		}
	}

	//スキル発動
	playSkill();

	//ダメージ処理
	if (damage_no != 0)
		damage_no--;
	if (player_damage == true)
		playerDamagemotion();

	//ダメージ表記
	if (damage_num_count != 0) {
		damage_num_count--;
		DrawFormatStringToHandle(player.pos_x_ - 15, player.pos_y_ - 70, C_RED, font32, "%d", damage_num);
	}

}

//ダメージを受けたときの処理
//乱数
int damage_random = 0;

void playerDamage(int damage, int enemy_color) {
	if (damage_no == 0) {
		PlaySoundMem(se_damage, DX_PLAYTYPE_BACK);
		player_damage = true;
		damage_no = 60;
		//ダメージ乱数計算
		damage_random = rand() % (damage / 5);
		damage += damage_random;
		//属性相性判定
		if (player.mode_ == enemy_color - 1 || player.mode_ == enemy_color + 2) {
			damage = damage / 2;
		}
		else if (player.mode_ == enemy_color + 1 || player.mode_ == enemy_color - 2) {
			damage = damage * 2;
		}
		//hpを減らす
		player.hp_ -= damage;
		//ダメージ表示用の変数に数値を渡す
		damage_num = damage;
		damage_num_count = 40;
		//hpが0になったら
		if (player.hp_ <= 0) {
			player.hp_ = 0;
			//ゲームオーバー処理
			StopSoundMem(sound_battle);
			StopSoundMem(sound_battle_magician);
			StopSoundMem(sound_battle_fairy);
			StopSoundMem(sound_battle_doragon);
			PlaySoundMem(sound_gameover, DX_PLAYTYPE_LOOP, 1);
			play_mode = GAME_OVER;
			player_damage = false;
		}
	}
}

//ダメージを受けたときの動作
int damage_ani = 0;

void playerDamagemotion() {
	damage_ani++;
	//跳ねる
	if (damage_ani == 1) {
		player.pos_y_ -= 1;
		jump_power = 10;
		jump_s = 0;
	}
	//向いてる向きによって後退する
	switch (player.dir_) {
	case LEFT:
		player.pos_x_ += 10;
		break;
	case RIGHT:
		player.pos_x_ -= 10;
		break;
	}
	if (damage_ani == 10) {
		damage_ani = 0;
		player_damage = false;
	}
}

//ゲームオーバー処理
//ゲームオーバー座標
const int GAMEOVER_X1 = 400;
const int GAMEOVER_Y1 = 300;
const int GAMEOVER_X2 = 450;
const int GAMEOVER_Y2 = 340;

void gameOver() {
	//プレイヤー表示
	DrawRotaGraph(player.pos_x_, player.pos_y_, 2, player_rota, player.img_[player.mode_][player.battle_ani_], true);
	//90度回るまで回転させる
	switch (player.dir_) {
	case LEFT:
		if (player_rota < (PI / 2))
			player_rota += 0.01f;
		//回転しきったら文字を表示
		if (player_rota >= (PI / 2)) {
			player_rota = PI / 2;
			DrawStringToHandle(GAMEOVER_X1, GAMEOVER_Y1, "げーむおーばー", C_RED, font32);
			DrawStringToHandle(GAMEOVER_X2, GAMEOVER_Y2, "-Press [Enter]-", 0, font16);
			player.pos_y_ = BATTLE_Y + 10;
			//Enterキーで前の画面に戻る
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				StopSoundMem(sound_gameover);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
			}
		}
		break;
	case RIGHT:
		if (player_rota > -(PI / 2))
			player_rota -= 0.01f;
		//回転しきったら文字を表示
		if (player_rota <= -(PI / 2)) {
			player_rota = -(PI / 2);
			DrawStringToHandle(GAMEOVER_X1, GAMEOVER_Y1, "げーむおーばー", C_RED, font32);
			DrawStringToHandle(GAMEOVER_X2, GAMEOVER_Y2, "-Press [Enter]-", 0, font16);
			player.pos_y_ = BATTLE_Y + 10;
			//Enterキーで前の画面に戻る
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				StopSoundMem(sound_gameover);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
			}
		}
		break;
	}

}

bool init_clear = false;
int clear_random = 0;
bool equip_random = false;
int img_clear_mes = 0;
bool delete_ui = false;
//ドロップ確立
int item_drop_pal = 30;

void stageClear() {
	if (!init_clear) {
		img_clear_mes = LoadGraph("graphics/bg/message_frame_02_light.png");
		init_clear = true;
	}
	//キャラ表示
	DrawRotaGraph(player.pos_x_, player.pos_y_, 2, 0, player.img_[player.mode_][player.battle_ani_], true);
	DrawStringToHandle(GAMEOVER_X1, GAMEOVER_Y1, "ステージクリア！", YELLOW, font32);
	DrawStringToHandle(GAMEOVER_X2, GAMEOVER_Y2, "-Press [Enter]-", 0, font16);
	//装備ドロップ
	if (equip_random == true) {
		delete_ui = true;
		DrawRotaGraph(512, 680, 0.8F, 0, img_clear_mes, true);
		switch (stage) {
		case 1:
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[RED][1].name_.c_str());
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				getEquipment(RED, 1);
				equip_random = false;
				StopSoundMem(sound_clear);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
				delete_ui = false;
			}
			break;
		case 2:
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[GREEN][2].name_.c_str());
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				getEquipment(GREEN, 2);
				equip_random = false;
				StopSoundMem(sound_clear);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
				delete_ui = false;
			}
			break;
		case 3:
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[BLUE][1].name_.c_str());
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				getEquipment(BLUE, 1);
				equip_random = false;
				StopSoundMem(sound_clear);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
				delete_ui = false;
			}
			break;
		case 4:
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[GREEN][3].name_.c_str());
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				getEquipment(GREEN, 3);
				equip_random = false;
				StopSoundMem(sound_clear);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
				delete_ui = false;
			}
			break;
		case 5:
			if (clear_random < 10) {
				DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[ARM][1].name_.c_str());
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
					PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
					getEquipment(ARM, 3);
					equip_random = false;
					StopSoundMem(sound_clear);
					PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
					scene = SCENE_PLAY;
					delete_ui = false;
				}
			}
			else {
				DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[RED][3].name_.c_str());
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
					PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
					getEquipment(RED, 3);
					equip_random = false;
					StopSoundMem(sound_clear);
					PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
					scene = SCENE_PLAY;
					delete_ui = false;
				}
			}
			break;
		case 6:
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[BLUE][3].name_.c_str());
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				getEquipment(BLUE, 3);
				equip_random = false;
				StopSoundMem(sound_clear);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
				delete_ui = false;
			}
			break;
		case 7:
			DrawFormatStringToHandle(100, 660, BROWN, font32, "%s を手に入れた！", eq_date[ARM][3].name_.c_str());
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
				getEquipment(ARM, 3);
				equip_random = false;
				StopSoundMem(sound_clear);
				PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
				scene = SCENE_PLAY;
				delete_ui = false;
			}
			break;
		}
	}
	//Enterキーで前の画面に戻る
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && !equip_random) {
		clear_random = rand() % 100;
		if (clear_random > item_drop_pal) {
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			StopSoundMem(sound_clear);
			PlaySoundMem(sound_play, DX_PLAYTYPE_LOOP, 1);
			scene = SCENE_PLAY;
		}
		else{
			PlaySoundMem(se_enter, DX_PLAYTYPE_BACK);
			equip_random = true;
		}
	}
}

void getSkillani() {
	//スプリントアニメーション読み込み
	LoadDivGraph("graphics/ani/sprint_left.png", 10, 10, 1, 1920 / 10, 192 / 1, sprint_ani[LEFT]);
	LoadDivGraph("graphics/ani/sprint_right.png", 10, 10, 1, 1920 / 10, 192 / 1, sprint_ani[RIGHT]);
	//赤スキルアニメーション読み込み
	LoadDivGraph("graphics/ani/ani_red0_left.png", 10, 10, 1, 2400 / 10, 240 / 1, skill_ani[RED][SK_Z][LEFT]);
	LoadDivGraph("graphics/ani/ani_red0_right.png", 10, 10, 1, 2400 / 10, 240 / 1, skill_ani[RED][SK_Z][RIGHT]);
	LoadDivGraph("graphics/ani/ani_red1.png", 20, 5, 4, 960 / 5, 768 / 4, skill_ani[RED][SK_X][0]);
	LoadDivGraph("graphics/ani/ani_red2.png", 16, 1, 16, 320 / 1, 3840 / 16, skill_ani[RED][SK_C][0]);
	//緑スキルアニメーション読み込み
	LoadDivGraph("graphics/ani/ani_green0.png", 15, 5, 3, 960 / 5, 576 / 3, skill_ani[GREEN][SK_Z][0]);
	LoadDivGraph("graphics/ani/ani_green1.png", 15, 5, 3, 960 / 5, 576 / 3, skill_ani[GREEN][SK_X][0]);
	LoadDivGraph("graphics/ani/ani_green2.png", 8, 8, 1, 1920 / 8, 240 / 1, skill_ani[GREEN][SK_C][0]);
	//青スキルアニメーション読み込み
	LoadDivGraph("graphics/ani/ani_blue0.png", 8, 8, 1, 1920 / 8, 240 / 1, skill_ani[BLUE][SK_Z][0]);
	LoadDivGraph("graphics/ani/ani_blue1.png", 8, 1, 8, 320 / 1, 960 / 8, skill_ani[BLUE][SK_X][0]);
	LoadDivGraph("graphics/ani/ani_blue2.png", 15, 5, 3, 3200 / 5, 1440 / 3, skill_ani[BLUE][SK_C][0]);
}

void playSkill() {
	sk_ani_frame--;
	if (sk_ani_frame == 0)
		sk_ani_frame = COUNT;

	//スプリント
	if (!st_sprint[LEFT]) {
		DrawRotaGraph(sprint_x[LEFT], sprint_y[LEFT], 1, 0, sprint_ani[LEFT][sprint_frame[LEFT]], true);
		if (sk_ani_frame == COUNT)
			sprint_frame[LEFT]++;
		if (sk_ani_frame == COUNT / 2)
			sprint_frame[LEFT]++;
		if (sprint_frame[LEFT] > 9) {
			sprint_frame[LEFT] = 0;
			st_sprint[LEFT] = true;
		}
	}
	if (!st_sprint[RIGHT]) {
		DrawRotaGraph(sprint_x[RIGHT], sprint_y[RIGHT], 1, 0, sprint_ani[RIGHT][sprint_frame[RIGHT]], true);
		if (sk_ani_frame == COUNT)
			sprint_frame[RIGHT]--;
		if (sk_ani_frame == COUNT / 2)
			sprint_frame[RIGHT]--;
		if (sprint_frame[RIGHT] < 0) {
			sprint_frame[RIGHT] = 9;
			st_sprint[RIGHT] = true;
		}
	}

	//赤Z
	if (!st_skill[RED][SK_Z]) {
		if (skill_frame[RED][SK_Z] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[RED][SK_Z] = player.pos_x_ - 10;
				skill_y[RED][SK_Z] = player.pos_y_ - 50;
				skill_dir[RED][SK_Z] = LEFT;
				break;
			case RIGHT:
				skill_x[RED][SK_Z] = player.pos_x_ + 10;
				skill_y[RED][SK_Z] = player.pos_y_ - 50;
				skill_dir[RED][SK_Z] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[RED][SK_Z], skill_y[RED][SK_Z], 1, 0, skill_ani[RED][SK_Z][skill_dir[RED][SK_Z]][skill_frame[RED][SK_Z]], true);
		if (sk_ani_frame == COUNT)
			skill_frame[RED][SK_Z]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[RED][SK_Z]++;
		if (skill_frame[RED][SK_Z] > 10) {
			skill_frame[RED][SK_Z] = 0;
			st_skill[RED][SK_Z] = true;
		}
		//ダメージ処理
		if (skill_frame[RED][SK_Z] == 4 && (sk_ani_frame == COUNT || sk_ani_frame == COUNT / 2)) {
			for (int i = 0; i < enemy_num[stage - 1]; i++) {
				switch (skill_dir[RED][SK_Z]) {
				case LEFT:
					if (skill_x[RED][SK_Z] - (80 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[RED][SK_Z] + (10 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
						&& skill_y[RED][SK_Z] - (50 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[RED][SK_Z] + (50 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
						enemyDamage(i, RED, SK_Z);
					}
					break;
				case RIGHT:
					if (skill_x[RED][SK_Z] - (10 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[RED][SK_Z] + (80 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
						&& skill_y[RED][SK_Z] - (50 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[RED][SK_Z] + (50 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
						enemyDamage(i, RED, SK_Z);
					}
					break;
				}
				if (battle_enemy[i].move_ == ENEMY_DAMAGE)
					break;
			}
		}
	}

	//赤X
	if (!st_skill[RED][SK_X]) {
		if (skill_frame[RED][SK_X] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[RED][SK_X] = player.pos_x_ - 20;
				skill_y[RED][SK_X] = player.pos_y_;
				skill_dir[RED][SK_X] = LEFT;
				break;
			case RIGHT:
				skill_x[RED][SK_X] = player.pos_x_ + 20;
				skill_y[RED][SK_X] = player.pos_y_;
				skill_dir[RED][SK_X] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[RED][SK_X], skill_y[RED][SK_X], 1, 0, skill_ani[RED][SK_X][0][skill_frame[RED][SK_X]], true);
		switch (skill_dir[RED][SK_X])
		{
		case LEFT:
			skill_x[RED][SK_X] -= 10;
			break;
		case RIGHT:
			skill_x[RED][SK_X] += 10;
		}
		if (sk_ani_frame == COUNT)
			skill_frame[RED][SK_X]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[RED][SK_X]++;
		if (skill_frame[RED][SK_X] > 20) {
			skill_frame[RED][SK_X] = 0;
			st_skill[RED][SK_X] = true;
		}
		//ダメージ処理
		for (int i = 0; i < enemy_num[stage - 1]; i++) {
			if (skill_x[RED][SK_X] - (40 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[RED][SK_X] + (40 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
				&& skill_y[RED][SK_X] - (20 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[RED][SK_X] + (20 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
				enemyDamage(i, RED, SK_X);
				skill_frame[RED][SK_X] = 0;
				st_skill[RED][SK_X] = true;
			}
		}
	}

	//赤C
	if (!st_skill[RED][SK_C]) {
		if (skill_frame[RED][SK_C] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[RED][SK_C] = player.pos_x_ - 100;
				skill_y[RED][SK_C] = player.pos_y_ - 80;
				break;
			case RIGHT:
				skill_x[RED][SK_C] = player.pos_x_ + 100;
				skill_y[RED][SK_C] = player.pos_y_ - 80;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[RED][SK_C], skill_y[RED][SK_C], 1, 0, skill_ani[RED][SK_C][0][skill_frame[RED][SK_C]], true);
		if (sk_ani_frame == COUNT)
			skill_frame[RED][SK_C]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[RED][SK_C]++;
		if (skill_frame[RED][SK_C] > 16) {
			skill_frame[RED][SK_C] = 0;
			st_skill[RED][SK_C] = true;
		}
		//ダメージ処理
		if (skill_frame[RED][SK_C] == 4 && (sk_ani_frame == COUNT || sk_ani_frame == COUNT / 2)) {
			PlaySoundMem(se_bomb, DX_PLAYTYPE_BACK);
			for (int i = 0; i < enemy_num[stage - 1]; i++) {
				if (skill_x[RED][SK_C] - (100 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[RED][SK_C] + (100 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
					&& skill_y[RED][SK_C] - (80 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[RED][SK_C] + (80 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
					enemyDamage(i, RED, SK_C);
				}
			}
		}
	}

	//緑Z
	if (!st_skill[GREEN][SK_Z]) {
		if (skill_frame[GREEN][SK_Z] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[GREEN][SK_Z] = player.pos_x_ - 50;
				skill_y[GREEN][SK_Z] = player.pos_y_;
				break;
			case RIGHT:
				skill_x[GREEN][SK_Z] = player.pos_x_ + 50;
				skill_y[GREEN][SK_Z] = player.pos_y_;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[GREEN][SK_Z], skill_y[GREEN][SK_Z], 1.5f, 0, skill_ani[GREEN][SK_Z][0][skill_frame[GREEN][SK_Z]], true);
		if (sk_ani_frame == COUNT)
			skill_frame[GREEN][SK_Z]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[GREEN][SK_Z]++;
		if (skill_frame[GREEN][SK_Z] > 6) {
			skill_frame[GREEN][SK_Z] = 0;
			st_skill[GREEN][SK_Z] = true;
		}
		//ダメージ処理
		if (skill_frame[GREEN][SK_Z] == 2 && (sk_ani_frame == COUNT || sk_ani_frame == COUNT / 2)) {
			for (int i = 0; i < enemy_num[stage - 1]; i++) {
				if (skill_x[GREEN][SK_Z] - (40 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[GREEN][SK_Z] + (40 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
					&& skill_y[GREEN][SK_Z] - (40 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[GREEN][SK_Z] + (40 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
					enemyDamage(i, GREEN, SK_Z);
					if (battle_enemy[i].move_ == ENEMY_DAMAGE)
						break;
				}
			}
		}
	}

	//緑X
	if (!st_skill[GREEN][SK_X]) {
		if (skill_frame[GREEN][SK_X] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[GREEN][SK_X] = player.pos_x_ - 50;
				skill_y[GREEN][SK_X] = player.pos_y_;
				skill_dir[GREEN][SK_X] = LEFT;
				break;
			case RIGHT:
				skill_x[GREEN][SK_X] = player.pos_x_ + 50;
				skill_y[GREEN][SK_X] = player.pos_y_;
				skill_dir[GREEN][SK_X] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[GREEN][SK_X], skill_y[GREEN][SK_X], 1.5f, 0, skill_ani[GREEN][SK_X][0][skill_frame[GREEN][SK_X]], true);
		switch (skill_dir[GREEN][SK_X])
		{
		case LEFT:
			skill_x[GREEN][SK_X] -= 20;
			break;
		case RIGHT:
			skill_x[GREEN][SK_X] += 20;
		}
		if (sk_ani_frame == COUNT)
			skill_frame[GREEN][SK_X]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[GREEN][SK_X]++;
		if (skill_frame[GREEN][SK_X] > 15) {
			skill_frame[GREEN][SK_X] = 0;
			st_skill[GREEN][SK_X] = true;
		}
		//ダメージ処理
		for (int i = 0; i < enemy_num[stage - 1]; i++) {
			if (skill_x[GREEN][SK_X] - (40 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[GREEN][SK_X] + (40 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
				&& skill_y[GREEN][SK_X] - (40 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[GREEN][SK_X] + (40 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
				enemyDamage(i, GREEN, SK_X);
				skill_frame[GREEN][SK_X] = 0;
				st_skill[GREEN][SK_X] = true;
			}
		}
	}

	//緑C
	if (!st_skill[GREEN][SK_C]) {
		if (skill_frame[GREEN][SK_C] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[GREEN][SK_C] = player.pos_x_ - 100;
				skill_y[GREEN][SK_C] = player.pos_y_ - 130;
				skill_dir[GREEN][SK_C] = LEFT;
				break;
			case RIGHT:
				skill_x[GREEN][SK_C] = player.pos_x_ + 100;
				skill_y[GREEN][SK_C] = player.pos_y_ - 130;
				skill_dir[GREEN][SK_C] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[GREEN][SK_C], skill_y[GREEN][SK_C], 1.5F, 0, skill_ani[GREEN][SK_C][0][skill_frame[GREEN][SK_C]], true);
		switch (skill_dir[GREEN][SK_C])
		{
		case LEFT:
			skill_x[GREEN][SK_C] -= 10;
			break;
		case RIGHT:
			skill_x[GREEN][SK_C] += 10;
		}
		if (sk_ani_frame == COUNT)
			skill_frame[GREEN][SK_C]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[GREEN][SK_C]++;
		if (skill_frame[GREEN][SK_C] > 16) {
			skill_frame[GREEN][SK_C] = 0;
			for (int i = 0; i < enemy_num[stage - 1]; i++) {
				enemy_damage_rock[i][GREEN][SK_C] = false;
			}
			st_skill[GREEN][SK_C] = true;
		}
		//ダメージ処理
		for (int i = 0; i < enemy_num[stage - 1]; i++) {
			if (skill_frame[GREEN][SK_C] < 8 && skill_frame[GREEN][SK_C] > 1) {
				if (skill_x[GREEN][SK_C] - (100 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[GREEN][SK_C] + (100 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
					&& skill_y[GREEN][SK_C] - (130 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[GREEN][SK_C] + (130 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
					if (!enemy_damage_rock[i][GREEN][SK_C]) {
						enemyDamage(i, GREEN, SK_C);
						enemy_damage_rock[i][GREEN][SK_C] = true;
					}
				}
			}
		}
	}

	//青Z
	if (!st_skill[BLUE][SK_Z]) {
		if (skill_frame[BLUE][SK_Z] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[BLUE][SK_Z] = player.pos_x_ - 20;
				skill_y[BLUE][SK_Z] = player.pos_y_;
				skill_dir[BLUE][SK_Z] = LEFT;
				break;
			case RIGHT:
				skill_x[BLUE][SK_Z] = player.pos_x_ + 20;
				skill_y[BLUE][SK_Z] = player.pos_y_;
				skill_dir[BLUE][SK_Z] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[BLUE][SK_Z], skill_y[BLUE][SK_Z], 1, 0, skill_ani[BLUE][SK_Z][0][skill_frame[BLUE][SK_Z]], true);
		switch (skill_dir[BLUE][SK_Z])
		{
		case LEFT:
			skill_x[BLUE][SK_Z] -= 15;
			break;
		case RIGHT:
			skill_x[BLUE][SK_Z] += 15;
		}
		if (sk_ani_frame == COUNT)
			skill_frame[BLUE][SK_Z]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[BLUE][SK_Z]++;
		if (skill_frame[BLUE][SK_Z] > 8) {
			skill_frame[BLUE][SK_Z] = 0;
			st_skill[BLUE][SK_Z] = true;
		}
		//ダメージ処理
		for (int i = 0; i < enemy_num[stage - 1]; i++) {
			if (skill_x[BLUE][SK_Z] - (40 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[BLUE][SK_Z] + (40 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
				&& skill_y[BLUE][SK_Z] - (40 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[BLUE][SK_Z] + (40 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
				enemyDamage(i, BLUE, SK_Z);
				skill_frame[BLUE][SK_Z] = 0;
				st_skill[BLUE][SK_Z] = true;
			}
		}
	}

	//青X
	if (!st_skill[BLUE][SK_X]) {
		if (skill_frame[BLUE][SK_X] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[BLUE][SK_X] = player.pos_x_ - 260;
				skill_y[BLUE][SK_X] = player.pos_y_ - 35;
				break;
			case RIGHT:
				skill_x[BLUE][SK_X] = player.pos_x_ + 260;
				skill_y[BLUE][SK_X] = player.pos_y_ - 35;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[BLUE][SK_X], skill_y[BLUE][SK_X], 1.5f, 0, skill_ani[BLUE][SK_X][0][skill_frame[BLUE][SK_X]], true);
		if (sk_ani_frame == COUNT)
			skill_frame[BLUE][SK_X]++;
		if (sk_ani_frame == COUNT / 2)
			skill_frame[BLUE][SK_X]++;
		if (skill_frame[BLUE][SK_X] > 8) {
			skill_frame[BLUE][SK_X] = 0;
			st_skill[BLUE][SK_X] = true;
		}
		//ダメージ処理
		if (skill_frame[BLUE][SK_X] == 2 && (sk_ani_frame == COUNT || sk_ani_frame == COUNT / 2)) {
			for (int i = 0; i < enemy_num[stage - 1]; i++) {
				if (skill_x[BLUE][SK_X] - (260 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[BLUE][SK_X] + (260 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
					&& skill_y[BLUE][SK_X] - (35 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[BLUE][SK_X] + (35 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
					enemyDamage(i, BLUE, SK_X);
				}
			}
		}

	}

	//青C
	if (!st_skill[BLUE][SK_C]) {
		if (skill_frame[BLUE][SK_C] == 0) {
			switch (player.dir_)
			{
			case LEFT:
				skill_x[BLUE][SK_C] = player.pos_x_ - 652;
				skill_y[BLUE][SK_C] = player.pos_y_;
				skill_dir[BLUE][SK_C] = LEFT;
				break;
			case RIGHT:
				skill_x[BLUE][SK_C] = player.pos_x_ + 140;
				skill_y[BLUE][SK_C] = player.pos_y_;
				skill_dir[BLUE][SK_C] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(skill_x[BLUE][SK_C], skill_y[BLUE][SK_C], 0.4F, 0, skill_ani[BLUE][SK_C][0][skill_frame[BLUE][SK_C]], true);
		DrawRotaGraph(skill_x[BLUE][SK_C] + 256, skill_y[BLUE][SK_C], 0.4F, 0, skill_ani[BLUE][SK_C][0][skill_frame[BLUE][SK_C]], true);
		DrawRotaGraph(skill_x[BLUE][SK_C] + 512, skill_y[BLUE][SK_C], 0.4F, 0, skill_ani[BLUE][SK_C][0][skill_frame[BLUE][SK_C]], true);
		if (sk_ani_frame == COUNT)
			skill_frame[BLUE][SK_C]++;
		if (skill_frame[BLUE][SK_C] > 4) {
			skill_frame[BLUE][SK_C] = 0;
			st_skill[BLUE][SK_C] = true;
		}
		//ダメージ処理
		if (skill_frame[BLUE][SK_C] == 1 && sk_ani_frame == COUNT) {
			PlaySoundMem(se_beam, DX_PLAYTYPE_BACK);
			for (int i = 0; i < enemy_num[stage - 1]; i++) {
				switch (skill_dir[BLUE][SK_C]) {
				case LEFT:
					if (skill_x[BLUE][SK_C] - (128 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[BLUE][SK_C] + (652 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
						&& skill_y[BLUE][SK_C] - (96 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[BLUE][SK_C] + (96 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
						enemyDamage(i, BLUE, SK_C);
					}
					break;
				case RIGHT:
					if (skill_x[BLUE][SK_C] - (140 + battle_enemy[i].r_) < battle_enemy[i].pos_x_ && skill_x[BLUE][SK_C] + (640 + battle_enemy[i].r_) > battle_enemy[i].pos_x_
						&& skill_y[BLUE][SK_C] - (96 + battle_enemy[i].r_) < battle_enemy[i].pos_y_ && skill_y[BLUE][SK_C] + (96 + battle_enemy[i].r_) > battle_enemy[i].pos_y_) {
						enemyDamage(i, BLUE, SK_C);
					}
					break;
				}
			}
		}
	}
}