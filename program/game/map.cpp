#include "../dxlib_ext/dxlib_ext.h"

bool init_map = false;

//マップチップ素材の縦横数
const int CHIP_X = 10;
const int CHIP_Y = 10;
const int CHIP_ALL = CHIP_X * CHIP_Y;
int chip[CHIP_ALL] = {0};
//マップチップの縦横サイズ
const int CHIP_SIZE_X = 32;
const int CHIP_SIZE_Y = 32;
//マップサイズ
const int MAP_SIZE_X = 20;
const int MAP_SIZE_Y = 10;
const int MAP_SIZE_ALL = MAP_SIZE_X * MAP_SIZE_Y;

void mapLoad() {

	if (!init_map) {
		//画像の読み込み
		LoadDivGraph("graphics / map / map_mura.png", CHIP_ALL, CHIP_X, CHIP_Y, CHIP_SIZE_X, CHIP_SIZE_Y, chip);
		init_map = true;
	}

	int map_date[MAP_SIZE_ALL] = {
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,

	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
	};

	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int k = 0; k < MAP_SIZE_X; k++) {
			DrawRotaGraph(CHIP_SIZE_X * 2 * k + 32, CHIP_SIZE_Y * 2 * i + 32, 2, 0, chip[map_date[k + i * MAP_SIZE_Y]], true);
		}
	}

}

