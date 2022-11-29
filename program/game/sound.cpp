#pragma once
#include "../dxlib_ext/dxlib_ext.h"

//BGM
int sound_title;
int sound_play;
int sound_shop;
int sound_clear;
int sound_gameover;
int sound_battle;
int sound_battle_magician;
int sound_battle_fairy;
int sound_battle_doragon;
//SE
int se_enter;
int se_esc;
int se_select;
int se_menu;
int se_buy;
int se_damage;
int se_sowrd;
int se_bomb;
int se_beam;
int se_warp;
int se_change;
int se_sprint;

void getSound() {
	//BGM
	sound_title = LoadSoundMem("sound/title.mp3");
	sound_play = LoadSoundMem("sound/stageselect.mp3");
	sound_shop = LoadSoundMem("sound/shop.mp3");
	sound_clear = LoadSoundMem("sound/clear.mp3");
	sound_gameover = LoadSoundMem("sound/gameover.mp3");
	sound_battle = LoadSoundMem("sound/battle.mp3");
	sound_battle_magician = LoadSoundMem("sound/vs_magician.mp3");
	sound_battle_fairy = LoadSoundMem("sound/vs_fairy.mp3");
	sound_battle_doragon = LoadSoundMem("sound/vs_doragon.mp3");
	//SE
	se_enter = LoadSoundMem("sound/enter.mp3");
	se_esc = LoadSoundMem("sound/escape.mp3");
	se_select = LoadSoundMem("sound/select.mp3");
	se_menu = LoadSoundMem("sound/openmenu.mp3");
	se_buy = LoadSoundMem("sound/coin04.mp3");
	se_damage = LoadSoundMem("sound/short_punch1.mp3");
	se_sowrd = LoadSoundMem("sound/sowrd.mp3");
	se_bomb = LoadSoundMem("sound/bomb.mp3");
	se_beam = LoadSoundMem("sound/shoot1.mp3");
	se_warp = LoadSoundMem("sound/warp1.mp3");
	se_change = LoadSoundMem("sound/poyo.mp3");
	se_sprint = LoadSoundMem("sound/sprint.mp3");
}