#include "../dxlib_ext/dxlib_ext.h"
#include "status.h"

//�v���C���[�X�e�[�^�X
Player player;

//�t���[�����J�E���g
int ani_frame = 20;

//�����摜
int color[3] = {0};

//�X�L���p�����[�^
Skill skill[3][3];

//�X�v�����g
int img_sprint = 0;
int sprint_cd = 0;

//�o���l�e�[�u��
int maxexp[19] = { 0 };

void getStatus() {

	//�L�����摜�ǂݍ���
	LoadDivGraph("graphics/chara/chara_red.png", 12, 3, 4, 96 / 3, 128 / 4, player.img_[RED]);
	LoadDivGraph("graphics/chara/chara_green.png", 12, 3, 4, 96 / 3, 128 / 4, player.img_[GREEN]);
	LoadDivGraph("graphics/chara/chara_blue.png", 12, 3, 4, 96 / 3, 128 / 4, player.img_[BLUE]);

	//�����摜�ǂݍ���
	color[RED] = LoadGraph("graphics/color/red.png");
	color[GREEN] = LoadGraph("graphics/color/green.png");
	color[BLUE] = LoadGraph("graphics/color/blue.png");

	//�X�v�����g�摜�ǂݍ���
	img_sprint = LoadGraph("graphics/skill/sprint.png");

	//�X�L���摜�ǂݍ���
	//�ԑ����i�A�^�b�N�j
	skill[RED][SK_Z].img_[0] = LoadGraph("graphics/skill/red02.png"); skill[RED][SK_Z].img_[1] = LoadGraph("graphics/skill/red03.png");
	skill[RED][SK_X].img_[0] = LoadGraph("graphics/skill/red12.png"); skill[RED][SK_X].img_[1] = LoadGraph("graphics/skill/red13.png");
	skill[RED][SK_C].img_[0] = LoadGraph("graphics/skill/red22.png"); skill[RED][SK_C].img_[1] = LoadGraph("graphics/skill/red23.png");
	//�Α����i�X�s�[�h�j
	skill[GREEN][SK_Z].img_[0] = LoadGraph("graphics/skill/green02.png"); skill[GREEN][SK_Z].img_[1] = LoadGraph("graphics/skill/green03.png");
	skill[GREEN][SK_X].img_[0] = LoadGraph("graphics/skill/green12.png"); skill[GREEN][SK_X].img_[1] = LoadGraph("graphics/skill/green13.png");
	skill[GREEN][SK_C].img_[0] = LoadGraph("graphics/skill/green22.png"); skill[GREEN][SK_C].img_[1] = LoadGraph("graphics/skill/green23.png");
	//�����i�o�����X�j
	skill[BLUE][SK_Z].img_[0] = LoadGraph("graphics/skill/blue02.png"); skill[BLUE][SK_Z].img_[1] = LoadGraph("graphics/skill/blue03.png");
	skill[BLUE][SK_X].img_[0] = LoadGraph("graphics/skill/blue12.png"); skill[BLUE][SK_X].img_[1] = LoadGraph("graphics/skill/blue13.png");
	skill[BLUE][SK_C].img_[0] = LoadGraph("graphics/skill/blue22.png"); skill[BLUE][SK_C].img_[1] = LoadGraph("graphics/skill/blue23.png");

	//�X�L�������p�����[�^�ݒ�
	for (int i = 0; i < 6; i++) {
		//�ԑ����i�A�^�b�N�j
		skill[RED][SK_Z].atk_[i] = 15 + (i * 3); skill[RED][SK_Z].cd_[i] = 1;
		skill[RED][SK_X].atk_[i] = 30 + (i * 6); skill[RED][SK_X].cd_[i] = 6 - ((float)i * 0.2f);
		skill[RED][SK_C].atk_[i] = 60 + (i * 12); skill[RED][SK_C].cd_[i] = 9 - ((float)i * 0.2f);
		//�Α����i�X�s�[�h�j
		skill[GREEN][SK_Z].atk_[i] = 5 + (i * 1); skill[GREEN][SK_Z].cd_[i] = 0.5;
		skill[GREEN][SK_X].atk_[i] = 10 + (i * 2); skill[GREEN][SK_X].cd_[i] = 2 - ((float)i * 0.2f);
		skill[GREEN][SK_C].atk_[i] = 20 + (i * 4); skill[GREEN][SK_C].cd_[i] = 3 - ((float)i * 0.2f);
		//�����i�o�����X�j
		skill[BLUE][SK_Z].atk_[i] = 10 + (i * 2); skill[BLUE][SK_Z].cd_[i] = 1;
		skill[BLUE][SK_X].atk_[i] = 20 + (i * 4); skill[BLUE][SK_X].cd_[i] = 4 - ((float)i * 0.2f);
		skill[BLUE][SK_C].atk_[i] = 40 + (i * 8); skill[BLUE][SK_C].cd_[i] = 6 - ((float)i * 0.2f);
	}

	//�X�L��������
	skill[RED][SK_Z].message_ = "����Z�������Ŏa��";
	skill[RED][SK_X].message_ = "���̋ʂ��΂�";
	skill[RED][SK_C].message_ = "���̌���˂��h���Ĕ���������";

	skill[GREEN][SK_Z].message_ = "���̐n�Ŏa��";
	skill[GREEN][SK_X].message_ = "���̐n���΂�";
	skill[GREEN][SK_C].message_ = "���������o���Ĕ�΂�";

	skill[BLUE][SK_Z].message_ = "��C���΂�";
	skill[BLUE][SK_X].message_ = "�n�ʂ���X�̒���˂��o��";
	skill[BLUE][SK_C].message_ = "��C��Z�����r�[�������";

	//�o���l�e�[�u���̌v�Z
	maxexp[0] = 100;
	for (int i = 1; i < 19; i++) {
		maxexp[i] = maxexp[i-1] + 10 * i;
	}
}

