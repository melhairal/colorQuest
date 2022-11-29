#include "../dxlib_ext/dxlib_ext.h"
#include "constant.h"
#include "status.h"

//プロトタイプ宣言
void playerDamage(int damage,int enemy_color);

//敵のデータを保持
Enemy enemy[11];
int img_dragon[3][3][10];

//敵パラメータのcsv読み込み
void Enemy::initialize(int type) {
	auto tbl = tnl::LoadCsv("csv/enemy.csv");
	name_ = tbl[type+1][0];

	id_ = std::atoi(tbl[type+1][1].c_str());
	hp_ = std::atoi(tbl[type+1][2].c_str());
	mhp_ = hp_;
	color_ = std::atoi(tbl[type+1][3].c_str());
	r_ = std::atoi(tbl[type + 1][4].c_str());
}

//アニメーション画像取得
void enemyImg() {
	//ブルースライム
	enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/スライムA_待機000.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/スライムA_待機001.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/スライムA_待機002.png");
	enemy[Enemy::BLUESLIME].ani_size_[ENEMY_STOP] = 3;
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/スライムA_移動000.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/スライムA_移動001.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/スライムA_移動002.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/スライムA_移動003.png");
	enemy[Enemy::BLUESLIME].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/スライムA_攻撃000.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/スライムA_攻撃001.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/スライムA_攻撃002.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/スライムA_攻撃003.png");
	enemy[Enemy::BLUESLIME].img_[ENEMY_ATACK][4] = LoadGraph("graphics/enemy/スライムA_攻撃004.png");
	enemy[Enemy::BLUESLIME].ani_size_[ENEMY_ATACK] = 5;

	//レッドスライム
	enemy[Enemy::REDSLIME].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/スライムB_待機000.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/スライムB_待機001.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/スライムB_待機002.png");
	enemy[Enemy::REDSLIME].ani_size_[ENEMY_STOP] = 3;
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/スライムB_移動000.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/スライムB_移動001.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/スライムB_移動002.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/スライムB_移動003.png");
	enemy[Enemy::REDSLIME].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/スライムB_攻撃000.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/スライムB_攻撃001.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/スライムB_攻撃002.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/スライムB_攻撃003.png");
	enemy[Enemy::REDSLIME].img_[ENEMY_ATACK][4] = LoadGraph("graphics/enemy/スライムB_攻撃004.png");
	enemy[Enemy::REDSLIME].ani_size_[ENEMY_ATACK] = 5;

	//レッドバード
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/鳥B_待機000.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/鳥B_待機001.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/鳥B_待機002.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/鳥B_待機003.png");
	enemy[Enemy::REDBIRD].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/鳥B_移動000.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/鳥B_移動001.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/鳥B_移動002.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/鳥B_移動003.png");
	enemy[Enemy::REDBIRD].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/鳥B_攻撃000.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/鳥B_攻撃001.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/鳥B_攻撃002.png");
	enemy[Enemy::REDBIRD].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/鳥B_攻撃003.png");
	enemy[Enemy::REDBIRD].ani_size_[ENEMY_ATACK] = 4;

	//グリーンバード
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/鳥C_待機000.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/鳥C_待機001.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/鳥C_待機002.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/鳥C_待機003.png");
	enemy[Enemy::GREENBIRD].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/鳥C_移動000.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/鳥C_移動001.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/鳥C_移動002.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/鳥C_移動003.png");
	enemy[Enemy::GREENBIRD].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/鳥C_攻撃000.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/鳥C_攻撃001.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/鳥C_攻撃002.png");
	enemy[Enemy::GREENBIRD].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/鳥C_攻撃003.png");
	enemy[Enemy::GREENBIRD].ani_size_[ENEMY_ATACK] = 4;

	//ブルーバード
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/鳥D_待機000.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/鳥D_待機001.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/鳥D_待機002.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/鳥D_待機003.png");
	enemy[Enemy::BLUEBIRD].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/鳥D_移動000.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/鳥D_移動001.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/鳥D_移動002.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/鳥D_移動003.png");
	enemy[Enemy::BLUEBIRD].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/鳥D_攻撃000.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/鳥D_攻撃001.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/鳥D_攻撃002.png");
	enemy[Enemy::BLUEBIRD].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/鳥D_攻撃003.png");
	enemy[Enemy::BLUEBIRD].ani_size_[ENEMY_ATACK] = 4;

	//レッドマジシャン
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/魔法使いA_待機000.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/魔法使いA_待機001.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/魔法使いA_待機002.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/魔法使いA_待機003.png");
	enemy[Enemy::REDMAGICIAN].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/魔法使いA_移動000.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/魔法使いA_移動001.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/魔法使いA_移動002.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/魔法使いA_移動003.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/魔法使いA_移動004.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/魔法使いA_移動005.png");
	enemy[Enemy::REDMAGICIAN].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/魔法使いA_攻撃000.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/魔法使いA_攻撃001.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/魔法使いA_攻撃002.png");
	enemy[Enemy::REDMAGICIAN].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/魔法使いA_攻撃003.png");
	enemy[Enemy::REDMAGICIAN].ani_size_[ENEMY_ATACK] = 4;

	//グリーンマジシャン
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/魔法使いD_待機000.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/魔法使いD_待機001.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/魔法使いD_待機002.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/魔法使いD_待機003.png");
	enemy[Enemy::GREENMAGICIAN].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/魔法使いD_移動000.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/魔法使いD_移動001.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/魔法使いD_移動002.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/魔法使いD_移動003.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/魔法使いD_移動004.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/魔法使いD_移動005.png");
	enemy[Enemy::GREENMAGICIAN].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/魔法使いD_攻撃000.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/魔法使いD_攻撃001.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/魔法使いD_攻撃002.png");
	enemy[Enemy::GREENMAGICIAN].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/魔法使いD_攻撃003.png");
	enemy[Enemy::GREENMAGICIAN].ani_size_[ENEMY_ATACK] = 4;

	//ブルーマジシャン
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/魔法使いB_待機000.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/魔法使いB_待機001.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/魔法使いB_待機002.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/魔法使いB_待機003.png");
	enemy[Enemy::BLUEMAGICIAN].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/魔法使いB_移動000.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/魔法使いB_移動001.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/魔法使いB_移動002.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/魔法使いB_移動003.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/魔法使いB_移動004.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/魔法使いB_移動005.png");
	enemy[Enemy::BLUEMAGICIAN].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/魔法使いB_攻撃000.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/魔法使いB_攻撃001.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/魔法使いB_攻撃002.png");
	enemy[Enemy::BLUEMAGICIAN].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/魔法使いB_攻撃003.png");
	enemy[Enemy::BLUEMAGICIAN].ani_size_[ENEMY_ATACK] = 4;

	//グリーンフェアリー
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/妖精A_待機000.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/妖精A_待機001.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/妖精A_待機002.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/妖精A_待機003.png");
	enemy[Enemy::GREENFAIRY].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/妖精A_移動000.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/妖精A_移動001.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/妖精A_移動002.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/妖精A_移動003.png");
	enemy[Enemy::GREENFAIRY].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/妖精A_攻撃000.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/妖精A_攻撃001.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/妖精A_攻撃002.png");
	enemy[Enemy::GREENFAIRY].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/妖精A_攻撃003.png");
	enemy[Enemy::GREENFAIRY].ani_size_[ENEMY_ATACK] = 4;

	//ブルーフェアリー
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/妖精B_待機000.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/妖精B_待機001.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/妖精B_待機002.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/妖精B_待機003.png");
	enemy[Enemy::BLUEFAIRY].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/妖精B_移動000.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/妖精B_移動001.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/妖精B_移動002.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/妖精B_移動003.png");
	enemy[Enemy::BLUEFAIRY].ani_size_[ENEMY_MOVE] = 4;
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/妖精B_攻撃000.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/妖精B_攻撃001.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/妖精B_攻撃002.png");
	enemy[Enemy::BLUEFAIRY].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/妖精B_攻撃003.png");
	enemy[Enemy::BLUEFAIRY].ani_size_[ENEMY_ATACK] = 4;

	//ドラゴン
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][0] = LoadGraph("graphics/enemy/ドラゴンA_待機000.png");
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][1] = LoadGraph("graphics/enemy/ドラゴンA_待機001.png");
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][2] = LoadGraph("graphics/enemy/ドラゴンA_待機002.png");
	enemy[Enemy::DRAGON].img_[ENEMY_STOP][3] = LoadGraph("graphics/enemy/ドラゴンA_待機003.png");
	enemy[Enemy::DRAGON].ani_size_[ENEMY_STOP] = 4;
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][0] = LoadGraph("graphics/enemy/ドラゴンA_移動000.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][1] = LoadGraph("graphics/enemy/ドラゴンA_移動001.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][2] = LoadGraph("graphics/enemy/ドラゴンA_移動002.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][3] = LoadGraph("graphics/enemy/ドラゴンA_移動003.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][4] = LoadGraph("graphics/enemy/ドラゴンA_移動004.png");
	enemy[Enemy::DRAGON].img_[ENEMY_MOVE][5] = LoadGraph("graphics/enemy/ドラゴンA_移動005.png");
	enemy[Enemy::DRAGON].ani_size_[ENEMY_MOVE] = 6;
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][0] = LoadGraph("graphics/enemy/ドラゴンA_攻撃000.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][1] = LoadGraph("graphics/enemy/ドラゴンA_攻撃001.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][2] = LoadGraph("graphics/enemy/ドラゴンA_攻撃002.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][3] = LoadGraph("graphics/enemy/ドラゴンA_攻撃003.png");
	enemy[Enemy::DRAGON].img_[ENEMY_ATACK][4] = LoadGraph("graphics/enemy/ドラゴンA_攻撃004.png");
	enemy[Enemy::DRAGON].ani_size_[ENEMY_ATACK] = 5;
	//赤ドラゴン
	img_dragon[RED][ENEMY_STOP][0] = LoadGraph("graphics/enemy/ドラゴンA_待機000.png");
	img_dragon[RED][ENEMY_STOP][1] = LoadGraph("graphics/enemy/ドラゴンA_待機001.png");
	img_dragon[RED][ENEMY_STOP][2] = LoadGraph("graphics/enemy/ドラゴンA_待機002.png");
	img_dragon[RED][ENEMY_STOP][3] = LoadGraph("graphics/enemy/ドラゴンA_待機003.png");
	
	img_dragon[RED][ENEMY_MOVE][0] = LoadGraph("graphics/enemy/ドラゴンA_移動000.png");
	img_dragon[RED][ENEMY_MOVE][1] = LoadGraph("graphics/enemy/ドラゴンA_移動001.png");
	img_dragon[RED][ENEMY_MOVE][2] = LoadGraph("graphics/enemy/ドラゴンA_移動002.png");
	img_dragon[RED][ENEMY_MOVE][3] = LoadGraph("graphics/enemy/ドラゴンA_移動003.png");
	img_dragon[RED][ENEMY_MOVE][4] = LoadGraph("graphics/enemy/ドラゴンA_移動004.png");
	img_dragon[RED][ENEMY_MOVE][5] = LoadGraph("graphics/enemy/ドラゴンA_移動005.png");

	img_dragon[RED][ENEMY_ATACK][0] = LoadGraph("graphics/enemy/ドラゴンA_攻撃000.png");
	img_dragon[RED][ENEMY_ATACK][1] = LoadGraph("graphics/enemy/ドラゴンA_攻撃001.png");
	img_dragon[RED][ENEMY_ATACK][2] = LoadGraph("graphics/enemy/ドラゴンA_攻撃002.png");
	img_dragon[RED][ENEMY_ATACK][3] = LoadGraph("graphics/enemy/ドラゴンA_攻撃003.png");
	img_dragon[RED][ENEMY_ATACK][4] = LoadGraph("graphics/enemy/ドラゴンA_攻撃004.png");
	//緑ドラゴン
	img_dragon[GREEN][ENEMY_STOP][0] = LoadGraph("graphics/enemy/ドラゴンC_待機000.png");
	img_dragon[GREEN][ENEMY_STOP][1] = LoadGraph("graphics/enemy/ドラゴンC_待機001.png");
	img_dragon[GREEN][ENEMY_STOP][2] = LoadGraph("graphics/enemy/ドラゴンC_待機002.png");
	img_dragon[GREEN][ENEMY_STOP][3] = LoadGraph("graphics/enemy/ドラゴンC_待機003.png");

	img_dragon[GREEN][ENEMY_MOVE][0] = LoadGraph("graphics/enemy/ドラゴンC_移動000.png");
	img_dragon[GREEN][ENEMY_MOVE][1] = LoadGraph("graphics/enemy/ドラゴンC_移動001.png");
	img_dragon[GREEN][ENEMY_MOVE][2] = LoadGraph("graphics/enemy/ドラゴンC_移動002.png");
	img_dragon[GREEN][ENEMY_MOVE][3] = LoadGraph("graphics/enemy/ドラゴンC_移動003.png");
	img_dragon[GREEN][ENEMY_MOVE][4] = LoadGraph("graphics/enemy/ドラゴンC_移動004.png");
	img_dragon[GREEN][ENEMY_MOVE][5] = LoadGraph("graphics/enemy/ドラゴンC_移動005.png");

	img_dragon[GREEN][ENEMY_ATACK][0] = LoadGraph("graphics/enemy/ドラゴンC_攻撃000.png");
	img_dragon[GREEN][ENEMY_ATACK][1] = LoadGraph("graphics/enemy/ドラゴンC_攻撃001.png");
	img_dragon[GREEN][ENEMY_ATACK][2] = LoadGraph("graphics/enemy/ドラゴンC_攻撃002.png");
	img_dragon[GREEN][ENEMY_ATACK][3] = LoadGraph("graphics/enemy/ドラゴンC_攻撃003.png");
	img_dragon[GREEN][ENEMY_ATACK][4] = LoadGraph("graphics/enemy/ドラゴンC_攻撃004.png");
	//青ドラゴン
	img_dragon[BLUE][ENEMY_STOP][0] = LoadGraph("graphics/enemy/ドラゴンB_待機000.png");
	img_dragon[BLUE][ENEMY_STOP][1] = LoadGraph("graphics/enemy/ドラゴンB_待機001.png");
	img_dragon[BLUE][ENEMY_STOP][2] = LoadGraph("graphics/enemy/ドラゴンB_待機002.png");
	img_dragon[BLUE][ENEMY_STOP][3] = LoadGraph("graphics/enemy/ドラゴンB_待機003.png");

	img_dragon[BLUE][ENEMY_MOVE][0] = LoadGraph("graphics/enemy/ドラゴンB_移動000.png");
	img_dragon[BLUE][ENEMY_MOVE][1] = LoadGraph("graphics/enemy/ドラゴンB_移動001.png");
	img_dragon[BLUE][ENEMY_MOVE][2] = LoadGraph("graphics/enemy/ドラゴンB_移動002.png");
	img_dragon[BLUE][ENEMY_MOVE][3] = LoadGraph("graphics/enemy/ドラゴンB_移動003.png");
	img_dragon[BLUE][ENEMY_MOVE][4] = LoadGraph("graphics/enemy/ドラゴンB_移動004.png");
	img_dragon[BLUE][ENEMY_MOVE][5] = LoadGraph("graphics/enemy/ドラゴンB_移動005.png");

	img_dragon[BLUE][ENEMY_ATACK][0] = LoadGraph("graphics/enemy/ドラゴンB_攻撃000.png");
	img_dragon[BLUE][ENEMY_ATACK][1] = LoadGraph("graphics/enemy/ドラゴンB_攻撃001.png");
	img_dragon[BLUE][ENEMY_ATACK][2] = LoadGraph("graphics/enemy/ドラゴンB_攻撃002.png");
	img_dragon[BLUE][ENEMY_ATACK][3] = LoadGraph("graphics/enemy/ドラゴンB_攻撃003.png");
	img_dragon[BLUE][ENEMY_ATACK][4] = LoadGraph("graphics/enemy/ドラゴンB_攻撃004.png");
}

