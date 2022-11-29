#include "../dxlib_ext/dxlib_ext.h"
#include "status.h"

//プレイヤーステータス
Player player;

//フレーム数カウント
int ani_frame = 20;

//属性画像
int color[3] = {0};

//スキルパラメータ
Skill skill[3][3];

//スプリント
int img_sprint = 0;
int sprint_cd = 0;

//経験値テーブル
int maxexp[19] = { 0 };

void getStatus() {

	//キャラ画像読み込み
	LoadDivGraph("graphics/chara/chara_red.png", 12, 3, 4, 96 / 3, 128 / 4, player.img_[RED]);
	LoadDivGraph("graphics/chara/chara_green.png", 12, 3, 4, 96 / 3, 128 / 4, player.img_[GREEN]);
	LoadDivGraph("graphics/chara/chara_blue.png", 12, 3, 4, 96 / 3, 128 / 4, player.img_[BLUE]);

	//属性画像読み込み
	color[RED] = LoadGraph("graphics/color/red.png");
	color[GREEN] = LoadGraph("graphics/color/green.png");
	color[BLUE] = LoadGraph("graphics/color/blue.png");

	//スプリント画像読み込み
	img_sprint = LoadGraph("graphics/skill/sprint.png");

	//スキル画像読み込み
	//赤属性（アタック）
	skill[RED][SK_Z].img_[0] = LoadGraph("graphics/skill/red02.png"); skill[RED][SK_Z].img_[1] = LoadGraph("graphics/skill/red03.png");
	skill[RED][SK_X].img_[0] = LoadGraph("graphics/skill/red12.png"); skill[RED][SK_X].img_[1] = LoadGraph("graphics/skill/red13.png");
	skill[RED][SK_C].img_[0] = LoadGraph("graphics/skill/red22.png"); skill[RED][SK_C].img_[1] = LoadGraph("graphics/skill/red23.png");
	//緑属性（スピード）
	skill[GREEN][SK_Z].img_[0] = LoadGraph("graphics/skill/green02.png"); skill[GREEN][SK_Z].img_[1] = LoadGraph("graphics/skill/green03.png");
	skill[GREEN][SK_X].img_[0] = LoadGraph("graphics/skill/green12.png"); skill[GREEN][SK_X].img_[1] = LoadGraph("graphics/skill/green13.png");
	skill[GREEN][SK_C].img_[0] = LoadGraph("graphics/skill/green22.png"); skill[GREEN][SK_C].img_[1] = LoadGraph("graphics/skill/green23.png");
	//青属性（バランス）
	skill[BLUE][SK_Z].img_[0] = LoadGraph("graphics/skill/blue02.png"); skill[BLUE][SK_Z].img_[1] = LoadGraph("graphics/skill/blue03.png");
	skill[BLUE][SK_X].img_[0] = LoadGraph("graphics/skill/blue12.png"); skill[BLUE][SK_X].img_[1] = LoadGraph("graphics/skill/blue13.png");
	skill[BLUE][SK_C].img_[0] = LoadGraph("graphics/skill/blue22.png"); skill[BLUE][SK_C].img_[1] = LoadGraph("graphics/skill/blue23.png");

	//スキル初期パラメータ設定
	for (int i = 0; i < 6; i++) {
		//赤属性（アタック）
		skill[RED][SK_Z].atk_[i] = 15 + (i * 3); skill[RED][SK_Z].cd_[i] = 1;
		skill[RED][SK_X].atk_[i] = 30 + (i * 6); skill[RED][SK_X].cd_[i] = 6 - ((float)i * 0.2f);
		skill[RED][SK_C].atk_[i] = 60 + (i * 12); skill[RED][SK_C].cd_[i] = 9 - ((float)i * 0.2f);
		//緑属性（スピード）
		skill[GREEN][SK_Z].atk_[i] = 5 + (i * 1); skill[GREEN][SK_Z].cd_[i] = 0.5;
		skill[GREEN][SK_X].atk_[i] = 10 + (i * 2); skill[GREEN][SK_X].cd_[i] = 2 - ((float)i * 0.2f);
		skill[GREEN][SK_C].atk_[i] = 20 + (i * 4); skill[GREEN][SK_C].cd_[i] = 3 - ((float)i * 0.2f);
		//青属性（バランス）
		skill[BLUE][SK_Z].atk_[i] = 10 + (i * 2); skill[BLUE][SK_Z].cd_[i] = 1;
		skill[BLUE][SK_X].atk_[i] = 20 + (i * 4); skill[BLUE][SK_X].cd_[i] = 4 - ((float)i * 0.2f);
		skill[BLUE][SK_C].atk_[i] = 40 + (i * 8); skill[BLUE][SK_C].cd_[i] = 6 - ((float)i * 0.2f);
	}

	//スキル説明文
	skill[RED][SK_Z].message_ = "炎を纏った剣で斬る";
	skill[RED][SK_X].message_ = "炎の玉を飛ばす";
	skill[RED][SK_C].message_ = "炎の剣を突き刺して爆発させる";

	skill[GREEN][SK_Z].message_ = "風の刃で斬る";
	skill[GREEN][SK_X].message_ = "風の刃を飛ばす";
	skill[GREEN][SK_C].message_ = "竜巻を作り出して飛ばす";

	skill[BLUE][SK_Z].message_ = "冷気を飛ばす";
	skill[BLUE][SK_X].message_ = "地面から氷の柱を突き出す";
	skill[BLUE][SK_C].message_ = "冷気を纏ったビームを放つ";

	//経験値テーブルの計算
	maxexp[0] = 100;
	for (int i = 1; i < 19; i++) {
		maxexp[i] = maxexp[i-1] + 10 * i;
	}
}

