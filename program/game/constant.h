#pragma once
#include "../dxlib_ext/dxlib_ext.h"

const float PI = 3.141592654F;

const int SCENE_TITLE = 0;
const int SCENE_PLAY = 1;
const int SCENE_BATTLE = 2;
const int SCENE_MENU = 3;
const int SCENE_SHOP = 4;

extern int scene;
extern int font16;
extern int font32;

//RGB(B,G,R)
const int C_RED = RGB(0, 0, 255);
const int C_GREEN = RGB(0, 255, 0);
const int C_BLUE = RGB(255, 0, 0);
const int BROWN = RGB(48, 78, 115);
const int YELLOW = RGB(0, 225, 255);

//画面端座標
const int MIN_X = 30;
const int MAX_X = 995;

//プレイモード
extern int play_mode;
const int STAGE_PLAY = 0;
const int GAME_OVER = 1;
const int STAGE_CLEAR = 2;

extern int now_scene;

//サウンド
//BGM
extern int sound_title;
extern int sound_play;
extern int sound_shop;
extern int sound_clear;
extern int sound_gameover;
extern int sound_battle;
extern int sound_battle_magician;
extern int sound_battle_fairy;
extern int sound_battle_doragon;
//SE
extern int se_enter;
extern int se_esc;
extern int se_select;
extern int se_menu;
extern int se_buy;
extern int se_damage;
extern int se_sowrd;
extern int se_bomb;
extern int se_beam;
extern int se_warp;
extern int se_change;
extern int se_sprint;