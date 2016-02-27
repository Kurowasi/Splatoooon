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

void Enemy_Draw(){ //�G�̕`�������֐�
	if (enemy_respawn_flag == true){
		//�L�����̕`��
		DrawBox(enemy_x, enemy_y, enemy_x + 30, enemy_y + 30, BLUE, true);

		//�ڂ̕`��
		if (angle_enemy == FRONT){ //�O�����̖ڂ̕`��
			DrawBox(enemy_x + 5, enemy_y + 10, enemy_x + 10, enemy_y + 15, BLACK, true);
			DrawBox(enemy_x + 20, enemy_y + 10, enemy_x + 25, enemy_y + 15, BLACK, true);
		}
		if (angle_enemy == BACK){ //�������̖ڂ̕`��
			DrawBox(enemy_x + 5, enemy_y + 20, enemy_x + 10, enemy_y + 25, BLACK, true);
			DrawBox(enemy_x + 20, enemy_y + 20, enemy_x + 25, enemy_y + 25, BLACK, true);
		}
		if (angle_enemy == RIGHT){ //�E�����̖ڂ̕`��
			DrawBox(enemy_x + 20, enemy_y + 10, enemy_x + 25, enemy_y + 15, BLACK, true);
		}
		if (angle_enemy == LEFT){ //�������̖ڂ̕`��
			DrawBox(enemy_x + 5, enemy_y + 10, enemy_x + 10, enemy_y + 15, BLACK, true);
		}

		//���̕`��
		DrawBox(enemy_x, enemy_y, enemy_x + 30, enemy_y + 30, BLACK, false);

		//DrawFormatString(0, 120, BLACK, "�G��HP�F%d", enemy_hp);
	}
	enemy_respawn_counter++;
	//DrawFormatString(0, 0, BLACK, "%d", enemy_respawn_counter);
}

void Enemy_Move(){ //�G�̈ړ�������֐�
	if (enemy_respawn_flag == true){
		//��L�[�֌W
		if (Key_Get(KEY_INPUT_W) == 1 && angle_enemy != FRONT){ //�O��������Ȃ��̂ɏ�L�[�������ꂽ��O�����ɂ���
			angle_enemy = FRONT;
		}
		if (Key_Get(KEY_INPUT_W) == 1 && Field_Front_Color_Return_Enemy() == 3 && angle_enemy == FRONT){ //��L�[�ŏ�Ɉړ�
			enemy_y -= enemy_v;
		}
		//���L�[�֌W
		if (Key_Get(KEY_INPUT_S) == 1 && angle_enemy != BACK){ //����������Ȃ��̂ɉ��L�[�������ꂽ��O�����ɂ���
			angle_enemy = BACK;
		}
		if (Key_Get(KEY_INPUT_S) == 1 && Field_Back_Color_Return_Enemy() == 3 && angle_enemy == BACK){ //���L�[�ŉ��Ɉړ�
			enemy_y += enemy_v;
		}
		//�E�L�[�֌W
		if (Key_Get(KEY_INPUT_D) == 1 && angle_enemy != RIGHT){ //�E��������Ȃ��̂ɉE�L�[�������ꂽ��O�����ɂ���
			angle_enemy = RIGHT;
		}
		if (Key_Get(KEY_INPUT_D) == 1 && Field_Right_Color_Return_Enemy() == 3 && angle_enemy == RIGHT){ //�E�L�[�ŉE�Ɉړ�
			enemy_x += enemy_v;
		}
		//���L�[�֌W
		if (Key_Get(KEY_INPUT_A) == 1 && angle_enemy != LEFT){ //����������Ȃ��̂ɍ��L�[�������ꂽ��O�����ɂ���
			angle_enemy = LEFT;
		}
		if (Key_Get(KEY_INPUT_A) == 1 && Field_Left_Color_Return_Enemy() == 3 && angle_enemy == LEFT){ //���L�[�ō��Ɉړ�
			enemy_x -= enemy_v;
		}
	}
}

void Enemy_Decision(){ //�L�����̓����蔻����s���֐�
	if (enemy_x <= 0){ //��ʍ��̓����蔻��
		enemy_x = 0;
	}
	if (enemy_x >= 570){ //��ʉE�̓����蔻��
		enemy_x = 570;
	}
	if (enemy_y <= 0){ //��ʏ�̓����蔻��
		enemy_y = 0;
	}
	if (enemy_y >= 870){ //��ʉ��̓����蔻��
		enemy_y = 870;
	}
}



void Enemy_Paint(){ //�G�̍U���i�y�C���g�j���s���֐�
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
	//DrawFormatString(0, 180, RED, "weapon_respawn:%d�b", weapon_respawn / 60);
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

int Enemy_X_Return(){ //�G�̂����W��n���֐�
	return enemy_x;
}

int Enemy_Y_Return(){ //�G�̂����W��n���֐�
	return enemy_y;
}