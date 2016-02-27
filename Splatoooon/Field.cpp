#include<DxLib.h>
#include"Config.h"
#include"Chara.h"
#include"Key.h"
#include"Enemy.h"

//フィールドの位置を表す変数
static int field_x;
static int field_y;

//キャラの位置を表す変数
static int chara_x_paint;
static int chara_y_paint;

//敵の位置を表す変数
static int enemy_x_paint;
static int enemy_y_paint;

//キャラの位置をマス単位で表す変数
static int chara_x_paint_masu;
static int chara_y_paint_masu;

//敵の位置をマス単位で表す変数
static int enemy_x_paint_masu;
static int enemy_y_paint_masu;

//ゲームの経過時間を入れておく変数
static int game_count;

//ゲームの終了を管理するフラグ
bool game_end_flag;

//色を塗った枚数を入れておく変数
static int color_count_chara = 0;
static int color_count_enemy = 0;

//フィールドで使う変数
static int field[30][20] = {
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },

};


void Field_Init(){ //フィールドで使う変数の初期化
	field_x = 0;
	field_y = 0;

	//キャラクターの位置
	chara_x_paint = Chara_X_Return();
	chara_y_paint = Chara_Y_Return();
	//キャラクターの位置（マス単位）
	chara_x_paint_masu = Chara_X_Return() / 30;
	chara_y_paint_masu = Chara_Y_Return() / 30;
	//敵の位置
	enemy_x_paint = Enemy_X_Return();
	enemy_y_paint = Enemy_Y_Return();
	//敵の位置（マス単位）
	enemy_x_paint_masu = Enemy_X_Return() / 30;
	enemy_y_paint_masu = Enemy_Y_Return() / 30;


	game_count = 0;

	game_end_flag = false;


	//キャラクターの初期位置のマスを自分の色に塗る
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (chara_x_paint_masu == j && chara_y_paint_masu == i){
				field[i][j] = 2;
			}
		}
	}
	//敵の初期位置のマスを敵の色に塗る
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (enemy_x_paint_masu == j && enemy_y_paint_masu == i){
				field[i][j] = 3;
			}
		}
	}


}


void Field_Draw(){ //フィールドを描画する関数
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (field[i][j] == 0){ //値が０のときに黄色のマスの描画
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, YELLOW, true);
				//DrawFormatString(field_x, field_y, BLACK, "%d", field[i][j]);
				field_x += 30; //ｘ方向の位置ずらし
			}
			if (field[i][j] == 1){ //値が１のときに緑のマスの描画
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, GREEN, true);
				//DrawFormatString(field_x, field_y, BLACK, "%d", field[i][j]);
				field_x += 30; //ｙ方向の位置ずらし
			}
			if (field[i][j] == 2){ //値が２のときに赤のマスの描画
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, RED, true);
				field_x += 30;
			}
			if (field[i][j] == 3){ //値が３のときに青のマスの描画
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, BLUE, true);
				field_x += 30;
			}
		}
		field_x = 0; //右端までいったので、左端に戻す
		field_y += 30; //ｙ方向のマスを一個分下にする
	}
	field_y = 0; //一番下までいったので、一番上に戻す
	game_count++;
	//DrawFormatString(0, 5, BLACK, "ゲームの経過時間：%d秒", game_count / 60);

}


void Chara_X_Get(){ //キャラのｘ座標の取得
	chara_x_paint = Chara_X_Return();
	chara_x_paint_masu = Chara_X_Return() / 30;
	/*
	//キャラの位置を表示しておく
	DrawFormatString(0, 30, BLACK, "キャラのｘ座標：%d", chara_x_paint);
	DrawFormatString(0, 60, BLACK, "キャラのｘコマ座標：%d", chara_x_paint_masu);
	*/
}