//�ԃ��x���A�b�v
void rlvUp() {
	//�X�L�����x���㏸
	if (player.r_lv_ < 17) {
		player.r_sp_++;
	}
	//���x��17�ȍ~�@�X�e�[�^�XUP
	else if (player.r_lv_ < 21) {
		player.atk_ += 0.05f;
	}
}

//�΃��x���A�b�v
void glvUp() {
	//�X�L�����x���㏸
	if (player.g_lv_ < 17) {
		player.g_sp_++;
	}
	//���x��17�ȍ~�@�X�e�[�^�XUP
	else if (player.g_lv_ < 21) {
		player.cd_ -= 0.025f;
	}
}

//���x���A�b�v
void blvUp() {
	//�X�L�����x���㏸
	if (player.b_lv_ < 17) {
		player.b_sp_++;
	}
	//���x��17�ȍ~�@�X�e�[�^�XUP
	else if (player.b_lv_ < 21) {
		player.cri_ += 2;
	}
}


Equip eq_date[4][10];
Equip eq_have[4][10];
Equip eq_now[4];
int eq_num[4] = {1,1,1,1};

//�����f�[�^����
void getEquipStatus() {
	eq_date[RED][0].name_ = "���̒���";
	eq_date[RED][0].atk_ = 1.1;
	eq_date[RED][0].message_ = "�ԑ����̍U���̈З͂�10%�オ��";

	eq_date[RED][1].name_ = "���̍׌�";
	eq_date[RED][1].cd_ = 0.8;
	eq_date[RED][1].message_ = "�ԑ����̍U���̃N�[���^�C����20%�Z���Ȃ�";

	eq_date[RED][2].name_ = "���̑���";
	eq_date[RED][2].cri_ = 20;
	eq_date[RED][2].message_ = "�ԑ����̍U���̃N���e�B�J������20%�オ��";

	eq_date[RED][3].name_ = "���̑匕";
	eq_date[RED][3].atk_ = 1.3;
	eq_date[RED][3].message_ = "�ԑ����̍U���̈З͂�30%�オ��";

	eq_date[GREEN][0].name_ = "���̑o��";
	eq_date[GREEN][0].atk_ = 1.1;
	eq_date[GREEN][0].message_ = "�Α����̍U���̈З͂�10%�オ��";

	eq_date[GREEN][1].name_ = "���̒Z��";
	eq_date[GREEN][1].atk_ = 1.3;
	eq_date[GREEN][1].message_ = "�Α����̍U���̈З͂�20%�オ��";

	eq_date[GREEN][2].name_ = "���̑o��";
	eq_date[GREEN][2].cri_ = 20;
	eq_date[GREEN][2].message_ = "�Α����̍U���̃N���e�B�J������20%�オ��";

	eq_date[GREEN][3].name_ = "���̑o��";
	eq_date[GREEN][3].cri_ = 30;
	eq_date[GREEN][3].message_ = "�Α����̍U���̃N���e�B�J������30%�オ��";

	eq_date[BLUE][0].name_ = "�X�̏�";
	eq_date[BLUE][0].atk_ = 1.1;
	eq_date[BLUE][0].message_ = "�����̍U���̈З͂�10%�オ��";

	eq_date[BLUE][1].name_ = "�X�̒Z��";
	eq_date[BLUE][1].cd_ = 0.8;
	eq_date[BLUE][1].message_ = "�����̍U���̃N�[���^�C����20%�Z���Ȃ�";

	eq_date[BLUE][2].name_ = "�X�̖���";
	eq_date[BLUE][2].cri_ = 20;
	eq_date[BLUE][2].message_ = "�����̍U���̃N���e�B�J������20%�オ��";

	eq_date[BLUE][3].name_ = "�X�̐���";
	eq_date[BLUE][3].atk_ = 1.2;
	eq_date[BLUE][3].cri_ = 20;
	eq_date[BLUE][3].message_ = "�����̍U���̈З͂ƃN���e�B�J������20%�オ��";

	eq_date[ARM][0].name_ = "�n�[�g�̃y���_���g";
	eq_date[ARM][0].hp_ = 20;
	eq_date[ARM][0].message_ = "�ő�HP��20���₷";

	eq_date[ARM][1].name_ = "�̘͂r��";
	eq_date[ARM][1].atk_ = 1.2;
	eq_date[ARM][1].message_ = "�^����_���[�W��20%�オ��";

	eq_date[ARM][2].name_ = "�H���̃u�[�c";
	eq_date[ARM][2].cd_ = 0.8;
	eq_date[ARM][2].message_ = "�N�[���^�C����20%�Z���Ȃ�";

	eq_date[ARM][3].name_ = "�܂̃y���_���g";
	eq_date[ARM][3].cri_ = 10;
	eq_date[ARM][3].message_ = "�N���e�B�J������10%�オ��";

	//��������
	eq_have[RED][0] = eq_date[RED][0];
	eq_have[GREEN][0] = eq_date[GREEN][0];
	eq_have[BLUE][0] = eq_date[BLUE][0];
	eq_have[ARM][0] = eq_date[ARM][0];
	
	eq_now[RED] = eq_have[RED][0];
	eq_now[GREEN] = eq_have[GREEN][0];
	eq_now[BLUE] = eq_have[BLUE][0];
	eq_now[ARM] = eq_have[ARM][0];
}

