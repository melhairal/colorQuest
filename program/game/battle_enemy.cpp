#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

//ƒvƒƒgƒ^ƒCƒvéŒ¾
void aiSlime(int id);
void aiBird(int id);
void aiMagician(int id);
void aiFairy(int id);
void aiDragon(int id);
void battleStage1();
void battleStage2();
void battleStage3();
void battleStage4();
void battleStage5();
void battleStage6();
void battleStage7();
extern int enemy_timer[3];

int stage = 1;
int clear_flag[7] = { false,false,false,false,false,false,false };
int clear_num = 1;
bool init_stage[7] = { false,false,false,false,false,false,false };
int enemy_num[7] = { 1,1,1,1,1,1,1 };
int clear_exp[7] = { 300,500,700,1200,1800,2900,5000 };
extern int exp_timer;

extern bool magician_red_attack[3];
extern bool magician_blue_attack[3];
extern bool magician_green_attack[3];
extern bool fairy_blue_attack[2][3];
extern bool fairy_green_attack[2][3];

void battleEnemy() {
	switch (stage) {
	case 1:
		battleStage1();
		break;
	case 2:
		battleStage2();
		break;
	case 3:
		battleStage3();
		break;
	case 4:
		battleStage4();
		break;
	case 5:
		battleStage5();
		break;
	case 6:
		battleStage6();
		break;
	case 7:
		battleStage7();
		break;
	}
}

void battleStage1() {
	//‰Šúİ’è
	if (!init_stage[0]) {
		PlaySoundMem(sound_battle, DX_PLAYTYPE_LOOP, 1);
		battle_enemy[0] = enemy[Enemy::BLUESLIME];
		battle_enemy[1] = enemy[Enemy::BLUESLIME];
		battle_enemy[2] = enemy[Enemy::REDSLIME];
		battle_enemy[0].pos_x_ = 600;
		battle_enemy[1].pos_x_ = 700;
		battle_enemy[2].pos_x_ = 800;
		enemy_num[0] = 3;
		for (int i = 0; i < enemy_num[0]; i++) {
			enemy_timer[i] = 0;
			enemy_damage_count[i] = 0;
		}
		init_stage[0] = true;
	}
	//“GAI“Ç‚İ‚İ
	if (battle_enemy[0].move_ != ENEMY_DEATH)
		aiSlime(0);
	if (battle_enemy[1].move_ != ENEMY_DEATH)
		aiSlime(1);
	if (battle_enemy[2].move_ != ENEMY_DEATH)
		aiSlime(2);
	//“G•`‰æ
	for (int i = 0; i < enemy_num[0]; i++) {
		if (battle_enemy[i].move_ != ENEMY_DEATH) {
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_, 1.5F, 0, battle_enemy[i].img_[battle_enemy[i].move_][battle_enemy[i].frame_], true, battle_enemy[i].dir_);
		}
	}
	//ƒNƒŠƒA”»’è
	if (battle_enemy[0].move_ == ENEMY_DEATH && battle_enemy[1].move_ == ENEMY_DEATH && battle_enemy[2].move_ == ENEMY_DEATH) {
		player.exp_ += clear_exp[0];
		exp_timer = 90;
		StopSoundMem(sound_battle);
		PlaySoundMem(sound_clear, DX_PLAYTYPE_LOOP, 1);
		play_mode = STAGE_CLEAR;
		clear_flag[0] = true;
		if (clear_num < 2) {
			clear_num += 1;
		}
	}
}