void Chara_Y_Get(){ //キャラのｙ座標の取得
	chara_y_paint = Chara_Y_Return();
	chara_y_paint_masu = Chara_Y_Return() / 30;
	/*
	//キャラの位置を表示しておく
	DrawFormatString(0, 90, BLACK, "キャラのｙ座標：%d", chara_y_paint);
	DrawFormatString(0, 120, BLACK, "キャラのｙコマ座標：%d", chara_y_paint_masu);
	*/
}


void Enemy_X_Get(){ //敵のｘ座標の取得
	enemy_x_paint = Enemy_X_Return();
	enemy_x_paint_masu = Enemy_X_Return() / 30;
	/*
	//キャラの位置を表示しておく
	DrawFormatString(0, 30 + 120, BLACK, "キャラのｘ座標：%d", enemy_x_paint);
	DrawFormatString(0, 60 + 120, BLACK, "キャラのｘコマ座標：%d", enemy_x_paint_masu);
	*/
}

void Enemy_Y_Get(){ //敵のｙ座標の取得
	enemy_y_paint = Enemy_Y_Return();
	enemy_y_paint_masu = Enemy_Y_Return() / 30;
	/*
	//キャラの位置を表示しておく
	DrawFormatString(0, 90 + 120, BLACK, "キャラのｙ座標：%d", enemy_y_paint);
	DrawFormatString(0, 120 + 120, BLACK, "キャラのｙコマ座標：%d", enemy_y_paint_masu);
	*/
}


void Color_Count(){ //コマを数える関数
	color_count_chara = 0;
	color_count_enemy = 0;
	for (int i = 0; i < 30; i++){ //自分のコマの数
		for (int j = 0; j < 20; j++){
			if (field[i][j] == 2){
				color_count_chara += 1;
			}
		}
	}
	for (int i = 0; i < 30; i++){ //敵のコマの数
		for (int j = 0; j < 20; j++){
			if (field[i][j] == 3){
				color_count_enemy += 1;
			}
		}
	}
	//DrawFormatString(0, 30, BLACK, "自分の枚数：%d", color_count_chara);
	//DrawFormatString(0, 60, BLACK, "敵の枚数：%d", color_count_enemy);
}

int Get_Chara_Color_Count(){
	return color_count_chara;
}

int Get_Enemy_Color_Count(){
	return color_count_enemy;
}




//////////////////////////////////////フィールドのペイント/////////////////////////////////////////////////////////////////////////////////////////////////

//ハンドガン
void Field_Front_Paint_Handgun(){ //キャラが攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Handgun();
				}
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					field[i][j] = 2;
				}
			}
		}
	}

}




void Field_Back_Paint_Handgun(){ //キャラが攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Handgun();
				}
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					field[i][j] = 2;
				}
			}

		}
	}
}

void Field_Right_Paint_Handgun(){ //キャラが攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Handgun();
				}
			}else{
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					field[i][j] = 2;
			}

			}
		}
	}
}

void Field_Left_Paint_Handgun(){ //キャラが攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Handgun();
				}
			}else{
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					field[i][j] = 2;
				}
			}

		}
	}
}

//マシンガン
void Field_Front_Paint_Machinegun(){ //キャラが攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Machinegun();
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu - 2){
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					Enemy_Damage_Machinegun(); 
					field[i][j] = 2;
				}
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					if(chara_y_paint_masu == 1){
						field[i][j] = 2;
					}else{
						field[i][j] = 2;
						field[i - 1][j] = 2;
					}
				}
			}
		}
	}
	//DrawFormatString(0, 200, BLACK, "%d", chara_y_paint_masu);
}




void Field_Back_Paint_Machinegun(){ //キャラが攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Machinegun();
				}
			}
			else if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu + 2){
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					Enemy_Damage_Machinegun();
					field[i][j] = 2;
				}
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					field[i][j] = 2;
					field[i + 1][j] = 2;
				}
			}

		}
	}
}

