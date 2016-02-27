#include<DxLib.h>
#include"Chara.h"
#include"Config.h"
#include"Key.h"
#include"Field.h"
#include"Weapon.h"

//キャラの描画に使う変数
static int chara_x;
static int chara_y;
//キャラの移動に使う変数
static int chara_v;

//キャラの体力
static int chara_hp;

//リスポーンまでの時間を入れる変数
static int chara_respawn_counter;

//武器を再起するまでの時間を入れる変数
static int weapon_respawn;

//キャラのリスポーンに使うフラグ
bool chara_respawn_flag;

enum{ //キャラクターの方向
	FRONT,
	RIGHT,
	BACK,
	LEFT
}angle;


void Chara_Init(){ //キャラで使う変数を初期化する関数
	//キャラクターの初期位置
	chara_x = 0;
	chara_y = 870;
	//キャラクターの移動速度
	chara_v = 30;
	//キャラクターのHP
	chara_hp = 100;
	//チャラクターの向いてる方向
	angle = FRONT;

	chara_respawn_counter = 1000;

	chara_respawn_flag = true;

	weapon_respawn = 1000;

}

void Chara_Draw(){ //キャラの描画をする関数
	if (chara_respawn_flag == true){
		//キャラの描画
		DrawBox(chara_x, chara_y, chara_x + 30, chara_y + 30, RED, true);

		//目の描画
		if (angle == FRONT){ //前向きの目の描画
			DrawBox(chara_x + 5, chara_y + 10, chara_x + 10, chara_y + 15, BLACK, true);
			DrawBox(chara_x + 20, chara_y + 10, chara_x + 25, chara_y + 15, BLACK, true);
		}
		if (angle == BACK){ //下向きの目の描画
			DrawBox(chara_x + 5, chara_y + 20, chara_x + 10, chara_y + 25, BLACK, true);
			DrawBox(chara_x + 20, chara_y + 20, chara_x + 25, chara_y + 25, BLACK, true);
		}
		if (angle == RIGHT){ //右向きの目の描画
			DrawBox(chara_x + 20, chara_y + 10, chara_x + 25, chara_y + 15, BLACK, true);
		}
		if (angle == LEFT){ //左向きの目の描画
			DrawBox(chara_x + 5, chara_y + 10, chara_x + 10, chara_y + 15, BLACK, true);
		}

		//淵の描画
		DrawBox(chara_x, chara_y, chara_x + 30, chara_y + 30, BLACK, false);

		//DrawFormatString(0, 90, BLACK, "自分の体力：%d", chara_hp);
	}
	chara_respawn_counter++;
	//DrawFormatString(0, 0, BLACK, "%d", chara_respawn_counter);
}

void Chara_Move(){ //キャラの移動をする関数
	if (chara_respawn_flag == true){
		//上キー関係
		if (Key_Get(KEY_INPUT_UP) == 1 && angle != FRONT){ //前向きじゃないのに上キーが押されたら前向きにする
			angle = FRONT;
		}
		if (Key_Get(KEY_INPUT_UP) == 1 && Field_Front_Color_Return() == 2 && angle == FRONT){ //上キーで上に移動
			chara_y -= chara_v;
		}
		//下キー関係
		if (Key_Get(KEY_INPUT_DOWN) == 1 && angle != BACK){ //下向きじゃないのに下キーが押されたら前向きにする
			angle = BACK;
		}
		if (Key_Get(KEY_INPUT_DOWN) == 1 && Field_Back_Color_Return() == 2 && angle == BACK){ //下キーで下に移動
			chara_y += chara_v;
		}
		//右キー関係
		if (Key_Get(KEY_INPUT_RIGHT) == 1 && angle != RIGHT){ //右向きじゃないのに右キーが押されたら前向きにする
			angle = RIGHT;
		}
		if (Key_Get(KEY_INPUT_RIGHT) == 1 && Field_Right_Color_Return() == 2 && angle == RIGHT){ //右キーで右に移動
			chara_x += chara_v;
		}
		//左キー関係
		if (Key_Get(KEY_INPUT_LEFT) == 1 && angle != LEFT){ //左向きじゃないのに左キーが押されたら前向きにする
			angle = LEFT;
		}
		if (Key_Get(KEY_INPUT_LEFT) == 1 && Field_Left_Color_Return() == 2 && angle == LEFT){ //左キーで左に移動
			chara_x -= chara_v;
		}
	}
}