//赤レベルアップ
void rlvUp() {
	//スキルレベル上昇
	if (player.r_lv_ < 17) {
		player.r_sp_++;
	}
	//レベル17以降　ステータスUP
	else if (player.r_lv_ < 21) {
		player.atk_ += 0.05f;
	}
}

//緑レベルアップ
void glvUp() {
	//スキルレベル上昇
	if (player.g_lv_ < 17) {
		player.g_sp_++;
	}
	//レベル17以降　ステータスUP
	else if (player.g_lv_ < 21) {
		player.cd_ -= 0.025f;
	}
}

//青レベルアップ
void blvUp() {
	//スキルレベル上昇
	if (player.b_lv_ < 17) {
		player.b_sp_++;
	}
	//レベル17以降　ステータスUP
	else if (player.b_lv_ < 21) {
		player.cri_ += 2;
	}
}


Equip eq_date[4][10];
Equip eq_have[4][10];
Equip eq_now[4];
int eq_num[4] = {1,1,1,1};

//装備データ入力
void getEquipStatus() {
	eq_date[RED][0].name_ = "炎の直剣";
	eq_date[RED][0].atk_ = 1.1;
	eq_date[RED][0].message_ = "赤属性の攻撃の威力が10%上がる";

	eq_date[RED][1].name_ = "炎の細剣";
	eq_date[RED][1].cd_ = 0.8;
	eq_date[RED][1].message_ = "赤属性の攻撃のクールタイムが20%短くなる";

	eq_date[RED][2].name_ = "炎の太刀";
	eq_date[RED][2].cri_ = 20;
	eq_date[RED][2].message_ = "赤属性の攻撃のクリティカル率が20%上がる";

	eq_date[RED][3].name_ = "炎の大剣";
	eq_date[RED][3].atk_ = 1.3;
	eq_date[RED][3].message_ = "赤属性の攻撃の威力が30%上がる";

	eq_date[GREEN][0].name_ = "風の双剣";
	eq_date[GREEN][0].atk_ = 1.1;
	eq_date[GREEN][0].message_ = "緑属性の攻撃の威力が10%上がる";

	eq_date[GREEN][1].name_ = "風の短剣";
	eq_date[GREEN][1].atk_ = 1.3;
	eq_date[GREEN][1].message_ = "緑属性の攻撃の威力が20%上がる";

	eq_date[GREEN][2].name_ = "風の双刀";
	eq_date[GREEN][2].cri_ = 20;
	eq_date[GREEN][2].message_ = "緑属性の攻撃のクリティカル率が20%上がる";

	eq_date[GREEN][3].name_ = "嵐の双剣";
	eq_date[GREEN][3].cri_ = 30;
	eq_date[GREEN][3].message_ = "緑属性の攻撃のクリティカル率が30%上がる";

	eq_date[BLUE][0].name_ = "氷の杖";
	eq_date[BLUE][0].atk_ = 1.1;
	eq_date[BLUE][0].message_ = "青属性の攻撃の威力が10%上がる";

	eq_date[BLUE][1].name_ = "氷の短杖";
	eq_date[BLUE][1].cd_ = 0.8;
	eq_date[BLUE][1].message_ = "青属性の攻撃のクールタイムが20%短くなる";

	eq_date[BLUE][2].name_ = "氷の魔杖";
	eq_date[BLUE][2].cri_ = 20;
	eq_date[BLUE][2].message_ = "青属性の攻撃のクリティカル率が20%上がる";

	eq_date[BLUE][3].name_ = "氷の聖杖";
	eq_date[BLUE][3].atk_ = 1.2;
	eq_date[BLUE][3].cri_ = 20;
	eq_date[BLUE][3].message_ = "青属性の攻撃の威力とクリティカル率が20%上がる";

	eq_date[ARM][0].name_ = "ハートのペンダント";
	eq_date[ARM][0].hp_ = 20;
	eq_date[ARM][0].message_ = "最大HPを20増やす";

	eq_date[ARM][1].name_ = "力の腕輪";
	eq_date[ARM][1].atk_ = 1.2;
	eq_date[ARM][1].message_ = "与えるダメージが20%上がる";

	eq_date[ARM][2].name_ = "羽根のブーツ";
	eq_date[ARM][2].cd_ = 0.8;
	eq_date[ARM][2].message_ = "クールタイムが20%短くなる";

	eq_date[ARM][3].name_ = "爪のペンダント";
	eq_date[ARM][3].cri_ = 10;
	eq_date[ARM][3].message_ = "クリティカル率が10%上がる";

	//初期装備
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

//装備入手処理
void getEquipment(int TYPE,int ID) {
	//重複チェック
	for (int i = 0; i < eq_num[TYPE]; i++) {
		if (eq_have[TYPE][i].name_ == eq_date[TYPE][ID].name_)
			get_double_equ = true;
	}
	if (!get_double_equ) {
		//取得処理
		if (eq_num[TYPE] < 10) {
			eq_have[TYPE][eq_num[TYPE]] = eq_date[TYPE][ID];
			eq_num[TYPE]++;
		}
		//所持数がいっぱい
		else {

		}
	}
	get_double_equ = false;
}


Item item_date[2][10];
Item item_have[2][10];
int item_num[2] = { 1,1 };

//アイテムデータ入力
void getItemStatus() {
	item_date[ITEM][0].name_ = "やくそう";
	item_date[ITEM][0].message_ = "HPが20回復する";
	item_date[ITEM][0].id_ = 0;
	item_date[ITEM][0].type_ = GRASS;
	item_date[ITEM][0].heal_ = 20;
	item_date[ITEM][0].buy_ = 50;
	item_date[ITEM][0].sold_ = 10;

	item_date[ITEM][1].name_ = "いやしそう";
	item_date[ITEM][1].message_ = "HPが40回復する";
	item_date[ITEM][1].id_ = 1;
	item_date[ITEM][1].type_ = GRASS;
	item_date[ITEM][1].heal_ = 40;
	item_date[ITEM][1].buy_ = 90;
	item_date[ITEM][1].sold_ = 18;

	item_date[ITEM][2].name_ = "下級ポーション";
	item_date[ITEM][2].message_ = "HPが60回復する";
	item_date[ITEM][2].id_ = 2;
	item_date[ITEM][2].type_ = PORTION;
	item_date[ITEM][2].heal_ = 60;
	item_date[ITEM][2].buy_ = 130;
	item_date[ITEM][2].sold_ = 26;

	item_date[ITEM][3].name_ = "上級ポーション";
	item_date[ITEM][3].message_ = "HPが100回復する";
	item_date[ITEM][3].id_ = 3;
	item_date[ITEM][3].type_ = PORTION;
	item_date[ITEM][3].heal_ = 100;
	item_date[ITEM][3].buy_ = 220;
	item_date[ITEM][3].sold_ = 44;

	item_date[ITEM][4].name_ = "エリクサー";
	item_date[ITEM][4].message_ = "HPが200回復する";
	item_date[ITEM][4].id_ = 4;
	item_date[ITEM][4].type_ = PORTION;
	item_date[ITEM][4].heal_ = 200;
	item_date[ITEM][4].buy_ = 420;
	item_date[ITEM][4].sold_ = 81;

	item_date[DAIJI][0].name_ = "古びた鍵";
	item_date[DAIJI][0].message_ = "ポケットに入っていた謎の鍵。どこの鍵なのかは分からない";
	item_date[DAIJI][0].id_ = 0;
	item_date[DAIJI][0].type_ = KEY;

	//初期アイテム
	item_have[ITEM][0] = item_date[ITEM][0];
	item_have[ITEM][0].num_ = 3;

	item_have[DAIJI][0] = item_date[DAIJI][0];
	item_have[DAIJI][0].num_ = 1;
}

//アイテム入手処理
bool get_double_item = false;

void getItem(int TYPE, int ID) {
	//重複チェック
	for (int i = 0; i < item_num[TYPE]; i++) {
		if (item_have[TYPE][i].name_ == item_date[TYPE][ID].name_) {
			item_have[TYPE][i].num_++;
			get_double_item = true;
		}
	}
	if (!get_double_item) {
		//取得処理
		item_have[TYPE][item_num[TYPE]] = item_date[TYPE][ID];
		item_have[TYPE][item_num[TYPE]].num_ = 1;
		item_num[TYPE]++;
	}
	get_double_item = false;
}