bool get_double_equ = false;

//�������菈��
void getEquipment(int TYPE,int ID) {
	//�d���`�F�b�N
	for (int i = 0; i < eq_num[TYPE]; i++) {
		if (eq_have[TYPE][i].name_ == eq_date[TYPE][ID].name_)
			get_double_equ = true;
	}
	if (!get_double_equ) {
		//�擾����
		if (eq_num[TYPE] < 10) {
			eq_have[TYPE][eq_num[TYPE]] = eq_date[TYPE][ID];
			eq_num[TYPE]++;
		}
		//�������������ς�
		else {

		}
	}
	get_double_equ = false;
}


Item item_date[2][10];
Item item_have[2][10];
int item_num[2] = { 1,1 };

//�A�C�e���f�[�^����
void getItemStatus() {
	item_date[ITEM][0].name_ = "�₭����";
	item_date[ITEM][0].message_ = "HP��20�񕜂���";
	item_date[ITEM][0].id_ = 0;
	item_date[ITEM][0].type_ = GRASS;
	item_date[ITEM][0].heal_ = 20;
	item_date[ITEM][0].buy_ = 50;
	item_date[ITEM][0].sold_ = 10;

	item_date[ITEM][1].name_ = "���₵����";
	item_date[ITEM][1].message_ = "HP��40�񕜂���";
	item_date[ITEM][1].id_ = 1;
	item_date[ITEM][1].type_ = GRASS;
	item_date[ITEM][1].heal_ = 40;
	item_date[ITEM][1].buy_ = 90;
	item_date[ITEM][1].sold_ = 18;

	item_date[ITEM][2].name_ = "�����|�[�V����";
	item_date[ITEM][2].message_ = "HP��60�񕜂���";
	item_date[ITEM][2].id_ = 2;
	item_date[ITEM][2].type_ = PORTION;
	item_date[ITEM][2].heal_ = 60;
	item_date[ITEM][2].buy_ = 130;
	item_date[ITEM][2].sold_ = 26;

	item_date[ITEM][3].name_ = "�㋉�|�[�V����";
	item_date[ITEM][3].message_ = "HP��100�񕜂���";
	item_date[ITEM][3].id_ = 3;
	item_date[ITEM][3].type_ = PORTION;
	item_date[ITEM][3].heal_ = 100;
	item_date[ITEM][3].buy_ = 220;
	item_date[ITEM][3].sold_ = 44;

	item_date[ITEM][4].name_ = "�G���N�T�[";
	item_date[ITEM][4].message_ = "HP��200�񕜂���";
	item_date[ITEM][4].id_ = 4;
	item_date[ITEM][4].type_ = PORTION;
	item_date[ITEM][4].heal_ = 200;
	item_date[ITEM][4].buy_ = 420;
	item_date[ITEM][4].sold_ = 81;

	item_date[DAIJI][0].name_ = "�Âт���";
	item_date[DAIJI][0].message_ = "�|�P�b�g�ɓ����Ă�����̌��B�ǂ��̌��Ȃ̂��͕�����Ȃ�";
	item_date[DAIJI][0].id_ = 0;
	item_date[DAIJI][0].type_ = KEY;

	//�����A�C�e��
	item_have[ITEM][0] = item_date[ITEM][0];
	item_have[ITEM][0].num_ = 3;

	item_have[DAIJI][0] = item_date[DAIJI][0];
	item_have[DAIJI][0].num_ = 1;
}

//�A�C�e�����菈��
bool get_double_item = false;

void getItem(int TYPE, int ID) {
	//�d���`�F�b�N
	for (int i = 0; i < item_num[TYPE]; i++) {
		if (item_have[TYPE][i].name_ == item_date[TYPE][ID].name_) {
			item_have[TYPE][i].num_++;
			get_double_item = true;
		}
	}
	if (!get_double_item) {
		//�擾����
		item_have[TYPE][item_num[TYPE]] = item_date[TYPE][ID];
		item_have[TYPE][item_num[TYPE]].num_ = 1;
		item_num[TYPE]++;
	}
	get_double_item = false;
}