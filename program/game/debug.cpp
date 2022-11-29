#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

extern int clear_num;
extern int item_drop_pal;

void debugGame() {
	//ステージクリア状況(1~7)(初期値：1)
	clear_num = 1;
	//経験値(初期値：0)
	player.exp_ = 0;
	//攻撃力(初期値：1)
	player.atk_ = 1;
	//HP(初期値：200)
	player.default_hp_ = 200;
	//装備ドロップ確立(0~100)(初期値：30)
	item_drop_pal = 30;
}