void battleStage2() {
	//‰Šúİ’è
	if (!init_stage[1]) {
		PlaySoundMem(sound_battle, DX_PLAYTYPE_LOOP, 1);
		battle_enemy[0] = enemy[Enemy::REDSLIME];
		battle_enemy[1] = enemy[Enemy::REDSLIME];
		battle_enemy[2] = enemy[Enemy::GREENBIRD];
		battle_enemy[0].pos_x_ = 600;
		battle_enemy[1].pos_x_ = 700;
		battle_enemy[2].pos_x_ = 800;
		battle_enemy[2].pos_y_ = 450;
		enemy_num[1] = 3;
		for (int i = 0; i < enemy_num[1]; i++) {
			enemy_timer[i] = 0;
			enemy_damage_count[i] = 0;
		}
		init_stage[1] = true;
	}
	//“GAI“Ç‚İ‚İ
	if (battle_enemy[0].move_ != ENEMY_DEATH)
		aiSlime(0);
	if (battle_enemy[1].move_ != ENEMY_DEATH)
		aiSlime(1);
	if (battle_enemy[2].move_ != ENEMY_DEATH)
		aiBird(2);
	//“G•`‰æ
	for (int i = 0; i < enemy_num[1]; i++) {
		if (battle_enemy[i].move_ != ENEMY_DEATH) {
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_, 1.5F, 0, battle_enemy[i].img_[battle_enemy[i].move_][battle_enemy[i].frame_], true, battle_enemy[i].dir_);
		}
	}
	//ƒNƒŠƒA”»’è
	if (battle_enemy[0].move_ == ENEMY_DEATH && battle_enemy[1].move_ == ENEMY_DEATH && battle_enemy[2].move_ == ENEMY_DEATH) {
		player.exp_ += clear_exp[1];
		exp_timer = 90;
		StopSoundMem(sound_battle);
		PlaySoundMem(sound_clear, DX_PLAYTYPE_LOOP, 1);
		play_mode = STAGE_CLEAR;
		clear_flag[1] = true;
		if (clear_num < 3) {
			clear_num += 1;
		}
	}
}

void battleStage3() {
	//‰Šúİ’è
	if (!init_stage[2]) {
		PlaySoundMem(sound_battle, DX_PLAYTYPE_LOOP, 1);
		battle_enemy[0] = enemy[Enemy::BLUEBIRD];
		battle_enemy[1] = enemy[Enemy::REDBIRD];
		battle_enemy[2] = enemy[Enemy::REDBIRD];
		battle_enemy[0].pos_x_ = 600;
		battle_enemy[0].pos_y_ = 450;
		battle_enemy[1].pos_x_ = 700;
		battle_enemy[1].pos_y_ = 450;
		battle_enemy[2].pos_x_ = 800;
		battle_enemy[2].pos_y_ = 450;
		enemy_num[2] = 3;
		for (int i = 0; i < enemy_num[2]; i++) {
			enemy_timer[i] = 0;
			enemy_damage_count[i] = 0;
		}
		init_stage[2] = true;
	}
	//“GAI“Ç‚İ‚İ
	if (battle_enemy[0].move_ != ENEMY_DEATH)
		aiBird(0);
	if (battle_enemy[1].move_ != ENEMY_DEATH)
		aiBird(1);
	if (battle_enemy[2].move_ != ENEMY_DEATH)
		aiBird(2);
	//“G•`‰æ
	for (int i = 0; i < enemy_num[2]; i++) {
		if (battle_enemy[i].move_ != ENEMY_DEATH) {
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_, 1.5F, 0, battle_enemy[i].img_[battle_enemy[i].move_][battle_enemy[i].frame_], true, battle_enemy[i].dir_);
		}
	}
	//ƒNƒŠƒA”»’è
	if (battle_enemy[0].move_ == ENEMY_DEATH && battle_enemy[1].move_ == ENEMY_DEATH && battle_enemy[2].move_ == ENEMY_DEATH) {
		player.exp_ += clear_exp[2];
		exp_timer = 90;
		StopSoundMem(sound_battle);
		PlaySoundMem(sound_clear, DX_PLAYTYPE_LOOP, 1);
		play_mode = STAGE_CLEAR;
		clear_flag[2] = true;
		if (clear_num < 4) {
			clear_num += 1;
		}
	}
}