Enemy battle_enemy[3];
int enemy_timer[3] = { 0,0,0 };
int enemy_ani[3] = { 0,0,0 };
int enemy_speed_x[3] = { 0,0,0 };
int enemy_speed_y[3] = { 0,0,0 };
int enemy_random[3] = { 0,0,0 };
int enemy_trigger[3] = { 0,0,0 };

//敵ダメージ処理
int enemy_damage_random = 0;
int enemy_damage_cri = 0;
bool damage_cri[3] = { false,false,false };
//敵ダメージ表記
int enemy_damage_count[3] = { 0,0,0 };
int enemy_damage[3] = { 0,0,0 };

void enemyDamage(int id, int MODE, int SKILL) {
	PlaySoundMem(se_damage, DX_PLAYTYPE_BACK);
	//ダメージを受けたときの動作処理を実行
	if (stage != 7) {
		battle_enemy[id].move_ = ENEMY_DAMAGE;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
	}
	//ダメージ計算
	enemy_damage[id] = skill[MODE][SKILL].atk_[skill[MODE][SKILL].slv_] * player.color_atk_[MODE];
	enemy_damage_random = rand() % (enemy_damage[id] / 5);
	enemy_damage[id] += enemy_damage_random;
	//クリティカル
	enemy_damage_cri = rand() % 100;
	if (player.color_cri_[MODE] > enemy_damage_cri) {
		enemy_damage[id] = enemy_damage[id] * 1.5;
		damage_cri[id] = true;
	}
	//属性相性計算
	if (MODE == battle_enemy[id].color_ - 1 || MODE == battle_enemy[id].color_ + 2) {
		enemy_damage[id] = enemy_damage[id] * 2;
	}
	else if (MODE == battle_enemy[id].color_ + 1 || MODE == battle_enemy[id].color_ - 2) {
		enemy_damage[id] = enemy_damage[id] / 2;
	}
	//HP減らす処理
	battle_enemy[id].hp_ -= enemy_damage[id];
	enemy_damage_count[id] = 40;
}