void Chara_Decision(){ //キャラの当たり判定を行う関数
	if (chara_x <= 0){ //画面左の当たり判定
		chara_x = 0;
	}
	if (chara_x >= 570){ //画面右の当たり判定
		chara_x = 570;
	}
	if (chara_y <= 0){ //画面上の当たり判定
		chara_y = 0;
	}
	if (chara_y >= 870){ //画面下の当たり判定
		chara_y = 870;
	}
}

void Chara_Paint(){ //キャラの攻撃（ペイント）を行う関数
	if (chara_respawn_flag == true){
		if ((Key_Get(KEY_INPUT_RETURN) == 1) && (angle == FRONT)){
			if (Get_Weapon_Select_Chara() == HAND_GUN && weapon_respawn > HANDGUN_RESPAWN){
				Field_Front_Paint_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == MACHINE_GUN && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Front_Paint_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SNIPER_RIFLE && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Front_Paint_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SHOT_GUN && weapon_respawn > SHOTGUN_RESPAWN){
				Field_Front_Paint_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
		if ((Key_Get(KEY_INPUT_RETURN) == 1) && (angle == BACK)){
			if (Get_Weapon_Select_Chara() == HAND_GUN && weapon_respawn > HANDGUN_RESPAWN){
				Field_Back_Paint_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == MACHINE_GUN && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Back_Paint_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SNIPER_RIFLE && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Back_Paint_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SHOT_GUN && weapon_respawn > SHOTGUN_RESPAWN){
				Field_Back_Paint_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
		if ((Key_Get(KEY_INPUT_RETURN) == 1) && (angle == RIGHT)){
			if (Get_Weapon_Select_Chara() == HAND_GUN && weapon_respawn > HANDGUN_RESPAWN){
				Field_Right_Paint_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == MACHINE_GUN && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Right_Paint_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SNIPER_RIFLE && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Right_Paint_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SHOT_GUN && weapon_respawn > SHOTGUN_RESPAWN){
				Field_Right_Paint_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
		if ((Key_Get(KEY_INPUT_RETURN) == 1) && (angle == LEFT)){
			if (Get_Weapon_Select_Chara() == HAND_GUN && weapon_respawn > HANDGUN_RESPAWN){
				Field_Left_Paint_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == MACHINE_GUN && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Left_Paint_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SNIPER_RIFLE && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Left_Paint_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Chara() == SHOT_GUN && weapon_respawn > SHOTGUN_RESPAWN){
				Field_Left_Paint_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
	}
	weapon_respawn++;
	//DrawFormatString(0, 200, RED, "weapon_respawn:%d秒", weapon_respawn / 60);
}


void Chara_Damage_Handgun(){ //キャラクターのダメージを行う関数
	chara_hp -= 30;
}
void Chara_Damage_Machinegun(){ //キャラクターのダメージを行う関数
	chara_hp -= 50;
}
void Chara_Damage_Sniperrifle(){ //キャラクターのダメージを行う関数
	chara_hp -= 100;
}
void Chara_Damage_Shotgun(){ //キャラクターのダメージを行う関数
	chara_hp -= 100;
}


void Chara_Respawn(){ //キャラクターのリスポーンする（最初の位置にする）関数
	Chara_Init();
	chara_respawn_counter = 0;
}

void Chara_Respawn_Time(){ //キャラクターの復帰するまでの時間を扱う関数
	if (chara_respawn_counter > 150){
		chara_respawn_flag = true;
	}
}

void Chara_Hp_Check(){ //キャラクターのHPをチェックする関数
	if (chara_hp <= 0){
		Chara_Respawn();
		chara_respawn_flag = false;
	}
}


int Chara_X_Return(){ //キャラのｘ座標を渡す関数
	return chara_x;
}

int Chara_Y_Return(){ //キャラのｙ座標を渡す関数
	return chara_y;
}