void battleStage4() {
	//‰Šúİ’è
	if (!init_stage[3]) {
		PlaySoundMem(sound_battle, DX_PLAYTYPE_LOOP, 1);
		battle_enemy[0] = enemy[Enemy::BLUESLIME];
		battle_enemy[1] = enemy[Enemy::REDBIRD];
		battle_enemy[2] = enemy[Enemy::GREENMAGICIAN];
		battle_enemy[0].pos_x_ = 600;
		battle_enemy[1].pos_x_ = 700;
		battle_enemy[1].pos_y_ = 450;
		battle_enemy[2].pos_x_ = 800;
		battle_enemy[2].pos_y_ = 570;
		magician_green_attack[2] = false;
		enemy_num[3] = 3;
		for (int i = 0; i < enemy_num[3]; i++) {
			enemy_timer[i] = 0;
			enemy_damage_count[i] = 0;
		}
		init_stage[3] = true;
	}
	//“G•`‰æ
	for (int i = 0; i < enemy_num[3]; i++) {
		if (battle_enemy[i].move_ != ENEMY_DEATH) {
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_, 1.5F, 0, battle_enemy[i].img_[battle_enemy[i].move_][battle_enemy[i].frame_], true, battle_enemy[i].dir_);
		}
	}
	//ƒNƒŠƒA”»’è
	if (battle_enemy[0].move_ == ENEMY_DEATH && battle_enemy[1].move_ == ENEMY_DEATH && battle_enemy[2].move_ == ENEMY_DEATH) {
		player.exp_ += clear_exp[3];
		exp_timer = 90;
		StopSoundMem(sound_battle);
		PlaySoundMem(sound_clear, DX_PLAYTYPE_LOOP, 1);
		play_mode = STAGE_CLEAR;
		clear_flag[3] = true;
		if (clear_num < 5) {
			clear_num += 1;
		}
	}
	//“GAI“Ç‚İ‚İ
	if (battle_enemy[0].move_ != ENEMY_DEATH)
		aiSlime(0);
	if (battle_enemy[1].move_ != ENEMY_DEATH)
		aiBird(1);
	if (battle_enemy[2].move_ != ENEMY_DEATH)
		aiMagician(2);
}

void battleStage5() {
	//‰Šúİ’è
	if (!init_stage[4]) {
		PlaySoundMem(sound_battle_magician, DX_PLAYTYPE_LOOP, 1);
		battle_enemy[0] = enemy[Enemy::REDMAGICIAN];
		battle_enemy[1] = enemy[Enemy::GREENMAGICIAN];
		battle_enemy[2] = enemy[Enemy::BLUEMAGICIAN];
		battle_enemy[0].pos_x_ = 600;
		battle_enemy[0].pos_y_ = 560;
		magician_red_attack[0] = false;
		battle_enemy[1].pos_x_ = 700;
		battle_enemy[1].pos_y_ = 560;
		magician_green_attack[1] = false;
		battle_enemy[2].pos_x_ = 800;
		battle_enemy[2].pos_y_ = 560;
		magician_blue_attack[2] = false;
		enemy_num[4] = 3;
		for (int i = 0; i < enemy_num[4]; i++) {
			enemy_timer[i] = 0;
			enemy_damage_count[i] = 0;
		}
		init_stage[4] = true;
	}
	//“G•`‰æ
	for (int i = 0; i < enemy_num[4]; i++) {
		if (battle_enemy[i].move_ != ENEMY_DEATH) {
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_, 1.5F, 0, battle_enemy[i].img_[battle_enemy[i].move_][battle_enemy[i].frame_], true, battle_enemy[i].dir_);
		}
	}
	//ƒNƒŠƒA”»’è
	if (battle_enemy[0].move_ == ENEMY_DEATH && battle_enemy[1].move_ == ENEMY_DEATH && battle_enemy[2].move_ == ENEMY_DEATH) {
		player.exp_ += clear_exp[4];
		exp_timer = 90;
		StopSoundMem(sound_battle_magician);
		PlaySoundMem(sound_clear, DX_PLAYTYPE_LOOP, 1);
		play_mode = STAGE_CLEAR;
		clear_flag[4] = true;
		if (clear_num < 6) {
			clear_num += 1;
		}
	}
	//“GAI“Ç‚İ‚İ
	if (battle_enemy[0].move_ != ENEMY_DEATH)
		aiMagician(0);
	if (battle_enemy[1].move_ != ENEMY_DEATH)
		aiMagician(1);
	if (battle_enemy[2].move_ != ENEMY_DEATH)
		aiMagician(2);
}