//敵AI
//スライム
void aiSlime(int id) {
	//y=600
	//プレイヤーの方を向く
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//アニメーション
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//時間カウント
	//上限1分
	if(enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//触れたらダメージ
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 20 && battle_enemy[id].pos_x_ < player.pos_x_ + 20
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 20 && battle_enemy[id].pos_y_ < player.pos_y_ + 20) {
		playerDamage(15, battle_enemy[id].color_);
	}

	//状態毎の動作
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//1秒止まる
		if (enemy_timer[id] == 60) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_MOVE:
		//移動スピードの設定
		enemy_speed_x[id] = 1;
		//ランダムでダッシュする
		enemy_random[id] = rand() % 600;
		if (enemy_random[id] == 0) {
			//3秒
			enemy_trigger[id] = 3 * 60;
		}
		if (enemy_trigger[id] != 0) {
			enemy_trigger[id]--;
			enemy_speed_x[id] = 2;
		}
		//プレイヤーに近づくまで動く
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			break;
		}
		//プレイヤーに近づいたら攻撃に移行
		if (battle_enemy[id].pos_x_ > player.pos_x_ - 55 && battle_enemy[id].pos_x_ < player.pos_x_ + 55
			&& battle_enemy[id].pos_y_ > player.pos_y_ - 55 && battle_enemy[id].pos_y_ < player.pos_y_ + 55) {
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_ATACK:
		//攻撃判定のタイミングでプレイヤーにダメージを与える
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
		//攻撃モーションが終わったら停止に戻る
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//ダメージを受けたときの動作
		//のけぞる
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10フレーム後に移動状態に戻る
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HPが0を下回ってたら死亡判定
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
		//死亡処理
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//画面外にいかない処理
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
}

