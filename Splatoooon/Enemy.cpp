#include<DxLib.h>
#include"Enemy.h"
#include"Config.h"
#include"Key.h"
#include"Field.h"
#include"Weapon.h"


static int enemy_x;
static int enemy_y;
static int enemy_v;
static int enemy_hp;
static int enemy_respawn_counter;
static bool enemy_respawn_flag;
static int weapon_respawn;

enum{
	FRONT,
	RIGHT,
	BACK,
	LEFT
}angle_enemy;



void Enemy_Init(){
	enemy_x = 570;
	enemy_y = 0;
	enemy_v = 30;
	angle_enemy = FRONT;
	enemy_hp = 100;
	enemy_respawn_counter = 1000;
	enemy_respawn_flag = true;
	weapon_respawn = 1000;
}

void Enemy_Draw(){ //敵の描画をする関数
	if (enemy_respawn_flag == true){
		//キャラの描画
		DrawBox(enemy_x, enemy_y, enemy_x + 30, enemy_y + 30, BLUE, true);

		//目の描画
		if (angle_enemy == FRONT){ //前向きの目の描画
			DrawBox(enemy_x + 5, enemy_y + 10, enemy_x + 10, enemy_y + 15, BLACK, true);
			DrawBox(enemy_x + 20, enemy_y + 10, enemy_x + 25, enemy_y + 15, BLACK, true);
		}
		if (angle_enemy == BACK){ //下向きの目の描画
			DrawBox(enemy_x + 5, enemy_y + 20, enemy_x + 10, enemy_y + 25, BLACK, true);
			DrawBox(enemy_x + 20, enemy_y + 20, enemy_x + 25, enemy_y + 25, BLACK, true);
		}
		if (angle_enemy == RIGHT){ //右向きの目の描画
			DrawBox(enemy_x + 20, enemy_y + 10, enemy_x + 25, enemy_y + 15, BLACK, true);
		}
		if (angle_enemy == LEFT){ //左向きの目の描画
			DrawBox(enemy_x + 5, enemy_y + 10, enemy_x + 10, enemy_y + 15, BLACK, true);
		}

		//淵の描画
		DrawBox(enemy_x, enemy_y, enemy_x + 30, enemy_y + 30, BLACK, false);

		//DrawFormatString(0, 120, BLACK, "敵のHP：%d", enemy_hp);
	}
	enemy_respawn_counter++;
	//DrawFormatString(0, 0, BLACK, "%d", enemy_respawn_counter);
}

void Enemy_Move(){ //敵の移動をする関数
	if (enemy_respawn_flag == true){
		//上キー関係
		if (Key_Get(KEY_INPUT_W) == 1 && angle_enemy != FRONT){ //前向きじゃないのに上キーが押されたら前向きにする
			angle_enemy = FRONT;
		}
		if (Key_Get(KEY_INPUT_W) == 1 && Field_Front_Color_Return_Enemy() == 3 && angle_enemy == FRONT){ //上キーで上に移動
			enemy_y -= enemy_v;
		}
		//下キー関係
		if (Key_Get(KEY_INPUT_S) == 1 && angle_enemy != BACK){ //下向きじゃないのに下キーが押されたら前向きにする
			angle_enemy = BACK;
		}
		if (Key_Get(KEY_INPUT_S) == 1 && Field_Back_Color_Return_Enemy() == 3 && angle_enemy == BACK){ //下キーで下に移動
			enemy_y += enemy_v;
		}
		//右キー関係
		if (Key_Get(KEY_INPUT_D) == 1 && angle_enemy != RIGHT){ //右向きじゃないのに右キーが押されたら前向きにする
			angle_enemy = RIGHT;
		}
		if (Key_Get(KEY_INPUT_D) == 1 && Field_Right_Color_Return_Enemy() == 3 && angle_enemy == RIGHT){ //右キーで右に移動
			enemy_x += enemy_v;
		}
		//左キー関係
		if (Key_Get(KEY_INPUT_A) == 1 && angle_enemy != LEFT){ //左向きじゃないのに左キーが押されたら前向きにする
			angle_enemy = LEFT;
		}
		if (Key_Get(KEY_INPUT_A) == 1 && Field_Left_Color_Return_Enemy() == 3 && angle_enemy == LEFT){ //左キーで左に移動
			enemy_x -= enemy_v;
		}
	}
}