void Field_Right_Paint_Machinegun(){ //キャラが攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Machinegun();
				}
			}else if (Enemy_X_Return() / 30 == chara_x_paint_masu + 2 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Machinegun();
					field[i][j] = 2;
				}
			}else{
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					if(chara_x_paint_masu == 18){
						field[i][j] = 2;
					}else{
						field[i][j] = 2;
						field[i][j + 1] = 2;
					}
				}

			}
		}
	}
}

void Field_Left_Paint_Machinegun(){ //キャラが攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Machinegun();
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu - 2 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Machinegun();
					field[i][j] = 2;
				}
			}else{
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					if(chara_x_paint_masu == 1){
						field[i][j] = 2;
					}else{
						field[i][j] = 2;
						field[i][j - 1] = 2;
					}
				}
			}

		}
	}
}

//スナイパー
void Field_Front_Paint_Sniperrifle(){ //キャラが攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Sniperrifle();
				}
			}else if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu - 2){
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
				}			
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu - 3){
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
					field[i - 1][j] = 2;
				}			
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					if(chara_y_paint_masu == 1){
						field[i][j] = 2;
					}else if(chara_y_paint_masu == 2){
						field[i][j] = 2;
						field[i - 1][j] = 2;
					}else{
						field[i][j] = 2;
						field[i - 1][j] = 2;
						field[i - 2][j] = 2;
					}
					
				}
			}
		}
	}

}




void Field_Back_Paint_Sniperrifle(){ //キャラが攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Sniperrifle();
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu + 2){
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu + 3){
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
					field[i + 1][j] = 2;
				}
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					field[i][j] = 2;
					field[i + 1][j] = 2;
					field[i + 2][j] = 2;
				}
			}

		}
	}
}

void Field_Right_Paint_Sniperrifle(){ //キャラが攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Sniperrifle();
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu + 2 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu + 3 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
					field[i][j + 1] = 2;
				}
			}else{
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					if(chara_x_paint_masu == 18){
						field[i][j] = 2;
					}else if(chara_x_paint_masu == 17){
						field[i][j] = 2;
						field[i][j + 1] = 2;
					}else{
						field[i][j] = 2;
						field[i][j + 1] = 2;
						field[i][j + 2] = 2;
					}
				}

			}
		}
	}
}

void Field_Left_Paint_Sniperrifle(){ //キャラが攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Enemy_Damage_Sniperrifle();
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu - 2 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu - 3 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Sniperrifle();
					field[i][j] = 2;
					field[i][j - 1] = 2;
				}
			}else{
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					if(chara_x_paint_masu == 1){
						field[i][j] = 2;
					}else if(chara_x_paint_masu == 2){
						field[i][j] = 2;
						field[i][j - 1] = 2;
					}else{
						field[i][j] = 2;
						field[i][j - 1] = 2;
						field[i][j - 2] = 2;
					}
				}
			}

		}
	}
}

//ショットガン
void Field_Front_Paint_Shotgun(){ //キャラが攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					Enemy_Damage_Shotgun();
					field[i][j - 1] = 2;
					field[i][j + 1] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i][j + 1] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i][j - 1] = 2;

				}
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu - 1 == i){
					if(chara_x_paint_masu == 0){
						field[i][j] = 2;
						field[i][j + 1] = 2;
					}else if(chara_x_paint_masu == 19){
						field[i][j] = 2;
						field[i][j - 1] = 2;
					}else{
						field[i][j] = 2;
						field[i][j - 1] = 2;
						field[i][j + 1] = 2;
					}
				}
			}
		}
	}

}




