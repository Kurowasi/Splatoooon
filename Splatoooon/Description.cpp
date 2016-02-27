#include<DxLib.h>
#include"Config.h"
#include"Description.h"
#include"Key.h"


static bool description_flag;
static int font_handle;
static int font_handle2;

void Description_Init(){
	font_handle = CreateFontToHandle("�l�r ����", 50 , 3);
	font_handle2 = CreateFontToHandle("�l�r ����", 30, 3);
	description_flag = false;
}

void Description(){
	Description_Draw();
	Description_Decision();
}

void Description_Draw(){
	DrawStringToHandle(160, 0, "���[������", WHITE, font_handle);
	DrawStringToHandle(0, 100, "���̃Q�[���͂Q�l�őΐ킷��Q�[���ł��B", WHITE, font_handle2);
	DrawStringToHandle(0, 150, "�`����͐ԁB�a����͐ł��B", WHITE, font_handle2);
	DrawStringToHandle(0, 200, "�`����̃L�[�����", RED, font_handle2);
	DrawStringToHandle(0, 250, "�u��(��Ɉړ�)�v�u��(�E�Ɉړ�)�v", WHITE, font_handle2);
	DrawStringToHandle(0, 300, "�u��(���Ɉړ�)�v�u��(���Ɉړ�)�v", WHITE, font_handle2);
	DrawStringToHandle(0, 350, "Enter(�F��h��B������U������)�ł��B", WHITE, font_handle2);
	DrawStringToHandle(0, 400, "�a����̃L�[�����", BLUE, font_handle2);
	DrawStringToHandle(0, 450, "�u�v(��Ɉړ�)�v�u�c(�E�Ɉړ�)�v", WHITE, font_handle2);
	DrawStringToHandle(0, 500, "�u�r(���Ɉړ�)�v�u�`(���Ɉړ�)�v", WHITE, font_handle2);
	DrawStringToHandle(0, 550, "SPACE(�F��h��B������U������)�ł��B", WHITE, font_handle2);
	DrawStringToHandle(0, 650, "����ɂ���ēh���͈͂�З͂��Ⴂ�܂�", WHITE, font_handle2);
	DrawStringToHandle(0, 700, "�������Ԃ͂P���ő����h�����l�̏����ł��B", WHITE, font_handle2);
	DrawStringToHandle(0, 750, "Enter�������ƕ���I����ʂɈڍs���܂�", WHITE, font_handle2);

}

void Description_Decision(){
	if(Key_Get(KEY_INPUT_RETURN) == 1){
		description_flag = true;
	}
}

bool Get_Description_Flag(){
	return description_flag;
}