void Enemy_Decision(){ //キャラの当たり判定を行う関数
	if (enemy_x <= 0){ //画面左の当たり判定
		enemy_x = 0;
	}
	if (enemy_x >= 570){ //画面右の当たり判定
		enemy_x = 570;
	}
	if (enemy_y <= 0){ //画面上の当たり判定
		enemy_y = 0;
	}
	if (enemy_y >= 870){ //画面下の当たり判定
		enemy_y = 870;
	}
}



void Enemy_Paint(){ //敵の攻撃（ペイント）を行う関数
	if (enemy_respawn_flag == true){
		if ((Key_Get(KEY_INPUT_SPACE) == 1) && (angle_enemy == FRONT)){
			if (Get_Weapon_Select_Enemy() == 1 && weapon_respawn > HANDGUN_RESPAWN){
				Field_Front_Paint_Enemy_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 2 && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Front_Paint_Enemy_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 3 && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Front_Paint_Enemy_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 4 && weapon_respawn > SHOT_GUN){
				Field_Front_Paint_Enemy_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
		if ((Key_Get(KEY_INPUT_SPACE) == 1) && (angle_enemy == BACK)){
			if (Get_Weapon_Select_Enemy() == 1 && weapon_respawn > HANDGUN_RESPAWN){
				Field_Back_Paint_Enemy_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 2 && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Back_Paint_Enemy_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 3 && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Back_Paint_Enemy_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 4 && weapon_respawn > SHOT_GUN){
				Field_Back_Paint_Enemy_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
		if ((Key_Get(KEY_INPUT_SPACE) == 1) && (angle_enemy == RIGHT)){
			if (Get_Weapon_Select_Enemy() == 1 && weapon_respawn > HANDGUN_RESPAWN){
				Field_Right_Paint_Enemy_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 2 && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Right_Paint_Enemy_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 3 && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Right_Paint_Enemy_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 4 && weapon_respawn > SHOT_GUN){
				Field_Right_Paint_Enemy_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
		if ((Key_Get(KEY_INPUT_SPACE) == 1) && (angle_enemy == LEFT)){
			if (Get_Weapon_Select_Enemy() == 1 && weapon_respawn > HANDGUN_RESPAWN){
				Field_Left_Paint_Enemy_Handgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 2 && weapon_respawn > MACHINEGUN_RESPAWN){
				Field_Left_Paint_Enemy_Machinegun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 3 && weapon_respawn > SNIPERRIFLE_RESPAWN){
				Field_Left_Paint_Enemy_Sniperrifle();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}else if (Get_Weapon_Select_Enemy() == 4 && weapon_respawn > SHOT_GUN){
				Field_Left_Paint_Enemy_Shotgun();
				PlaySoundFile("shot.mp3", DX_PLAYTYPE_BACK);
				weapon_respawn = 0;
			}
		}
	}
	weapon_respawn++;
	//DrawFormatString(0, 180, RED, "weapon_respawn:%d秒", weapon_respawn / 60);
}


void Enemy_Damage_Handgun(){
	enemy_hp -= 30;
}
void Enemy_Damage_Machinegun(){
	enemy_hp -= 50;
}
void Enemy_Damage_Sniperrifle(){
	enemy_hp -= 100;
}
void Enemy_Damage_Shotgun(){
	enemy_hp -= 100;
}


void Enemy_Respawn(){
	Enemy_Init();
	enemy_respawn_counter = 0;
}


void Enemy_Respawn_Time(){
	if (enemy_respawn_counter > 150){
		enemy_respawn_flag = true;
	}
}


void Enemy_Hp_Check(){
	if (enemy_hp <= 0){
		Enemy_Respawn();
		enemy_respawn_flag = false;
	}
}

int Enemy_X_Return(){ //敵のｘ座標を渡す関数
	return enemy_x;
}

int Enemy_Y_Return(){ //敵のｙ座標を渡す関数
	return enemy_y;
}