//鳥
bool bird_damage_rock[3];
void aiBird(int id) {
	//y=400~500
	//アニメーション
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//時間カウント
	//上限1分
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//触れたらダメージ
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 40 && battle_enemy[id].pos_x_ < player.pos_x_ + 40
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 40 && battle_enemy[id].pos_y_ < player.pos_y_ + 40) {
		if (!bird_damage_rock[id]) {
			playerDamage(35, battle_enemy[id].color_);
			bird_damage_rock[id] = true;
		}
	}
	//状態毎の動作
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//プレイヤーの方を向く
		battle_enemy[id].dir_ = ENEMY_LEFT;
		if (battle_enemy[id].pos_x_ < player.pos_x_)
			battle_enemy[id].dir_ = ENEMY_RIGHT;
		//対空する高さを決める
		if (enemy_timer[id] == 1) {
			enemy_random[id] = rand() % 3;
			enemy_speed_y[id] = (battle_enemy[id].pos_y_ - (400 + 50 * enemy_random[id])) / 60;
		}
		//決まった高さに戻る
		battle_enemy[id].pos_y_ -= enemy_speed_y[id];
		//1秒止まる
		if (enemy_timer[id] == 60) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		bird_damage_rock[id] = false;
		break;
	case ENEMY_MOVE:
		//プレイヤーの方を向く
		battle_enemy[id].dir_ = ENEMY_LEFT;
		if (battle_enemy[id].pos_x_ < player.pos_x_)
			battle_enemy[id].dir_ = ENEMY_RIGHT;
		//移動スピードの設定
		enemy_speed_x[id] = 2;
		//ランダムでダッシュする
		enemy_random[id] = rand() % 600;
		if (enemy_random[id] == 0) {
			//3秒
			enemy_trigger[id] = 3 * 60;
		}
		if (enemy_trigger[id] != 0) {
			enemy_trigger[id]--;
			enemy_speed_x[id] = 3;
		}
		//プレイヤーに近づくまで動く
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			break;
		}
		//プレイヤーに近づいたら攻撃に移行
		if (battle_enemy[id].pos_x_ > player.pos_x_ - 200 && battle_enemy[id].pos_x_ < player.pos_x_ + 200) {
			PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		bird_damage_rock[id] = false;
		break;
	case ENEMY_ATACK:
		//プレイヤーの座標を記憶する
		if (enemy_timer[id] == 1) {
			enemy_speed_x[id] = (battle_enemy[id].pos_x_ - player.pos_x_) / 30;
			enemy_speed_y[id] = (battle_enemy[id].pos_y_ - (player.pos_y_ + 40)) / 30;
		}
		//突撃
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
		//攻撃モーションが終わったら停止に戻る
		if (enemy_timer[id] == 65) {
			bird_damage_rock[id] = false;
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//ダメージを受けたときの動作
		//のけぞる
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10フレーム後に移動状態に戻る
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HPが0を下回ってたら死亡判定
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
		//死亡処理
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//画面外にいかない処理
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
}

//マジシャン
bool magician_red_attack[3];
bool magician_green_attack[3];
bool magician_blue_attack[3];
extern int skill_ani[3][3][2][50];
int magician_skill_x[3];
int magician_skill_y[3];
int magician_skill_dir[3];
int magician_skill_frame[3] = {0,0,0};
//テレポートエフェクト
bool init_magician = false;
int magician_terepo_ani[10];
int magician_terepo_frame = 0;

void aiMagician(int id) {
	//y=560
	if (!init_magician) {
		LoadDivGraph("graphics/ani/terepo.png", 10, 10, 1, 120, 120, magician_terepo_ani);
		init_magician = true;
	}
	//プレイヤーの方を向く
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//アニメーション
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//時間カウント
	//上限1分
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;

	//状態毎の動作
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//ランダムで離れる
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
		//ランダムでプレイヤーの反対にテレポートする
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
		//2秒止まる
		if (enemy_timer[id] == 180) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
			magician_terepo_frame = 0;
		}
		break;
	case ENEMY_MOVE:
		//移動スピードの設定
		enemy_speed_x[id] = 1;
		//ランダムでダッシュする
		enemy_random[id] = rand() % 600;
		if (enemy_random[id] == 0) {
			//3秒
			enemy_trigger[id] = 3 * 60;
		}
		if (enemy_trigger[id] != 0) {
			enemy_trigger[id]--;
			enemy_speed_x[id] = 2;
		}
		//プレイヤーに近づくまで動く
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ -= enemy_speed_x[id];
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			break;
		}
		//プレイヤーに近づいたら攻撃に移行
		if (battle_enemy[id].pos_x_ > player.pos_x_ - 400 && battle_enemy[id].pos_x_ < player.pos_x_ + 400) {
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_ATACK:
		//攻撃判定のタイミングでプレイヤーにダメージを与える
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
		//攻撃モーションが終わったら停止に戻る
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//ダメージを受けたときの動作
		//のけぞる
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10フレーム後に移動状態に戻る
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HPが0を下回ってたら死亡判定
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
		//死亡処理
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//画面外にいかない処理
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
	//攻撃魔法処理
	//赤
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
		//ダメージ処理
		if (magician_skill_x[id] - 60 < player.pos_x_ && magician_skill_x[id] + 60 > player.pos_x_
			&& magician_skill_y[id] - 60 < player.pos_y_ && magician_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(25, battle_enemy[id].color_);
			magician_red_attack[id] = false;
			magician_skill_frame[id] = 0;
		}
	}
	//緑
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
		//ダメージ処理
		if (magician_skill_x[id] - 60 < player.pos_x_ && magician_skill_x[id] + 60 > player.pos_x_
			&& magician_skill_y[id] - 60 < player.pos_y_ && magician_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(15, battle_enemy[id].color_);
			magician_green_attack[id] = false;
			magician_skill_frame[id] = 0;
		}
	}
	//青
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
		//ダメージ処理
		if (magician_skill_x[id] - 60 < player.pos_x_ && magician_skill_x[id] + 60 > player.pos_x_
			&& magician_skill_y[id] - 60 < player.pos_y_ && magician_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(20, battle_enemy[id].color_);
			magician_blue_attack[id] = false;
			magician_skill_frame[id] = 0;
		}
	}
}