void Field_Back_Paint_Shotgun(){ //キャラが攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if (Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
					Enemy_Damage_Shotgun();
					field[i][j - 1] = 2;
					field[i][j + 1] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i][j + 1] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i][j - 1] = 2;
				}
			}else{
				if (chara_x_paint_masu == j && chara_y_paint_masu + 1 == i){
					if(chara_x_paint_masu == 0){
						field[i][j] = 2;
						field[i][j + 1] = 2;
					}else if(chara_x_paint_masu == 19){
						field[i][j] = 2;
						field[i][j - 1] = 2;
					}else{
						field[i][j] = 2;
						field[i][j - 1] = 2;
						field[i][j + 1] = 2;
					}
				}
			}

		}
	}
}

void Field_Right_Paint_Shotgun(){ //キャラが攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Shotgun();
					field[i - 1][j] = 2;
					field[i + 1][j] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i + 1][j] = 2;

				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu + 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i - 1][j] = 2;
				}
			}else{
				if (chara_x_paint_masu + 1 == j && chara_y_paint_masu == i){
					if(chara_y_paint_masu == 0){
						field[i][j] = 2;
						field[i + 1][j] = 2;
					}else{
						field[i][j] = 2;
						field[i - 1][j] = 2;
						field[i + 1][j] = 2;
					}
				}

			}
		}
	}
}

void Field_Left_Paint_Shotgun(){ //キャラが攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu){
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Shotgun();
					field[i - 1][j] = 2;
					field[i + 1][j] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu - 1){
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i + 1][j] = 2;
				}
			}else if(Enemy_X_Return() / 30 == chara_x_paint_masu - 1 && Enemy_Y_Return() / 30 == chara_y_paint_masu + 1){
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					Enemy_Damage_Shotgun();
					field[i][j] = 2;
					field[i - 1][j] = 2;
				}
			}else{
				if (chara_x_paint_masu - 1 == j && chara_y_paint_masu == i){
					if(chara_y_paint_masu == 0){
						field[i][j] = 2;
						field[i + 1][j] = 2;
					}else{
						field[i][j] = 2;
						field[i - 1][j] = 2;
						field[i + 1][j] = 2;
					}
				}
			}

		}
	}
}























//////////////////////////////////////敵のフィールドのペイント/////////////////////////////////////////////////////////////////////////////////////////////////
//ハンドガン
void Field_Front_Paint_Enemy_Handgun(){ //敵が攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Handgun();
				}
			}else{
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					field[i][j] = 3;
				}
			}
		}
	}

}


void Field_Back_Paint_Enemy_Handgun(){ //敵が攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Handgun();
				}
			}else{
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					field[i][j] = 3;
				}
			}
		}
	}
}

void Field_Right_Paint_Enemy_Handgun(){ //敵が攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Handgun();
				}
			}else{
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					field[i][j] = 3;
				}
			}

		}
	}
}

void Field_Left_Paint_Enemy_Handgun(){ //敵が攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Handgun();
				}
			}else{
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					field[i][j] = 3;
				}
			}

		}
	}
}
//マシンガン
void Field_Front_Paint_Enemy_Machinegun(){ //敵が攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Machinegun();
				}
			}else if(Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu - 2){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					Chara_Damage_Machinegun();
					field[i][j] = 3;
				}
			}else{
				if(enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					if(enemy_y_paint_masu == 1){
						field[i][j] = 3;
					}else{ 
						field[i][j] = 3;
						field[i - 1][j] = 3;
					}
				}
			}
		}
	}

}


void Field_Back_Paint_Enemy_Machinegun(){ //敵が攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Machinegun();
				}
			}else if(Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu + 2){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					Chara_Damage_Machinegun();
					field[i][j] = 3;
				}
			}else{
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					field[i][j] = 3;
					field[i + 1][j] = 3;
				}
			}
		}
	}
}

void Field_Right_Paint_Enemy_Machinegun(){ //敵が攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Machinegun();
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu + 2 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Machinegun();
					field[i][j] = 3;
				}
			}else{
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					if(enemy_x_paint_masu == 18){
						field[i][j] = 3;
					}else{
						field[i][j] = 3;
						field[i][j + 1] = 3;
					}
				}
			}

		}
	}
}

