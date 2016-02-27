#include<DxLib.h>
#include"Config.h"
#include"Key.h"
#include"Weapon.h"
#include<string.h>
#include<stdio.h>

//�}�E�X�̈ʒu�����Ă����ϐ�
static int mouse_point_x;
static int mouse_point_y;

//�e�̑I���t���O
static int weapon_select_chara;
static int weapon_select_enemy;

//�X�e�[�W��ύX������t���O
static bool weapon_flag;

//�t�H���g�f�[�^�����Ă���
static int font_handle;
static int font_handle2;

//�N���b�N�̉񐔂��J�E���g����ϐ�
static int select_count;

//�I�񂾕�������Ă����ϐ�
static char *chara_select_weapon;
static char *enemy_select_weapon;

void Weapon_Init(){
	mouse_point_x = 0;
	mouse_point_y = 0;
	weapon_select_chara = 0;
	weapon_select_enemy = 0;
	weapon_flag = false;
	font_handle = CreateFontToHandle("�l�r ����", 20, 8);
	font_handle2 = CreateFontToHandle("MS �S�V�b�N", 30, 8);
	select_count = 0;
	chara_select_weapon = "����";
	enemy_select_weapon = "����";

}

void Weapon(){
	Weapon_Draw();
	Weapon_Select();
	Check_Select_Count();
}

void Weapon_Draw(){
	//����摜�̕\��
	LoadGraphScreen(0, 0, "hand.jpg", TRUE);
	LoadGraphScreen(300, 330, "machine2.jpg", TRUE);
	LoadGraphScreen(0, 450, "sniper.jpg", TRUE);
	LoadGraphScreen(300, 450, "shotgun.jpg", TRUE);
	//DrawFormatString(0, 120, BLACK, "%d", weapon_flag);
	//DrawFormatString(0, 120, BLACK, "%d", weapon_select);


	DrawStringToHandle(300, 5, "�g����������̔ԍ���", RED, font_handle);
	DrawStringToHandle(300, 35, "�L�[�{�[�h�œ��͂��Ă�������", RED, font_handle);
	DrawStringToHandle(260, 420, "�@", BLACK, font_handle2);
	DrawStringToHandle(310, 420, "�A", BLACK, font_handle2);
	DrawStringToHandle(260, 450, "�B", BLACK, font_handle2);
	DrawStringToHandle(310, 450, "�C", BLACK, font_handle2);

	DrawStringToHandle(300, 85, "�`���񂪑I�񂾕����", RED, font_handle);
	DrawFormatStringToHandle(360, 115, RED, font_handle, "%s�ł�", chara_select_weapon);
	DrawStringToHandle(300, 145, "�a���񂪑I�񂾕����", RED, font_handle);
	DrawFormatStringToHandle(360, 175, RED, font_handle, "%s�ł�", enemy_select_weapon);
}

void Weapon_Select(){
	//DrawFormatString(0, 0, BLACK, "select_count:%d", select_count);
	if ((Key_Get(KEY_INPUT_1) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "�n���h�K�����I�΂�܂���");
		weapon_select_chara = HAND_GUN;
		chara_select_weapon = "�n���h�K��";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_2) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "�}�V���K�����I�΂�܂���");
		weapon_select_chara = MACHINE_GUN;
		chara_select_weapon = "�}�V���K��";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_3) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "�X�i�C�p�[���C�t�����I�΂�܂���");
		weapon_select_chara = SNIPER_RIFLE;
		chara_select_weapon = "�X�i�C�p�[���C�t��";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_4) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "�V���b�g�K�����I�΂�܂���");
		weapon_select_chara = SHOT_GUN;
		chara_select_weapon = "�V���b�g�K��";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_1) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "�n���h�K�����I�΂�܂���");
		weapon_select_enemy = HAND_GUN;
		enemy_select_weapon = "�n���h�K��";
		select_count = 2;
	}else if ((Key_Get(KEY_INPUT_2) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "�}�V���K�����I�΂�܂���");
		weapon_select_enemy = MACHINE_GUN;
		enemy_select_weapon = "�}�V���K��";
		select_count = 2;
	}else if ((Key_Get(KEY_INPUT_3) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "�X�i�C�p�[���C�t�����I�΂�܂���");
		weapon_select_enemy = SNIPER_RIFLE;
		enemy_select_weapon = "�X�i�C�p�[���C�t��";
		select_count = 2;
	}else if ((Key_Get(KEY_INPUT_4) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "�V���b�g�K�����I�΂�܂���");
		weapon_select_enemy = SHOT_GUN;
		enemy_select_weapon = "�V���b�g�K��";
		select_count = 2;
	}
}

void Check_Select_Count(){
	if (select_count == 2){
		weapon_flag = true;
	}
}

bool Get_Weapon_Flag(){
	return weapon_flag;
}



int Get_Weapon_Select_Chara(){
	return weapon_select_chara;
}

int Get_Weapon_Select_Enemy(){
	return weapon_select_enemy;
}