//妖精
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
	//プレイヤーの方を向く
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//アニメーション
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//時間カウント
	//上限1分
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//触れたらダメージ
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 20 && battle_enemy[id].pos_x_ < player.pos_x_ + 20
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 20 && battle_enemy[id].pos_y_ < player.pos_y_ + 20) {
		playerDamage(15, battle_enemy[id].color_);
	}

	//状態毎の動作
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//2秒止まる
		enemy_speed_x[id] = 0;
		if (enemy_timer[id] == 120) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_MOVE:
		//ランダム分岐：行動3パターン（その場、離れる、回り込む）
		if (enemy_timer[id] == 1) {
			//行動決定
			enemy_random[id] = rand() % 3;
			switch (enemy_random[id]) {
			case 0:
				//その場
				enemy_speed_x[id] = 0;
				break;
			case 1:
				//離れる
				if (battle_enemy[id].dir_ == ENEMY_LEFT) {
					enemy_speed_x[id] = 3;
				}
				else if (battle_enemy[id].dir_ == ENEMY_RIGHT) {
					enemy_speed_x[id] = -3;
				}
				break;
			case 2:
				//回り込む
				if (battle_enemy[id].dir_ == ENEMY_LEFT) {
					enemy_speed_x[id] = ((player.pos_x_ - 200) - battle_enemy[id].pos_x_) / 60;
				}
				else if (battle_enemy[id].dir_ == ENEMY_RIGHT) {
					enemy_speed_x[id] = ((player.pos_x_ + 200) - battle_enemy[id].pos_x_) / 60;
				}
	/*			enemy_speed_x[id] = ((player.pos_x_ - battle_enemy[id].pos_x_) * 2) / 60;*/
				break;
			}
			//高さ決定
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
			//移動完了→攻撃に移る
			battle_enemy[id].move_ = ENEMY_ATACK;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_ATACK:
		//攻撃判定のタイミングでプレイヤーにダメージを与える
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
		//攻撃モーションが終わったら停止に戻る
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DAMAGE:
		//ダメージを受けたときの動作
		//のけぞる
		switch (battle_enemy[id].dir_) {
		case ENEMY_LEFT:
			battle_enemy[id].pos_x_ += 5;
			break;
		case ENEMY_RIGHT:
			battle_enemy[id].pos_x_ -= 5;
			break;
		}
		//10フレーム後に移動状態に戻る
		if (enemy_timer[id] == 10) {
			if (battle_enemy[id].hp_ > 0) {
				battle_enemy[id].move_ = ENEMY_MOVE;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
			}
			//HPが0を下回ってたら死亡判定
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
		//死亡処理
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//画面外にいかない処理
	if (battle_enemy[id].pos_x_ < MIN_X + 50) {
		battle_enemy[id].pos_x_ = MIN_X + 50;
	}
	if (battle_enemy[id].pos_x_ > MAX_X - 50) {
		battle_enemy[id].pos_x_ = MAX_X - 50;
	}

	//攻撃魔法処理
	//緑1
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
		//ダメージ処理
		if (fairy_skill_x[id] - 60 < player.pos_x_ && fairy_skill_x[id] + 60 > player.pos_x_
			&& fairy_skill_y[id] - 60 < player.pos_y_ && fairy_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(30, battle_enemy[id].color_);
			fairy_green_attack[0][id] = false;
			fairy_skill_frame[id] = 0;
		}
	}

	//緑2
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
		//ダメージ処理
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


	//青1
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
		//ダメージ処理
		if (fairy_skill_x[id] - 60 < player.pos_x_ && fairy_skill_x[id] + 60 > player.pos_x_
			&& fairy_skill_y[id] - 60 < player.pos_y_ && fairy_skill_y[id] + 60 > player.pos_y_) {
			playerDamage(40, battle_enemy[id].color_);
			fairy_blue_attack[0][id] = false;
			fairy_skill_frame[id] = 0;
		}
	}

	//青2
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
		//ダメージ処理
		if (fairy_skill_frame[id] == 1 && enemy_ani[id] == 0) {
			PlaySoundMem(se_beam, DX_PLAYTYPE_BACK);
			if (fairy_skill_x[id] - 140 < player.pos_x_ && fairy_skill_x[id] + 652 > player.pos_x_
				&& fairy_skill_y[id] - 90 < player.pos_y_ && fairy_skill_y[id] + 90 > player.pos_y_) {
				playerDamage(70, battle_enemy[id].color_);
			}
		}
	}

}

