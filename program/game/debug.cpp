#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

extern int clear_num;
extern int item_drop_pal;

void debugGame() {
	//�X�e�[�W�N���A��(1~7)(�����l�F1)
	clear_num = 1;
	//�o���l(�����l�F0)
	player.exp_ = 0;
	//�U����(�����l�F1)
	player.atk_ = 1;
	//HP(�����l�F200)
	player.default_hp_ = 200;
	//�����h���b�v�m��(0~100)(�����l�F30)
	item_drop_pal = 30;
}