void battleStage6() {
	//‰Šúİ’è
	if (!init_stage[5]) {
		PlaySoundMem(sound_battle_fairy, DX_PLAYTYPE_LOOP, 1);
		battle_enemy[0] = enemy[Enemy::GREENFAIRY];
		battle_enemy[1] = enemy[Enemy::BLUEFAIRY];
		battle_enemy[0].pos_x_ = 600;
		battle_enemy[0].pos_y_ = 400;
		fairy_green_attack[0][0] = false;
		fairy_green_attack[1][0] = false;
		battle_enemy[1].pos_x_ = 800;
		battle_enemy[1].pos_y_ = 400;
		fairy_blue_attack[0][1] = false;
		fairy_blue_attack[1][1] = false;
		enemy_num[5] = 2;
		for (int i = 0; i < enemy_num[5]; i++) {
			enemy_timer[i] = 0;
			enemy_damage_count[i] = 0;
		}
		init_stage[5] = true;
	}
	//“G•`‰æ
	for (int i = 0; i < enemy_num[5]; i++) {
		if (battle_enemy[i].move_ != ENEMY_DEATH) {
			DrawRotaGraph(battle_enemy[i].pos_x_, battle_enemy[i].pos_y_, 1.5F, 0, battle_enemy[i].img_[battle_enemy[i].move_][battle_enemy[i].frame_], true, battle_enemy[i].dir_);
		}
	}
	//ƒNƒŠƒA”»’è
	if (battle_enemy[0].move_ == ENEMY_DEATH && battle_enemy[1].move_ == ENEMY_DEATH) {
		player.exp_ += clear_exp[5];
		exp_timer = 90;
		StopSoundMem(sound_battle_fairy);
		PlaySoundMem(sound_clear, DX_PLAYTYPE_LOOP, 1);
		play_mode = STAGE_CLEAR;
		clear_flag[5] = true;
		if (clear_num < 7) {
			clear_num += 1;
		}
	}
	//“GAI“Ç‚İ‚İ
	if (battle_enemy[0].move_ != ENEMY_DEATH)
		aiFairy(0);
	if (battle_enemy[1].move_ != ENEMY_DEATH)
		aiFairy(1);
}

void battleStage7() {
	//‰Šúİ’è
	if (!init_stage[6]) {
		PlaySoundMem(sound_battle_doragon, DX_PLAYTYPE_LOOP, 1);
		battle_enemy[0] = enemy[Enemy::DRAGON];
		battle_enemy[0].pos_x_ = 900;
		battle_enemy[0].pos_y_ = 530;
		enemy_num[6] = 1;
		enemy_timer[0] = 0;
		enemy_damage_count[0] = 0;
		init_stage[6] = true;
	}
	//“G•`‰æ
	if (battle_enemy[0].hp_ != 0)
		DrawRotaGraph(battle_enemy[0].pos_x_, battle_enemy[0].pos_y_, 1.5F, 0, battle_enemy[0].img_[battle_enemy[0].move_][battle_enemy[0].frame_], true, battle_enemy[0].dir_);
	//“GAI“Ç‚İ‚İ
	if (battle_enemy[0].hp_ != 0)
		aiDragon(0);
	//ƒNƒŠƒA”»’è
	if (battle_enemy[0].move_ == ENEMY_DEATH) {
		exp_timer = 90;
		player.exp_ += clear_exp[6];
		StopSoundMem(sound_battle_doragon);
		PlaySoundMem(sound_clear, DX_PLAYTYPE_LOOP, 1);
		play_mode = STAGE_CLEAR;
		clear_flag[6] = true;
	}
}