//ドラゴン
//近づいて通常攻撃3回→色変え→画面端で特殊行動
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
	//プレイヤーの方を向く
	battle_enemy[id].dir_ = ENEMY_LEFT;
	if (battle_enemy[id].pos_x_ < player.pos_x_)
		battle_enemy[id].dir_ = ENEMY_RIGHT;
	//アニメーション
	enemy_ani[id]++;
	if (enemy_ani[id] == 10) {
		enemy_ani[id] = 0;
		battle_enemy[id].frame_++;
		if (battle_enemy[id].ani_size_[battle_enemy[id].move_] == battle_enemy[id].frame_)
			battle_enemy[id].frame_ = 0;
	}
	//時間カウント
	//上限1分
	if (enemy_timer[id] < 3600)
		enemy_timer[id]++;
	//触れたらダメージ
	if (battle_enemy[id].pos_x_ > player.pos_x_ - 60 && battle_enemy[id].pos_x_ < player.pos_x_ + 60
		&& battle_enemy[id].pos_y_ > player.pos_y_ - 100 && battle_enemy[id].pos_y_ < player.pos_y_ + 60) {
		playerDamage(20, battle_enemy[id].color_);
	}

	//状態毎の動作
	switch (battle_enemy[id].move_) {
	case ENEMY_STOP:
		//1秒止まる
		if (enemy_timer[id] == 60) {
			battle_enemy[id].move_ = ENEMY_MOVE;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
			doragon_terepo_frame = 0;
		}
		//3回行動したら
		if (doragon_count == 3) {
			if (enemy_timer[id] > 15 && enemy_timer[id] <= 55) {
				DrawRotaGraph(battle_enemy[id].pos_x_, battle_enemy[id].pos_y_, 1, 0, doragon_terepo_ani[doragon_terepo_frame], true);
			}
			if ((enemy_ani[id] == 0 || enemy_ani[id] == 5) && doragon_terepo_frame < 9) {
				doragon_terepo_frame++;
			}
			if (enemy_timer[id] == 30) {
				PlaySoundMem(se_change, DX_PLAYTYPE_BACK);
				//属性変化
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
				//特殊技
				doragon_special = true;
			}
			if (enemy_timer[id] == 56) {
				doragon_count = 0;
			}
		}
		break;
	case ENEMY_MOVE:
		//移動スピードの設定
		enemy_speed_x[id] = 3;
		if (!doragon_special) {
			//プレイヤーに近づくまで動く
			switch (battle_enemy[id].dir_) {
			case ENEMY_LEFT:
				battle_enemy[id].pos_x_ -= enemy_speed_x[id];
				break;
			case ENEMY_RIGHT:
				battle_enemy[id].pos_x_ += enemy_speed_x[id];
				break;
			}
			//プレイヤーに近づいたら攻撃に移行
			if (battle_enemy[id].pos_x_ > player.pos_x_ - 130 && battle_enemy[id].pos_x_ < player.pos_x_ + 130
				&& battle_enemy[id].pos_y_ > player.pos_y_ - 100 && battle_enemy[id].pos_y_ < player.pos_y_ + 60) {
				battle_enemy[id].move_ = ENEMY_ATACK;
				battle_enemy[id].frame_ = 0;
				enemy_timer[id] = 0;
				doragon_count += 1;
			}
		}
		else {
			//右を向いてX900まで移動
			battle_enemy[id].dir_ = ENEMY_RIGHT;
			battle_enemy[id].pos_x_ += enemy_speed_x[id];
			//900を超えたら左を向いて攻撃状態に移行
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
		//攻撃判定のタイミングでプレイヤーにダメージを与える
		if (enemy_timer[id] == 20) {
			PlaySoundMem(se_sowrd, DX_PLAYTYPE_BACK);
			if (!doragon_special) {
				if (battle_enemy[id].pos_x_ > player.pos_x_ - 160 && battle_enemy[id].pos_x_ < player.pos_x_ + 160
					&& battle_enemy[id].pos_y_ > player.pos_y_ - 100 && battle_enemy[id].pos_y_ < player.pos_y_ + 60) {
					playerDamage(25, battle_enemy[id].color_);
				}
			}
			//特殊攻撃
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
		//攻撃モーションが終わったら停止に戻る
		if (enemy_timer[id] == battle_enemy[id].ani_size_[ENEMY_ATACK] * 10) {
			doragon_special = false;
			battle_enemy[id].move_ = ENEMY_STOP;
			battle_enemy[id].frame_ = 0;
			enemy_timer[id] = 0;
		}
		break;
	case ENEMY_DEATH:
		//死亡処理
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
		break;
	}
	//画面外にいかない処理
	if (battle_enemy[id].pos_x_ < MIN_X) {
		battle_enemy[id].pos_x_ = MIN_X;
	}
	if (battle_enemy[id].pos_x_ > MAX_X) {
		battle_enemy[id].pos_x_ = MAX_X;
	}
	//HPが0を下回ってたら死亡判定
	if (battle_enemy[id].hp_ <= 0) {
		battle_enemy[id].pos_x_ = -1;
		battle_enemy[id].pos_y_ = -1;
		battle_enemy[id].move_ = ENEMY_DEATH;
		battle_enemy[id].frame_ = 0;
		enemy_timer[id] = 0;
	}

	//特殊攻撃
	//赤
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
		//ダメージ処理
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
	//緑
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
	//青
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
		//ダメージ処理
		if (doragon_blue_frame == 1 && enemy_ani[id] == 0) {
			PlaySoundMem(se_beam, DX_PLAYTYPE_BACK);
			if (player.pos_y_  > 450) {
				playerDamage(70, battle_enemy[id].color_);
			}
		}
	}
}