#pragma once
#include "../dxlib_ext/dxlib_ext.h"

//�����̒l
const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;
const int ARM = 3;

//�X�L���l
const int SK_Z = 0;
const int SK_X = 1;
const int SK_C = 2;

//�����摜
extern int color[3];

//�X�v�����g�摜
extern int img_sprint;
extern int sprint_cd;

//�v���C���[�̌���
const int LEFT = 0;
const int RIGHT = 1;

//�v���C���[�X�e�[�^�X
class Player {
public:
	int default_hp_ = 200;
	int mhp_ = default_hp_;
	int hp_ = mhp_;
	float atk_ = 1;
	float cd_ = 1;
	int cri_ = 10;
	float color_atk_[3] = {0};
	float color_cd_[3] = {0};
	int color_cri_[3] = {0};
	int exp_ = 0;
	int pos_x_ = 300;
	int pos_y_ = 300;
	int img_[3][12] = {0};
	int battle_ani_ = 8;
	int mode_ = RED;
	int r_lv_ = 1;
	int g_lv_ = 1;
	int b_lv_ = 1;
	int r_sp_ = 0;
	int g_sp_ = 0;
	int b_sp_ = 0;
	int dir_ = RIGHT;
};

//�t���[�����J�E���g
extern int ani_frame;

//�X�L���p�����[�^
class Skill {
public:
	int slv_ = 0;
	int atk_[6] = {0};
	float cd_[6] = {0};
	int img_[2] = {0};
	std::string message_;
};

extern Skill skill[3][3];

//�o���l�e�[�u��
extern int maxexp[19];

extern Player player;

//����
class Equip {
public:
	std::string name_;
	float atk_ = 1;
	float cd_ = 1;
	int cri_ = 1;
	int hp_ = 0;
	std::string message_;
};

//�����f�[�^
extern Equip eq_date[4][10];
//����
extern Equip eq_have[4][10];
//������
extern Equip eq_now[4];
//��
extern int eq_num[4];

//�A�C�e��
const int ITEM = 0;
const int DAIJI = 1;

const int GRASS = 0;
const int PORTION = 1;
const int KEY = 2;

class Item {
public:
	std::string name_;
	std::string message_;
	int id_ = 0;
	int type_ = 0;
	int num_ = 0;
	int heal_ = 0;
	int buy_ = 0;
	int sold_ = 0;
};

extern Item item_date[2][10];
extern Item item_have[2][10];
extern int item_num[2];


//�G�X�e�[�^�X
class Enemy {
public:
	enum {
		BLUESLIME,
		REDSLIME,
		REDBIRD,
		GREENBIRD,
		BLUEBIRD,
		REDMAGICIAN,
		GREENMAGICIAN,
		BLUEMAGICIAN,
		GREENFAIRY,
		BLUEFAIRY,
		DRAGON
	};

	void initialize(int type);

	std::string name_;
	int id_;
	int mhp_;
	int hp_;
	int color_;
	//���a
	int r_;
	//�ʒu
	int pos_x_ = 600;
	int pos_y_ = 600;
	//���� false�F�� true�F�E
	bool dir_ = false;
	//���
	int move_ = 0;
	int frame_ = 0;
	//�A�j���[�V�����̃t���[�������i�[
	int ani_size_[3];
	//�����E�A�j���[�V����
	int img_[3][10];
};

extern Enemy enemy[11];
extern Enemy battle_enemy[3];

const int ENEMY_STOP = 0;
const int ENEMY_MOVE = 1;
const int ENEMY_ATACK = 2;
const int ENEMY_DAMAGE = 3;
const int ENEMY_DEATH = 4;

const bool ENEMY_LEFT = false;
const bool ENEMY_RIGHT = true;

extern int stage;
extern int enemy_num[7];
extern int enemy_damage_count[3];
extern int enemy_damage[3];