void Field_Left_Paint_Enemy_Machinegun(){ //敵が攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Machinegun();
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu - 2 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Machinegun();
					field[i][j] = 3;
				}
			}else{
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					if(enemy_x_paint_masu == 1){
						field[i][j] = 3;
					}else{
						field[i][j] = 3;
						field[i][j - 1] = 3;
					}
				}
			}

		}
	}
}
//スナイパー
void Field_Front_Paint_Enemy_Sniperrifle(){ //敵が攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Sniperrifle();
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu - 2){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu - 3){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
					field[i - 1][j] = 3;
				}
			}else{
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					if(enemy_y_paint_masu == 1){
						field[i][j] = 3;
					}else if(enemy_y_paint_masu == 2){
						field[i][j] = 3;
						field[i - 1][j] = 3;
					}else{
						field[i][j] = 3;
						field[i - 1][j] = 3;
						field[i - 2][j] = 3;
					}
				}
			}
		}
	}

}


void Field_Back_Paint_Enemy_Sniperrifle(){ //敵が攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Sniperrifle();
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu + 2){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu + 3){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
					field[i + 3][j] = 3;
				}
			}else{
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					field[i][j] = 3;
					field[i + 1][j] = 3;
					field[i + 2][j] = 3;
				}
			}
		}
	}
}

void Field_Right_Paint_Enemy_Sniperrifle(){ //敵が攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Sniperrifle();
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu + 2 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu + 3 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
					field[i][j + 1] = 3;
				}
			}else{
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					if(enemy_x_paint_masu == 18){
						field[i][j] = 3;
					}else if(enemy_x_paint_masu == 17){
						field[i][j] = 3;
						field[i][j + 1] = 3;
					}else{
						field[i][j] = 3;
						field[i][j + 1] = 3;
						field[i][j + 2] = 3;
					}
				}
			}

		}
	}
}

void Field_Left_Paint_Enemy_Sniperrifle(){ //敵が攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if ((i == 0) && (j == 0)){
					Chara_Damage_Sniperrifle();
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu - 2 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu - 3 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Sniperrifle();
					field[i][j] = 3;
					field[i][j - 1] = 3;
				}
			}else{
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					if(enemy_x_paint_masu == 1){
						field[i][j] = 3;
					}else if(enemy_x_paint_masu == 2){
						field[i][j] = 3;
						field[i][j - 1] = 3;
					}else{
						field[i][j] = 3;
						field[i][j - 1] = 3;
						field[i][j - 2] = 3;
					}
				}
			}

		}
	}
}
//ショットガン
void Field_Front_Paint_Enemy_Shotgun(){ //敵が攻撃したときに前のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					Chara_Damage_Shotgun();
					field[i][j - 1] = 3;
					field[i][j + 1] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					Chara_Damage_Shotgun();
					field[i][j] = 3;
					field[i - 1][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					Chara_Damage_Shotgun();
					field[i][j] = 3;
					field[i + 1][j] = 3;
				}
			} else{
				if (enemy_x_paint_masu == j && enemy_y_paint_masu - 1 == i){
					if(enemy_x_paint_masu == 0){
						field[i][j] = 3;
						field[i][j + 1] = 3;
					}else if(enemy_x_paint_masu == 19){
						field[i][j] = 3;
						field[i][j - 1] = 3;
					}else{
						field[i][j] = 3;
						field[i][j - 1] = 3;
						field[i][j + 1] = 3;
					}
				}
			}
		}
	}

}


