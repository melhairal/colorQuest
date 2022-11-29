#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

//�v���g�^�C�v�錾
void playerDamage(int damage,int enemy_color);

//�G�̃f�[�^��ێ�
Enemy enemy[11];
int img_dragon[3][3][10];

//�G�p�����[�^��csv�ǂݍ���
void Enemy::initialize(int type) {
	auto tbl = tnl::LoadCsv("csv/enemy.csv");
	name_ = tbl[type+1][0];

	id_ = std::atoi(tbl[type+1][1].c_str());
	hp_ = std::atoi(tbl[type+1][2].c_str());
	mhp_ = hp_;
	color_ = std::atoi(tbl[type+1][3].c_str());
	r_ = std::atoi(tbl[type + 1][4].c_str());
}

//�A�j���[�V�����摜�擾
void enemyImg() {
	//�u���[�X���C��
	enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/�X���C��A_�ҋ@000.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/�X���C��A_�ҋ@001.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/�X���C��A_�ҋ@002.png");
	enemy[Enemy::BLUESLIME].ani_size_[ENEMY_STOP] = 3;
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�X���C��A_�ړ�000.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�X���C��A_�ړ�001.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�X���C��A_�ړ�002.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�X���C��A_�ړ�003.png");
	enemy[Enemy::BLUESLIME].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�X���C��A_�U��000.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�X���C��A_�U��001.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�X���C��A_�U��002.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�X���C��A_�U��003.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][4] = LoadGraph("graphics/enemy/�X���C��A_�U��004.png");
	enemy[Enemy::BLUESLIME].ani_size_[ENEMY_ATACK] = 5;

	//���b�h�X���C��
	enemy[Enemy::REDSLIME].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/�X���C��B_�ҋ@000.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/�X���C��B_�ҋ@001.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/�X���C��B_�ҋ@002.png");
	enemy[Enemy::REDSLIME].ani_size_[ENEMY_STOP] = 3;
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�X���C��B_�ړ�000.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�X���C��B_�ړ�001.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�X���C��B_�ړ�002.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�X���C��B_�ړ�003.png");
	enemy[Enemy::REDSLIME].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�X���C��B_�U��000.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�X���C��B_�U��001.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�X���C��B_�U��002.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�X���C��B_�U��003.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][4] = LoadGraph("graphics/enemy/�X���C��B_�U��004.png");
	enemy[Enemy::REDSLIME].ani_size_[ENEMY_ATACK] = 5;

	//���b�h�o�[�h
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/��B_�ҋ@000.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/��B_�ҋ@001.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/��B_�ҋ@002.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/��B_�ҋ@003.png");
	enemy[Enemy::REDBIRD].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/��B_�ړ�000.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/��B_�ړ�001.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/��B_�ړ�002.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/��B_�ړ�003.png");
	enemy[Enemy::REDBIRD].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/��B_�U��000.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/��B_�U��001.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/��B_�U��002.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/��B_�U��003.png");
	enemy[Enemy::REDBIRD].ani_size_[ENEMY_ATACK] = 4;

	//�O���[���o�[�h
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/��C_�ҋ@000.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/��C_�ҋ@001.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/��C_�ҋ@002.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/��C_�ҋ@003.png");
	enemy[Enemy::GREENBIRD].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/��C_�ړ�000.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/��C_�ړ�001.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/��C_�ړ�002.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/��C_�ړ�003.png");
	enemy[Enemy::GREENBIRD].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/��C_�U��000.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/��C_�U��001.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/��C_�U��002.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/��C_�U��003.png");
	enemy[Enemy::GREENBIRD].ani_size_[ENEMY_ATACK] = 4;

	//�u���[�o�[�h
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/��D_�ҋ@000.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/��D_�ҋ@001.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/��D_�ҋ@002.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/��D_�ҋ@003.png");
	enemy[Enemy::BLUEBIRD].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/��D_�ړ�000.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/��D_�ړ�001.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/��D_�ړ�002.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/��D_�ړ�003.png");
	enemy[Enemy::BLUEBIRD].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/��D_�U��000.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/��D_�U��001.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/��D_�U��002.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/��D_�U��003.png");
	enemy[Enemy::BLUEBIRD].ani_size_[ENEMY_ATACK] = 4;

	//���b�h�}�W�V����
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/���@�g��A_�ҋ@000.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/���@�g��A_�ҋ@001.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/���@�g��A_�ҋ@002.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/���@�g��A_�ҋ@003.png");
	enemy[Enemy::REDMAGICIAN].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/���@�g��A_�ړ�000.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/���@�g��A_�ړ�001.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/���@�g��A_�ړ�002.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/���@�g��A_�ړ�003.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/���@�g��A_�ړ�004.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/���@�g��A_�ړ�005.png");
	enemy[Enemy::REDMAGICIAN].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/���@�g��A_�U��000.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/���@�g��A_�U��001.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/���@�g��A_�U��002.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/���@�g��A_�U��003.png");
	enemy[Enemy::REDMAGICIAN].ani_size_[ENEMY_ATACK] = 4;

	//�O���[���}�W�V����
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/���@�g��D_�ҋ@000.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/���@�g��D_�ҋ@001.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/���@�g��D_�ҋ@002.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/���@�g��D_�ҋ@003.png");
	enemy[Enemy::GREENMAGICIAN].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/���@�g��D_�ړ�000.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/���@�g��D_�ړ�001.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/���@�g��D_�ړ�002.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/���@�g��D_�ړ�003.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/���@�g��D_�ړ�004.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/���@�g��D_�ړ�005.png");
	enemy[Enemy::GREENMAGICIAN].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/���@�g��D_�U��000.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/���@�g��D_�U��001.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/���@�g��D_�U��002.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/���@�g��D_�U��003.png");
	enemy[Enemy::GREENMAGICIAN].ani_size_[ENEMY_ATACK] = 4;

	//�u���[�}�W�V����
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/���@�g��B_�ҋ@000.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/���@�g��B_�ҋ@001.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/���@�g��B_�ҋ@002.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/���@�g��B_�ҋ@003.png");
	enemy[Enemy::BLUEMAGICIAN].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/���@�g��B_�ړ�000.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/���@�g��B_�ړ�001.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/���@�g��B_�ړ�002.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/���@�g��B_�ړ�003.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/���@�g��B_�ړ�004.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/���@�g��B_�ړ�005.png");
	enemy[Enemy::BLUEMAGICIAN].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/���@�g��B_�U��000.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/���@�g��B_�U��001.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/���@�g��B_�U��002.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/���@�g��B_�U��003.png");
	enemy[Enemy::BLUEMAGICIAN].ani_size_[ENEMY_ATACK] = 4;

	//�O���[���t�F�A���[
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/�d��A_�ҋ@000.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/�d��A_�ҋ@001.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/�d��A_�ҋ@002.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/�d��A_�ҋ@003.png");
	enemy[Enemy::GREENFAIRY].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�d��A_�ړ�000.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�d��A_�ړ�001.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�d��A_�ړ�002.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�d��A_�ړ�003.png");
	enemy[Enemy::GREENFAIRY].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�d��A_�U��000.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�d��A_�U��001.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�d��A_�U��002.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�d��A_�U��003.png");
	enemy[Enemy::GREENFAIRY].ani_size_[ENEMY_ATACK] = 4;

	//�u���[�t�F�A���[
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/�d��B_�ҋ@000.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/�d��B_�ҋ@001.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/�d��B_�ҋ@002.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/�d��B_�ҋ@003.png");
	enemy[Enemy::BLUEFAIRY].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�d��B_�ړ�000.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�d��B_�ړ�001.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�d��B_�ړ�002.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�d��B_�ړ�003.png");
	enemy[Enemy::BLUEFAIRY].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�d��B_�U��000.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�d��B_�U��001.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�d��B_�U��002.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�d��B_�U��003.png");
	enemy[Enemy::BLUEFAIRY].ani_size_[ENEMY_ATACK] = 4;

	//�h���S��
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@000.png");
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@001.png");
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@002.png");
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@003.png");
	enemy[Enemy::DRAGON].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�h���S��A_�ړ�000.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�h���S��A_�ړ�001.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�h���S��A_�ړ�002.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�h���S��A_�ړ�003.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/�h���S��A_�ړ�004.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/�h���S��A_�ړ�005.png");
	enemy[Enemy::DRAGON].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�h���S��A_�U��000.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�h���S��A_�U��001.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�h���S��A_�U��002.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�h���S��A_�U��003.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][4] = LoadGraph("graphics/enemy/�h���S��A_�U��004.png");
	enemy[Enemy::DRAGON].ani_size_[ENEMY_ATACK] = 5;
	//�ԃh���S��
	img_dragon[RED][ENEMY_STOP][0] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@000.png");
	img_dragon[RED][ENEMY_STOP][1] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@001.png");
	img_dragon[RED][ENEMY_STOP][2] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@002.png");
	img_dragon[RED][ENEMY_STOP][3] = LoadGraph("graphics/enemy/�h���S��A_�ҋ@003.png");
	
	img_dragon[RED][ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�h���S��A_�ړ�000.png");
	img_dragon[RED][ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�h���S��A_�ړ�001.png");
	img_dragon[RED][ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�h���S��A_�ړ�002.png");
	img_dragon[RED][ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�h���S��A_�ړ�003.png");
	img_dragon[RED][ENEMY_MOVE][4] = LoadGraph("graphics/enemy/�h���S��A_�ړ�004.png");
	img_dragon[RED][ENEMY_MOVE][5] = LoadGraph("graphics/enemy/�h���S��A_�ړ�005.png");

	img_dragon[RED][ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�h���S��A_�U��000.png");
	img_dragon[RED][ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�h���S��A_�U��001.png");
	img_dragon[RED][ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�h���S��A_�U��002.png");
	img_dragon[RED][ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�h���S��A_�U��003.png");
	img_dragon[RED][ENEMY_ATACK][4] = LoadGraph("graphics/enemy/�h���S��A_�U��004.png");
	//�΃h���S��
	img_dragon[GREEN][ENEMY_STOP][0] = LoadGraph("graphics/enemy/�h���S��C_�ҋ@000.png");
	img_dragon[GREEN][ENEMY_STOP][1] = LoadGraph("graphics/enemy/�h���S��C_�ҋ@001.png");
	img_dragon[GREEN][ENEMY_STOP][2] = LoadGraph("graphics/enemy/�h���S��C_�ҋ@002.png");
	img_dragon[GREEN][ENEMY_STOP][3] = LoadGraph("graphics/enemy/�h���S��C_�ҋ@003.png");

	img_dragon[GREEN][ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�h���S��C_�ړ�000.png");
	img_dragon[GREEN][ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�h���S��C_�ړ�001.png");
	img_dragon[GREEN][ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�h���S��C_�ړ�002.png");
	img_dragon[GREEN][ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�h���S��C_�ړ�003.png");
	img_dragon[GREEN][ENEMY_MOVE][4] = LoadGraph("graphics/enemy/�h���S��C_�ړ�004.png");
	img_dragon[GREEN][ENEMY_MOVE][5] = LoadGraph("graphics/enemy/�h���S��C_�ړ�005.png");

	img_dragon[GREEN][ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�h���S��C_�U��000.png");
	img_dragon[GREEN][ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�h���S��C_�U��001.png");
	img_dragon[GREEN][ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�h���S��C_�U��002.png");
	img_dragon[GREEN][ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�h���S��C_�U��003.png");
	img_dragon[GREEN][ENEMY_ATACK][4] = LoadGraph("graphics/enemy/�h���S��C_�U��004.png");
	//�h���S��
	img_dragon[BLUE][ENEMY_STOP][0] = LoadGraph("graphics/enemy/�h���S��B_�ҋ@000.png");
	img_dragon[BLUE][ENEMY_STOP][1] = LoadGraph("graphics/enemy/�h���S��B_�ҋ@001.png");
	img_dragon[BLUE][ENEMY_STOP][2] = LoadGraph("graphics/enemy/�h���S��B_�ҋ@002.png");
	img_dragon[BLUE][ENEMY_STOP][3] = LoadGraph("graphics/enemy/�h���S��B_�ҋ@003.png");

	img_dragon[BLUE][ENEMY_MOVE][0] = LoadGraph("graphics/enemy/�h���S��B_�ړ�000.png");
	img_dragon[BLUE][ENEMY_MOVE][1] = LoadGraph("graphics/enemy/�h���S��B_�ړ�001.png");
	img_dragon[BLUE][ENEMY_MOVE][2] = LoadGraph("graphics/enemy/�h���S��B_�ړ�002.png");
	img_dragon[BLUE][ENEMY_MOVE][3] = LoadGraph("graphics/enemy/�h���S��B_�ړ�003.png");
	img_dragon[BLUE][ENEMY_MOVE][4] = LoadGraph("graphics/enemy/�h���S��B_�ړ�004.png");
	img_dragon[BLUE][ENEMY_MOVE][5] = LoadGraph("graphics/enemy/�h���S��B_�ړ�005.png");

	img_dragon[BLUE][ENEMY_ATACK][0] = LoadGraph("graphics/enemy/�h���S��B_�U��000.png");
	img_dragon[BLUE][ENEMY_ATACK][1] = LoadGraph("graphics/enemy/�h���S��B_�U��001.png");
	img_dragon[BLUE][ENEMY_ATACK][2] = LoadGraph("graphics/enemy/�h���S��B_�U��002.png");
	img_dragon[BLUE][ENEMY_ATACK][3] = LoadGraph("graphics/enemy/�h���S��B_�U��003.png");
	img_dragon[BLUE][ENEMY_ATACK][4] = LoadGraph("graphics/enemy/�h���S��B_�U��004.png");
}

Enemy battle_enemy[3];
int enemy_timer[3] = { 0,0,0 };
int enemy_ani[3] = { 0,0,0 };
int enemy_speed_x[3] = { 0,0,0 };
int enemy_speed_y[3] = { 0,0,0 };
int enemy_random[3] = { 0,0,0 };
int enemy_trigger[3] = { 0,0,0 };

//�G�_���[�W����
int enemy_damage_random = 0;
int enemy_damage_cri = 0;
bool damage_cri[3] = { false,false,false };
//�G�_���[�W�\�L
int enemy_damage_count[3] = { 0,0,0 };
int enemy_damage[3] = { 0,0,0 };

void enemyDamage(int id, int MODE, int SKILL) {
	PlaySoundMem(se_damage, DX_PLAYTYPE_BACK);
	//�_���[�W���󂯂��Ƃ��̓��쏈�������s
	if (stage != 7) {
		battle_enemy[id].move_ = ENEMY_DAMAGE;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
	}
	//�_���[�W�v�Z
	enemy_damage[id] = skill[MODE][SKILL].atk_[skill[MODE][SKILL].slv_] * player.color_atk_[MODE];
	enemy_damage_random = rand() % (enemy_damage[id] / 5);
	enemy_damage[id] += enemy_damage_random;
	//�N���e�B�J��
	enemy_damage_cri = rand() % 100;
	if (player.color_cri_[MODE] > enemy_damage_cri) {
		enemy_damage[id] = enemy_damage[id] * 1.5;
		damage_cri[id] = true;
	}
	//���������v�Z
	if (MODE == battle_enemy[id].color_ - 1 || MODE == battle_enemy[id].color_ + 2) {
		enemy_damage[id] = enemy_damage[id] * 2;
	}
	else if (MODE == battle_enemy[id].color_ + 1 || MODE == battle_enemy[id].color_ - 2) {
		enemy_damage[id] = enemy_damage[id] / 2;
	}
	//HP���炷����
	battle_enemy[id].hp_ -= enemy_damage[id];
	enemy_damage_count[id] = 40;
}

//�GAI
//�X���C��
void aiSlime(int id) {
	//y=600
	//�v���C���[�̕�������
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//�A�j���[�V����
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//���ԃJ�E���g
	//���1��
	if(enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//�G�ꂽ��_���[�W
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 20 && battle_enemy[id].pos_x_ < player.pos_x_ + 20
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 20 && battle_enemy[id].pos_y_ < player.pos_y_ + 20) {
		playerDamage(15, battle_enemy[id].color_);
	}

	//��Ԗ��̓���
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//1�b�~�܂�
		if (enemy_timer[id] == 60) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_MOVE:
		//�ړ��X�s�[�h�̐ݒ�
		enemy_speed_x[id] = 1;
		//�����_���Ń_�b�V������
		enemy_random[id] = rand() % 600;
		if (enemy_random[id] == 0) {
			//3�b
			enemy_trigger[id] = 3 * 60;
		}
		if (enemy_trigger[id] != 0) {
			enemy_trigger[id]--;
			enemy_speed_x[id] = 2;
		}
		//�v���C���[�ɋ߂Â��܂œ���
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			break;
		}
		//�v���C���[�ɋ߂Â�����U���Ɉڍs
		if (battle_enemy[id].pos_x_ > player.pos_x_ - 55 && battle_enemy[id].pos_x_ < player.pos_x_ + 55
			&& battle_enemy[id].pos_y_ > player.pos_y_ - 55 && battle_enemy[id].pos_y_ < player.pos_y_ + 55) {
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_ATACK:
		//�U������̃^�C�~���O�Ńv���C���[�Ƀ_���[�W��^����
		if (enemy_timer[id] == 20) {
			PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
			if (battle_enemy[id].pos_x_ > player.pos_x_ - 55 && battle_enemy[id].pos_x_ < player.pos_x_ + 55
				&& battle_enemy[id].pos_y_ > player.pos_y_ - 55 && battle_enemy[id].pos_y_ < player.pos_y_ + 55) {
				switch (battle_enemy[id].id_) {
				case Enemy::BLUESLIME:
					playerDamage(25, battle_enemy[id].color_);
					break;
				case Enemy::REDSLIME:
					playerDamage(35, battle_enemy[id].color_);
					break;
				}
			}
		}
		//�U�����[�V�������I��������~�ɖ߂�
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//�_���[�W���󂯂��Ƃ��̓���
		//�̂�����
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10�t���[����Ɉړ���Ԃɖ߂�
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HP��0��������Ă��玀�S����
			else if (battle_enemy[id].hp_ <= 0) {
				battle_enemy[id].pos_x_ = -1;
				battle_enemy[id].pos_y_ = -1;
				battle_enemy[id].move_ = ENEMY_DEATH;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
		}
		break;
	case ENEMY_DEATH:
		//���S����
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//��ʊO�ɂ����Ȃ�����
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
}

//��
bool bird_damage_rock[3];
void aiBird(int id) {
	//y=400~500
	//�A�j���[�V����
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//���ԃJ�E���g
	//���1��
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//�G�ꂽ��_���[�W
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 40 && battle_enemy[id].pos_x_ < player.pos_x_ + 40
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 40 && battle_enemy[id].pos_y_ < player.pos_y_ + 40) {
		if (!bird_damage_rock[id]) {
			playerDamage(35, battle_enemy[id].color_);
			bird_damage_rock[id] = true;
		}
	}
	//��Ԗ��̓���
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//�v���C���[�̕�������
		battle_enemy[id].dir_ = ENEMY_LEFT;
		if (battle_enemy[id].pos_x_ < player.pos_x_)
			battle_enemy[id].dir_ = ENEMY_RIGHT;
		//�΋󂷂鍂�������߂�
		if (enemy_timer[id] == 1) {
			enemy_random[id] = rand() % 3;
			enemy_speed_y[id] = (battle_enemy[id].pos_y_ - (400 + 50 * enemy_random[id])) / 60;
		}
		//���܂��������ɖ߂�
		battle_enemy[id].pos_y_ -= enemy_speed_y[id];
		//1�b�~�܂�
		if (enemy_timer[id] == 60) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		bird_damage_rock[id] = false;
		break;
	case ENEMY_MOVE:
		//�v���C���[�̕�������
		battle_enemy[id].dir_ = ENEMY_LEFT;
		if (battle_enemy[id].pos_x_ < player.pos_x_)
			battle_enemy[id].dir_ = ENEMY_RIGHT;
		//�ړ��X�s�[�h�̐ݒ�
		enemy_speed_x[id] = 2;
		//�����_���Ń_�b�V������
		enemy_random[id] = rand() % 600;
		if (enemy_random[id] == 0) {
			//3�b
			enemy_trigger[id] = 3 * 60;
		}
		if (enemy_trigger[id] != 0) {
			enemy_trigger[id]--;
			enemy_speed_x[id] = 3;
		}
		//�v���C���[�ɋ߂Â��܂œ���
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			break;
		}
		//�v���C���[�ɋ߂Â�����U���Ɉڍs
		if (battle_enemy[id].pos_x_ > player.pos_x_ - 200 && battle_enemy[id].pos_x_ < player.pos_x_ + 200) {
			PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		bird_damage_rock[id] = false;
		break;
	case ENEMY_ATACK:
		//�v���C���[�̍��W���L������
		if (enemy_timer[id] == 1) {
			enemy_speed_x[id] = (battle_enemy[id].pos_x_ - player.pos_x_) / 30;
			enemy_speed_y[id] = (battle_enemy[id].pos_y_ - (player.pos_y_ + 40)) / 30;
		}
		//�ˌ�
		if (enemy_timer[id] < 30) {
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			battle_enemy[id].pos_y_ -= enemy_speed_y[id];
		}
		else if (enemy_timer[id] < 35) {
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
		}
		else if (enemy_timer[id] < 65) {
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			battle_enemy[id].pos_y_ += enemy_speed_y[id];
		}
		//�U�����[�V�������I��������~�ɖ߂�
		if (enemy_timer[id] == 65) {
			bird_damage_rock[id] = false;
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//�_���[�W���󂯂��Ƃ��̓���
		//�̂�����
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10�t���[����Ɉړ���Ԃɖ߂�
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HP��0��������Ă��玀�S����
			else if (battle_enemy[id].hp_ <= 0) {
				battle_enemy[id].pos_x_ = -1;
				battle_enemy[id].pos_y_ = -1;
				battle_enemy[id].move_ = ENEMY_DEATH;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
		}
		break;
	case ENEMY_DEATH:
		//���S����
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//��ʊO�ɂ����Ȃ�����
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
}

//�}�W�V����
bool magician_red_attack[3];
bool magician_green_attack[3];
bool magician_blue_attack[3];
extern int skill_ani[3][3][2][50];
int magician_skill_x[3];
int magician_skill_y[3];
int magician_skill_dir[3];
int magician_skill_frame[3] = {0,0,0};
//�e���|�[�g�G�t�F�N�g
bool init_magician = false;
int magician_terepo_ani[10];
int magician_terepo_frame = 0;

void aiMagician(int id) {
	//y=560
	if (!init_magician) {
		LoadDivGraph("graphics/ani/terepo.png", 10, 10, 1, 120, 120, magician_terepo_ani);
		init_magician = true;
	}
	//�v���C���[�̕�������
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//�A�j���[�V����
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//���ԃJ�E���g
	//���1��
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;

	//��Ԗ��̓���
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//�����_���ŗ����
		enemy_speed_x[id] = 0;
		if (enemy_timer[id] == 1) {
			enemy_random[id] = rand() % 4;
		}
		if (enemy_random[id] == 0) {
			enemy_speed_x[id] = 5;
		}
		if (enemy_timer[id] > 15) {
			enemy_speed_x[id] = 0;
		}
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			break;
		}
		//�����_���Ńv���C���[�̔��΂Ƀe���|�[�g����
		if (enemy_random[id] == 2 && enemy_timer[id] > 30) {
			if (enemy_timer[id] == 31) {
				PlaySoundMem(se_warp, DX_PLAYTYPE_BACK);
			}
			if (enemy_timer[id] < 70) {
				DrawRotaGraph(battle_enemy[id].pos_x_, battle_enemy[id].pos_y_ + 20, 1, 0, magician_terepo_ani[magician_terepo_frame], true);
			}
			if ((enemy_ani[id] == 0 || enemy_ani[id] == 5) && magician_terepo_frame < 9) {
				magician_terepo_frame++;
			}
			if (enemy_timer[id] == 60) {
				battle_enemy[id].pos_x_ = player.pos_x_ - (battle_enemy[id].pos_x_ - player.pos_x_);
			}
		}
		//2�b�~�܂�
		if (enemy_timer[id] == 180) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
			magician_terepo_frame = 0;
		}
		break;
	case ENEMY_MOVE:
		//�ړ��X�s�[�h�̐ݒ�
		enemy_speed_x[id] = 1;
		//�����_���Ń_�b�V������
		enemy_random[id] = rand() % 600;
		if (enemy_random[id] == 0) {
			//3�b
			enemy_trigger[id] = 3 * 60;
		}
		if (enemy_trigger[id] != 0) {
			enemy_trigger[id]--;
			enemy_speed_x[id] = 2;
		}
		//�v���C���[�ɋ߂Â��܂œ���
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			break;
		}
		//�v���C���[�ɋ߂Â�����U���Ɉڍs
		if (battle_enemy[id].pos_x_ > player.pos_x_ - 400 && battle_enemy[id].pos_x_ < player.pos_x_ + 400) {
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_ATACK:
		//�U������̃^�C�~���O�Ńv���C���[�Ƀ_���[�W��^����
		if (enemy_timer[id] == 10) {
			PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
			switch (battle_enemy[id].id_) {
			case Enemy::REDMAGICIAN:
				magician_red_attack[id] = true;
				break;
			case Enemy::GREENMAGICIAN:
				magician_green_attack[id] = true;
				break;
			case Enemy::BLUEMAGICIAN:
				magician_blue_attack[id] = true;
				break;
			}
		}
		//�U�����[�V�������I��������~�ɖ߂�
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//�_���[�W���󂯂��Ƃ��̓���
		//�̂�����
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10�t���[����Ɉړ���Ԃɖ߂�
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HP��0��������Ă��玀�S����
			else if (battle_enemy[id].hp_ <= 0) {
				battle_enemy[id].pos_x_ = -1;
				battle_enemy[id].pos_y_ = -1;
				battle_enemy[id].move_ = ENEMY_DEATH;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
		}
		break;
	case ENEMY_DEATH:
		//���S����
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//��ʊO�ɂ����Ȃ�����
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
	//�U�����@����
	//��
	if (magician_red_attack[id] == true) {
		if (magician_skill_frame[id] == 0) {
			switch (battle_enemy[id].dir_)
			{
			case ENEMY_LEFT:
				magician_skill_x[id] = battle_enemy[id].pos_x_ - 10;
				magician_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				magician_skill_dir[id] = LEFT;
				break;
			case ENEMY_RIGHT:
				magician_skill_x[id] = battle_enemy[id].pos_x_ + 10;
				magician_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				magician_skill_dir[id] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(magician_skill_x[id], magician_skill_y[id], 1, 0, skill_ani[RED][SK_X][0][magician_skill_frame[id]], true);
		switch (magician_skill_dir[id])
		{
		case LEFT:
			magician_skill_x[id] -= 8;
			break;
		case RIGHT:
			magician_skill_x[id] += 8;
		}
		if (enemy_ani[id] == 0 || enemy_ani[id] == 5) {
			magician_skill_frame[id]++;
		}

		if (magician_skill_frame[id] > 20) {
			magician_skill_frame[id] = 0;
			magician_red_attack[id] = false;
		}
		//�_���[�W����
		if (magician_skill_x[id] - 60 < player.pos_x_ && magician_skill_x[id] + 60 > player.pos_x_
			&& magician_skill_y[id] - 60 < player.pos_y_ && magician_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(25, battle_enemy[id].color_);
			magician_red_attack[id] = false;
			magician_skill_frame[id] = 0;
		}
	}
	//��
	if (magician_green_attack[id] == true) {
		if (magician_skill_frame[id] == 0) {
			switch (battle_enemy[id].dir_)
			{
			case ENEMY_LEFT:
				magician_skill_x[id] = battle_enemy[id].pos_x_ - 30;
				magician_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				magician_skill_dir[id] = LEFT;
				break;
			case ENEMY_RIGHT:
				magician_skill_x[id] = battle_enemy[id].pos_x_ + 30;
				magician_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				magician_skill_dir[id] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(magician_skill_x[id], magician_skill_y[id], 1, 0, skill_ani[GREEN][SK_X][0][magician_skill_frame[id]], true);
		switch (magician_skill_dir[id])
		{
		case LEFT:
			magician_skill_x[id] -= 15;
			break;
		case RIGHT:
			magician_skill_x[id] += 15;
		}
		if (enemy_ani[id] == 0 || enemy_ani[id] == 5) {
			magician_skill_frame[id]++;
		}

		if (magician_skill_frame[id] > 15) {
			magician_skill_frame[id] = 0;
			magician_green_attack[id] = false;
		}
		//�_���[�W����
		if (magician_skill_x[id] - 60 < player.pos_x_ && magician_skill_x[id] + 60 > player.pos_x_
			&& magician_skill_y[id] - 60 < player.pos_y_ && magician_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(15, battle_enemy[id].color_);
			magician_green_attack[id] = false;
			magician_skill_frame[id] = 0;
		}
	}
	//��
	if (magician_blue_attack[id] == true) {
		if (magician_skill_frame[id] == 0) {
			switch (battle_enemy[id].dir_)
			{
			case ENEMY_LEFT:
				magician_skill_x[id] = battle_enemy[id].pos_x_ - 20;
				magician_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				magician_skill_dir[id] = LEFT;
				break;
			case ENEMY_RIGHT:
				magician_skill_x[id] = battle_enemy[id].pos_x_ + 20;
				magician_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				magician_skill_dir[id] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(magician_skill_x[id], magician_skill_y[id], 1, 0, skill_ani[BLUE][SK_Z][0][magician_skill_frame[id]], true);
		switch (magician_skill_dir[id])
		{
		case LEFT:
			magician_skill_x[id] -= 12;
			break;
		case RIGHT:
			magician_skill_x[id] += 12;
		}
		if (enemy_ani[id] == 0 || enemy_ani[id] == 5) {
			magician_skill_frame[id]++;
		}
		if (magician_skill_frame[id] > 8) {
			magician_skill_frame[id] = 0;
			magician_blue_attack[id] = false;
		}
		//�_���[�W����
		if (magician_skill_x[id] - 60 < player.pos_x_ && magician_skill_x[id] + 60 > player.pos_x_
			&& magician_skill_y[id] - 60 < player.pos_y_ && magician_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(20, battle_enemy[id].color_);
			magician_blue_attack[id] = false;
			magician_skill_frame[id] = 0;
		}
	}
}

//�d��
bool fairy_green_attack[2][3];
bool fairy_blue_attack[2][3];
int fairy_skill_x[3];
int fairy_skill_y[3];
int fairy_skill_dir[3];
int fairy_skill_frame[3] = { 0,0,0 };
int fairy_skill_speed_x[3];
int fairy_skill_speed_y[3];
bool fairy_skill_rock[3];

void aiFairy(int id) {
	//y=400~500
	//�v���C���[�̕�������
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//�A�j���[�V����
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//���ԃJ�E���g
	//���1��
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//�G�ꂽ��_���[�W
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 20 && battle_enemy[id].pos_x_ < player.pos_x_ + 20
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 20 && battle_enemy[id].pos_y_ < player.pos_y_ + 20) {
		playerDamage(15, battle_enemy[id].color_);
	}

	//��Ԗ��̓���
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//2�b�~�܂�
		enemy_speed_x[id] = 0;
		if (enemy_timer[id] == 120) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_MOVE:
		//�����_������F�s��3�p�^�[���i���̏�A�����A��荞�ށj
		if (enemy_timer[id] == 1) {
			//�s������
			enemy_random[id] = rand() % 3;
			switch (enemy_random[id]) {
			case 0:
				//���̏�
				enemy_speed_x[id] = 0;
				break;
			case 1:
				//�����
				if (battle_enemy[id].dir_ == ENEMY_LEFT) {
					enemy_speed_x[id] = 3;
				}
				else if (battle_enemy[id].dir_ == ENEMY_RIGHT) {
					enemy_speed_x[id] = -3;
				}
				break;
			case 2:
				//��荞��
				if (battle_enemy[id].dir_ == ENEMY_LEFT) {
					enemy_speed_x[id] = ((player.pos_x_ - 200) - battle_enemy[id].pos_x_) / 60;
				}
				else if (battle_enemy[id].dir_ == ENEMY_RIGHT) {
					enemy_speed_x[id] = ((player.pos_x_ + 200) - battle_enemy[id].pos_x_) / 60;
				}
	/*			enemy_speed_x[id] = ((player.pos_x_ - battle_enemy[id].pos_x_) * 2) / 60;*/
				break;
			}
			//��������
			enemy_random[id] = rand() % 4;
			switch (enemy_random[id]) {
			case 0:
			case 1:
			case 2:
				enemy_speed_y[id] = (battle_enemy[id].pos_y_ - (330 + 70 * enemy_random[id])) / 60;
				break;
			case 3:
				enemy_speed_y[id] = (battle_enemy[id].pos_y_ - 600) / 60;
				break;
			}
		}
		battle_enemy[id].pos_x_ += enemy_speed_x[id];
		battle_enemy[id].pos_y_ -= enemy_speed_y[id];
		if (enemy_timer[id] == 61) {
			//�ړ��������U���Ɉڂ�
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_ATACK:
		//�U������̃^�C�~���O�Ńv���C���[�Ƀ_���[�W��^����
		if (enemy_timer[id] == 20) {
			PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
			switch (battle_enemy[id].id_) {
			case Enemy::GREENFAIRY:
				switch (enemy_random[id]) {
				case 0:
				case 1:
				case 2:
					fairy_green_attack[0][id] = true;
					break;
				case 3:
					fairy_green_attack[1][id] = true;
					break;
				}
				break;
			case Enemy::BLUEFAIRY:
				switch (enemy_random[id]) {
				case 0:
				case 1:
				case 2:
					fairy_blue_attack[0][id] = true;
					break;
				case 3:
					fairy_blue_attack[1][id] = true;
					break;
				}
				break;
			}
		}
		//�U�����[�V�������I��������~�ɖ߂�
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//�_���[�W���󂯂��Ƃ��̓���
		//�̂�����
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10�t���[����Ɉړ���Ԃɖ߂�
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HP��0��������Ă��玀�S����
			else if (battle_enemy[id].hp_ <= 0) {
				battle_enemy[id].pos_x_ = -1;
				battle_enemy[id].pos_y_ = -1;
				battle_enemy[id].move_ = ENEMY_DEATH;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
		}
		break;
	case ENEMY_DEATH:
		//���S����
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//��ʊO�ɂ����Ȃ�����
	if (battle_enemy[id].pos_x_ < MIN_X + 50) {
		battle_enemy[id].pos_x_ = MIN_X + 50;
	}
	if (battle_enemy[id].pos_x_ > MAX_X - 50) {
		battle_enemy[id].pos_x_ = MAX_X - 50;
	}

	//�U�����@����
	//��1
	if (fairy_green_attack[0][id] == true) {
		if (fairy_skill_frame[id] == 0) {
			switch (battle_enemy[id].dir_)
			{
			case ENEMY_LEFT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ - 30;
				fairy_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				fairy_skill_dir[id] = LEFT;
				break;
			case ENEMY_RIGHT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ + 30;
				fairy_skill_y[id] = battle_enemy[id].pos_y_ + 20;
				fairy_skill_dir[id] = RIGHT;
				break;
			}
			fairy_skill_speed_x[id] = (fairy_skill_x[id] - player.pos_x_) / 40;
			fairy_skill_speed_y[id] = (fairy_skill_y[id] - player.pos_y_) / 40;
		}
		DrawRotaGraph(fairy_skill_x[id], fairy_skill_y[id], 1, 0, skill_ani[GREEN][SK_X][0][fairy_skill_frame[id]], true);
		fairy_skill_x[id] -= fairy_skill_speed_x[id];
		fairy_skill_y[id] -= fairy_skill_speed_y[id];
		if (enemy_ani[id] == 0 || enemy_ani[id] == 5) {
			fairy_skill_frame[id]++;
		}
		if (fairy_skill_frame[id] > 15) {
			fairy_skill_frame[id] = 0;
			fairy_green_attack[0][id] = false;
		}
		//�_���[�W����
		if (fairy_skill_x[id] - 60 < player.pos_x_ && fairy_skill_x[id] + 60 > player.pos_x_
			&& fairy_skill_y[id] - 60 < player.pos_y_ && fairy_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(30, battle_enemy[id].color_);
			fairy_green_attack[0][id] = false;
			fairy_skill_frame[id] = 0;
		}
	}

	//��2
	if (fairy_green_attack[1][id] == true) {
		if (fairy_skill_frame[id] == 0) {
			switch (battle_enemy[id].dir_)
			{
			case ENEMY_LEFT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ - 100;
				fairy_skill_y[id] = battle_enemy[id].pos_y_ - 50;
				fairy_skill_dir[id] = LEFT;
				break;
			case ENEMY_RIGHT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ + 100;
				fairy_skill_y[id] = battle_enemy[id].pos_y_ - 50;
				fairy_skill_dir[id] = RIGHT;
				break;
			default:
				break;
			}
		}
		DrawRotaGraph(fairy_skill_x[id], fairy_skill_y[id], 1, 0, skill_ani[GREEN][SK_C][0][fairy_skill_frame[id]], true);
		switch (fairy_skill_dir[id])
		{
		case LEFT:
			fairy_skill_x[id] -= 10;
			break;
		case RIGHT:
			fairy_skill_x[id] += 10;
		}
		if (enemy_ani[id] == 0 || enemy_ani[id] == 5) {
			fairy_skill_frame[id]++;
		}
		if (fairy_skill_frame[id] > 16) {
			fairy_skill_rock[id] = false;
			fairy_skill_frame[id] = 0;
			fairy_green_attack[1][id] = false;
		}
		//�_���[�W����
		if (fairy_skill_frame[id] < 8 && fairy_skill_frame[id] > 1) {
			if (fairy_skill_x[id] - 90 < player.pos_x_ && fairy_skill_x[id] + 90 > player.pos_x_
				&& fairy_skill_y[id] - 150 < player.pos_y_ && fairy_skill_y[id] + 150 > player.pos_y_) {
				if (!fairy_skill_rock[id]) {
					playerDamage(60, battle_enemy[id].color_);
					fairy_skill_rock[id] = true;
				}
			}
		}
	}


	//��1
	if (fairy_blue_attack[0][id] == true) {
		if (fairy_skill_frame[id] == 0) {
			switch (battle_enemy[id].dir_)
			{
			case ENEMY_LEFT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ - 20;
				fairy_skill_y[id] = battle_enemy[id].pos_y_;
				fairy_skill_dir[id] = LEFT;
				break;
			case ENEMY_RIGHT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ + 20;
				fairy_skill_y[id] = battle_enemy[id].pos_y_;
				fairy_skill_dir[id] = RIGHT;
				break;
			}
			fairy_skill_speed_x[id] = (fairy_skill_x[id] - player.pos_x_) / 60;
			fairy_skill_speed_y[id] = (fairy_skill_y[id] - player.pos_y_) / 60;
		}
		DrawRotaGraph(fairy_skill_x[id], fairy_skill_y[id], 1, 0, skill_ani[BLUE][SK_Z][0][fairy_skill_frame[id]], true);
		fairy_skill_x[id] -= fairy_skill_speed_x[id];
		fairy_skill_y[id] -= fairy_skill_speed_y[id];
		if (enemy_ani[id] == 0) {
			fairy_skill_frame[id]++;
		}
		if (fairy_skill_frame[id] > 8) {
			fairy_skill_frame[id] = 0;
			fairy_blue_attack[0][id] = false;
		}
		//�_���[�W����
		if (fairy_skill_x[id] - 60 < player.pos_x_ && fairy_skill_x[id] + 60 > player.pos_x_
			&& fairy_skill_y[id] - 60 < player.pos_y_ && fairy_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(40, battle_enemy[id].color_);
			fairy_blue_attack[0][id] = false;
			fairy_skill_frame[id] = 0;
		}
	}

	//��2
	if (fairy_blue_attack[1][id] == true) {
		if (fairy_skill_frame[id] == 0) {
			switch (battle_enemy[id].dir_)
			{
			case ENEMY_LEFT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ - 652;
				fairy_skill_y[id] = battle_enemy[id].pos_y_;
				fairy_skill_dir[id] = LEFT;
				break;
			case ENEMY_RIGHT:
				fairy_skill_x[id] = battle_enemy[id].pos_x_ + 140;
				fairy_skill_y[id] = battle_enemy[id].pos_y_;
				fairy_skill_dir[id] = RIGHT;
				break;
			}
			fairy_skill_speed_x[id] = (fairy_skill_x[id] - player.pos_x_) / 60;
			fairy_skill_speed_y[id] = (fairy_skill_y[id] - player.pos_y_) / 60;
		}
		DrawRotaGraph(fairy_skill_x[id], fairy_skill_y[id], 0.4F, 0, skill_ani[BLUE][SK_C][0][fairy_skill_frame[id]], true);
		DrawRotaGraph(fairy_skill_x[id] + 256, fairy_skill_y[id], 0.4F, 0, skill_ani[BLUE][SK_C][0][fairy_skill_frame[id]], true);
		DrawRotaGraph(fairy_skill_x[id] + 512, fairy_skill_y[id], 0.4F, 0, skill_ani[BLUE][SK_C][0][fairy_skill_frame[id]], true);
		if (enemy_ani[id] == 0) {
			fairy_skill_frame[id]++;
		}
		if (fairy_skill_frame[id] > 4) {
			fairy_skill_frame[id] = 0;
			fairy_blue_attack[1][id] = false;
		}
		//�_���[�W����
		if (fairy_skill_frame[id] == 1 && enemy_ani[id] == 0) {
			PlaySoundMem(se_beam, DX_PLAYTYPE_BACK);
			if (fairy_skill_x[id] - 140 < player.pos_x_ && fairy_skill_x[id] + 652 > player.pos_x_
				&& fairy_skill_y[id] - 90 < player.pos_y_ && fairy_skill_y[id] + 90 > player.pos_y_) {
				playerDamage(70, battle_enemy[id].color_);
			}
		}
	}

}

//�h���S��
//�߂Â��Ēʏ�U��3�񁨐F�ς�����ʒ[�œ���s��
bool init_doragon = false;
int doragon_terepo_ani[10];
int doragon_terepo_frame;
int doragon_count = 0;
bool doragon_special = false;
bool doragon_red = false;
bool doragon_green = false;
bool doragon_blue = false;

int doragon_red_frame[7] = { 0,0,0,0,0,0,0 };
int doragon_red_x[7] = { 800,670,540,410,280,150,20 };
int doragon_red_y = 520;

int doragon_green_frame = 0;
int doragon_green_x = 0;
int doragon_green_y = 0;

int doragon_blue_frame = 0;
int doragon_blue_x = 620;
int doragon_blue_y = 550;

void aiDragon(int id) {
	if (!init_doragon) {
		LoadDivGraph("graphics/ani/change.png", 10, 10, 1, 240, 240, doragon_terepo_ani);
		init_doragon = true;
	}
	//y=530
	//�v���C���[�̕�������
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//�A�j���[�V����
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//���ԃJ�E���g
	//���1��
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//�G�ꂽ��_���[�W
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 60 && battle_enemy[id].pos_x_ < player.pos_x_ + 60
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 100 && battle_enemy[id].pos_y_ < player.pos_y_ + 60) {
		playerDamage(20, battle_enemy[id].color_);
	}

	//��Ԗ��̓���
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//1�b�~�܂�
		if (enemy_timer[id] == 60) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
			doragon_terepo_frame = 0;
		}
		//3��s��������
		if (doragon_count == 3) {
			if (enemy_timer[id] > 15 && enemy_timer[id] <= 55) {
				DrawRotaGraph(battle_enemy[id].pos_x_, battle_enemy[id].pos_y_, 1, 0, doragon_terepo_ani[doragon_terepo_frame], true);
			}
			if ((enemy_ani[id] == 0 || enemy_ani[id] == 5) && doragon_terepo_frame < 9) {
				doragon_terepo_frame++;
			}
			if (enemy_timer[id] == 30) {
				PlaySoundMem(se_change, DX_PLAYTYPE_BACK);
				//�����ω�
				battle_enemy[id].color_ = rand() % 3;
				for (int i = 0; i < 4; i++) {
					battle_enemy[id].img_[ENEMY_STOP][i] = img_dragon[battle_enemy[id].color_][ENEMY_STOP][i];
				}
				for (int i = 0; i < 6; i++) {
					battle_enemy[id].img_[ENEMY_MOVE][i] = img_dragon[battle_enemy[id].color_][ENEMY_MOVE][i];
				}
				for (int i = 0; i < 5; i++) {
					battle_enemy[id].img_[ENEMY_ATACK][i] = img_dragon[battle_enemy[id].color_][ENEMY_ATACK][i];
				}
				//����Z
				doragon_special = true;
			}
			if (enemy_timer[id] == 56) {
				doragon_count = 0;
			}
		}
		break;
	case ENEMY_MOVE:
		//�ړ��X�s�[�h�̐ݒ�
		enemy_speed_x[id] = 3;
		if (!doragon_special) {
			//�v���C���[�ɋ߂Â��܂œ���
			switch (battle_enemy[id].dir_) {
			case ENEMY_LEFT:
				battle_enemy[id].pos_x_ -= enemy_speed_x[id];
				break;
			case ENEMY_RIGHT:
				battle_enemy[id].pos_x_ += enemy_speed_x[id];
				break;
			}
			//�v���C���[�ɋ߂Â�����U���Ɉڍs
			if (battle_enemy[id].pos_x_ > player.pos_x_ - 130 && battle_enemy[id].pos_x_ < player.pos_x_ + 130
				&& battle_enemy[id].pos_y_ > player.pos_y_ - 100 && battle_enemy[id].pos_y_ < player.pos_y_ + 60) {
				battle_enemy[id].move_ = ENEMY_ATACK;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
				doragon_count += 1;
			}
		}
		else {
			//�E��������X900�܂ňړ�
			battle_enemy[id].dir_ = ENEMY_RIGHT;
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			//900�𒴂����獶�������čU����ԂɈڍs
			if (battle_enemy[id].pos_x_ >= 900) {
				battle_enemy[id].pos_x_ = 900;
				battle_enemy[id].dir_ = ENEMY_LEFT;
				battle_enemy[id].move_ = ENEMY_ATACK;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
		}
		break;
	case ENEMY_ATACK:
		//�U������̃^�C�~���O�Ńv���C���[�Ƀ_���[�W��^����
		if (enemy_timer[id] == 20) {
			PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
			if (!doragon_special) {
				if (battle_enemy[id].pos_x_ > player.pos_x_ - 160 && battle_enemy[id].pos_x_ < player.pos_x_ + 160
					&& battle_enemy[id].pos_y_ > player.pos_y_ - 100 && battle_enemy[id].pos_y_ < player.pos_y_ + 60) {
					playerDamage(25, battle_enemy[id].color_);
				}
			}
			//����U��
			else {
				switch (battle_enemy[id].color_) {
				case RED:
					doragon_red = true;
					break;
				case GREEN:
					doragon_green = true;
					break;
				case BLUE:
					doragon_blue = true;
					break;
				}
			}
		}
		//�U�����[�V�������I��������~�ɖ߂�
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			doragon_special = false;
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DEATH:
		//���S����
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//��ʊO�ɂ����Ȃ�����
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
	//HP��0��������Ă��玀�S����
	if (battle_enemy[id].hp_ <= 0) {
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].move_ = ENEMY_DEATH;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
	}

	//����U��
	//��
	if (doragon_red == true) {
		if (enemy_ani[id] == 0 || enemy_ani[id] == 5)
			doragon_red_frame[0]++;
		for (int i = 0; i < 6; i++) {
			DrawRotaGraph(doragon_red_x[i], doragon_red_y, 1, 0, skill_ani[RED][SK_C][0][doragon_red_frame[i]], true);
			doragon_red_frame[i + 1] = doragon_red_frame[i] - 3;
		}
		DrawRotaGraph(doragon_red_x[6], doragon_red_y, 1, 0, skill_ani[RED][SK_C][0][doragon_red_frame[6]], true);
		if (doragon_red_frame[6] > 16) {
			for (int i = 0; i < 7; i++) {
				doragon_red_frame[i] = 0;
				doragon_red = false;
			}
		}
		//�_���[�W����
		for (int i = 0; i < 7; i++) {
			if (doragon_red_frame[i] == 4 && (enemy_ani[id] == 0 || enemy_ani[id] == 5)) {
				PlaySoundMem(se_bomb, DX_PLAYTYPE_BACK);
				if (doragon_red_x[i] - 130 < player.pos_x_ && doragon_red_x[i] + 130 > player.pos_x_
					&& doragon_red_y - 110 < player.pos_y_ && doragon_red_y + 110 > player.pos_y_) {
					playerDamage(70, battle_enemy[id].color_);
				}
			}
		}
	}
	//��
	if (doragon_green == true) {
		if (doragon_green_frame == 0) {
			doragon_green_x = 800;
			doragon_green_y = 450;
			}
		DrawRotaGraph(doragon_green_x, doragon_green_y, 2, 0, skill_ani[GREEN][SK_C][0][doragon_green_frame], true);
		doragon_green_x -= 25;
		if (enemy_ani[id] == 0 || enemy_ani[id] == 5) {
			doragon_green_frame++;
		}
		if (doragon_green_frame > 16) {
			doragon_green_frame = 0;
			doragon_green = false;
		}
		if (doragon_green_x - 150 < player.pos_x_ && doragon_green_x + 20 > player.pos_x_
			&& doragon_green_y - 200 < player.pos_y_ && doragon_green_y + 200 > player.pos_y_) {
			playerDamage(60, battle_enemy[id].color_);
		}
	}
	//��
	if (doragon_blue == true) {
		DrawRotaGraph(doragon_blue_x, doragon_blue_y, 0.8F, 0, skill_ani[BLUE][SK_C][0][doragon_blue_frame], true);
		DrawRotaGraph(doragon_blue_x - 512, doragon_blue_y, 0.8F, 0, skill_ani[BLUE][SK_C][0][doragon_blue_frame], true);
		if (enemy_ani[id] == 0) {
			doragon_blue_frame++;
		}
		if (doragon_blue_frame > 4) {
			doragon_blue_frame = 0;
			doragon_blue = false;
		}
		//�_���[�W����
		if (doragon_blue_frame == 1 && enemy_ani[id] == 0) {
			PlaySoundMem(se_beam, DX_PLAYTYPE_BACK);
			if (player.pos_y_  > 450) {
				playerDamage(70, battle_enemy[id].color_);
			}
		}
	}
}