void Field_Back_Paint_Enemy_Shotgun(){ //敵が攻撃したときに後ろのフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					Chara_Damage_Shotgun();
					field[i][j - 1] = 3;
					field[i][j + 1] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					Chara_Damage_Shotgun();
					field[i][j] = 3;
					field[i][j + 1] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					Chara_Damage_Shotgun();
					field[i][j - 1] = 3;
				}
			}else{
				if (enemy_x_paint_masu == j && enemy_y_paint_masu + 1 == i){
					if(enemy_x_paint_masu == 0){
						field[i][j] = 3;
						field[i][j + 1] = 3;
					}else if(enemy_x_paint_masu == 19){
						field[i][j] = 3;
						field[i][j - 1] = 3;
					}else{
						field[i][j] = 3;
						field[i][j - 1] = 3;
						field[i][j + 1] = 3;
					}
				}
			}
		}
	}
}

void Field_Right_Paint_Enemy_Shotgun(){ //敵が攻撃したときに右のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Shotgun();
					field[i - 1][j] = 3;
					field[i + 1][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Shotgun();
					field[i][j] = 3;
					field[i + 1][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu + 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Shotgun();
					field[i][j] = 3;
					field[i - 1][j] = 3;
				}
			}else{
				if (enemy_x_paint_masu + 1 == j && enemy_y_paint_masu == i){
					if(enemy_y_paint_masu == 0){
						field[i][j] = 3;
						field[i + 1][j] = 3;
					}else{
						field[i][j] = 3;
						field[i - 1][j] = 3;
						field[i + 1][j] = 3;
					}
				}
			}

		}
	}
}

void Field_Left_Paint_Enemy_Shotgun(){ //敵が攻撃したときに左のフィールドをペイントする
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu){
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Shotgun();
					field[i - 1][j] = 3;
					field[i + 1][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu - 1){
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Shotgun();
					field[i][j] = 3;
					field[i + 1][j] = 3;
				}
			}else if (Chara_X_Return() / 30 == enemy_x_paint_masu - 1 && Chara_Y_Return() / 30 == enemy_y_paint_masu + 1){
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					Chara_Damage_Shotgun();
					field[i][j] = 3;
					field[i - 1][j] = 3;
				}
			}else{
				if (enemy_x_paint_masu - 1 == j && enemy_y_paint_masu == i){
					if(enemy_y_paint_masu == 0){
						field[i][j] = 3;
						field[i + 1][j] = 3;
					}else{
						field[i][j] = 3;
						field[i - 1][j] = 3;
						field[i + 1][j] = 3;
					}
				}
			}

		}
	}
}






////////////////////////マスの位置を返す/////////////////////////////////////////////////////////////////
int Field_Front_Color_Return(){ //前のマスの位置を返す関数
	return field[chara_y_paint_masu - 1][chara_x_paint_masu];
}

int Field_Back_Color_Return(){ //後ろスの位置を返す関数
	return field[chara_y_paint_masu + 1][chara_x_paint_masu];
}

int Field_Right_Color_Return(){ //右のマスの位置を返す関数
	return field[chara_y_paint_masu][chara_x_paint_masu + 1];
}

int Field_Left_Color_Return(){ //左のマスの位置を返す関数
	return field[chara_y_paint_masu][chara_x_paint_masu - 1];
}


////////////////////////敵のマスの位置を返す/////////////////////////////////////////////////////////////////
int Field_Front_Color_Return_Enemy(){ //敵の前のマスの位置を返す関数
	return field[enemy_y_paint_masu - 1][enemy_x_paint_masu];
}

int Field_Back_Color_Return_Enemy(){ //敵の後ろスの位置を返す関数
	return field[enemy_y_paint_masu + 1][enemy_x_paint_masu];
}

int Field_Right_Color_Return_Enemy(){ //敵の右のマスの位置を返す関数
	return field[enemy_y_paint_masu][enemy_x_paint_masu + 1];
}

int Field_Left_Color_Return_Enemy(){ //敵の左のマスの位置を返す関数
	return field[enemy_y_paint_masu][enemy_x_paint_masu - 1];
}



void Game_End_Check(){
	if ((game_count / 60) == 60){
		game_end_flag = true;
	}
}

bool Game_End_Flag_Return(){
	return game_end_flag;
}