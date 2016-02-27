#include<DxLib.h>
#include"Config.h"
#include"Chara.h"
#include"Key.h"
#include"Enemy.h"

//�t�B�[���h�̈ʒu��\���ϐ�
static int field_x;
static int field_y;

//�L�����̈ʒu��\���ϐ�
static int chara_x_paint;
static int chara_y_paint;

//�G�̈ʒu��\���ϐ�
static int enemy_x_paint;
static int enemy_y_paint;

//�L�����̈ʒu���}�X�P�ʂŕ\���ϐ�
static int chara_x_paint_masu;
static int chara_y_paint_masu;

//�G�̈ʒu���}�X�P�ʂŕ\���ϐ�
static int enemy_x_paint_masu;
static int enemy_y_paint_masu;

//�Q�[���̌o�ߎ��Ԃ����Ă����ϐ�
static int game_count;

//�Q�[���̏I�����Ǘ�����t���O
bool game_end_flag;

//�F��h�������������Ă����ϐ�
static int color_count_chara = 0;
static int color_count_enemy = 0;

//�t�B�[���h�Ŏg���ϐ�
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


void Field_Init(){ //�t�B�[���h�Ŏg���ϐ��̏�����
	field_x = 0;
	field_y = 0;

	//�L�����N�^�[�̈ʒu
	chara_x_paint = Chara_X_Return();
	chara_y_paint = Chara_Y_Return();
	//�L�����N�^�[�̈ʒu�i�}�X�P�ʁj
	chara_x_paint_masu = Chara_X_Return() / 30;
	chara_y_paint_masu = Chara_Y_Return() / 30;
	//�G�̈ʒu
	enemy_x_paint = Enemy_X_Return();
	enemy_y_paint = Enemy_Y_Return();
	//�G�̈ʒu�i�}�X�P�ʁj
	enemy_x_paint_masu = Enemy_X_Return() / 30;
	enemy_y_paint_masu = Enemy_Y_Return() / 30;


	game_count = 0;

	game_end_flag = false;


	//�L�����N�^�[�̏����ʒu�̃}�X�������̐F�ɓh��
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (chara_x_paint_masu == j && chara_y_paint_masu == i){
				field[i][j] = 2;
			}
		}
	}
	//�G�̏����ʒu�̃}�X��G�̐F�ɓh��
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (enemy_x_paint_masu == j && enemy_y_paint_masu == i){
				field[i][j] = 3;
			}
		}
	}


}


void Field_Draw(){ //�t�B�[���h��`�悷��֐�
	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 20; j++){
			if (field[i][j] == 0){ //�l���O�̂Ƃ��ɉ��F�̃}�X�̕`��
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, YELLOW, true);
				//DrawFormatString(field_x, field_y, BLACK, "%d", field[i][j]);
				field_x += 30; //�������̈ʒu���炵
			}
			if (field[i][j] == 1){ //�l���P�̂Ƃ��ɗ΂̃}�X�̕`��
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, GREEN, true);
				//DrawFormatString(field_x, field_y, BLACK, "%d", field[i][j]);
				field_x += 30; //�������̈ʒu���炵
			}
			if (field[i][j] == 2){ //�l���Q�̂Ƃ��ɐԂ̃}�X�̕`��
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, RED, true);
				field_x += 30;
			}
			if (field[i][j] == 3){ //�l���R�̂Ƃ��ɐ̃}�X�̕`��
				DrawBox(field_x, field_y, field_x + 30, field_y + 30, BLUE, true);
				field_x += 30;
			}
		}
		field_x = 0; //�E�[�܂ł������̂ŁA���[�ɖ߂�
		field_y += 30; //�������̃}�X��������ɂ���
	}
	field_y = 0; //��ԉ��܂ł������̂ŁA��ԏ�ɖ߂�
	game_count++;
	//DrawFormatString(0, 5, BLACK, "�Q�[���̌o�ߎ��ԁF%d�b", game_count / 60);

}


void Chara_X_Get(){ //�L�����̂����W�̎擾
	chara_x_paint = Chara_X_Return();
	chara_x_paint_masu = Chara_X_Return() / 30;
	/*
	//�L�����̈ʒu��\�����Ă���
	DrawFormatString(0, 30, BLACK, "�L�����̂����W�F%d", chara_x_paint);
	DrawFormatString(0, 60, BLACK, "�L�����̂��R�}���W�F%d", chara_x_paint_masu);
	*/
}

void Chara_Y_Get(){ //�L�����̂����W�̎擾
	chara_y_paint = Chara_Y_Return();
	chara_y_paint_masu = Chara_Y_Return() / 30;
	/*
	//�L�����̈ʒu��\�����Ă���
	DrawFormatString(0, 90, BLACK, "�L�����̂����W�F%d", chara_y_paint);
	DrawFormatString(0, 120, BLACK, "�L�����̂��R�}���W�F%d", chara_y_paint_masu);
	*/
}


void Enemy_X_Get(){ //�G�̂����W�̎擾
	enemy_x_paint = Enemy_X_Return();
	enemy_x_paint_masu = Enemy_X_Return() / 30;
	/*
	//�L�����̈ʒu��\�����Ă���
	DrawFormatString(0, 30 + 120, BLACK, "�L�����̂����W�F%d", enemy_x_paint);
	DrawFormatString(0, 60 + 120, BLACK, "�L�����̂��R�}���W�F%d", enemy_x_paint_masu);
	*/
}

void Enemy_Y_Get(){ //�G�̂����W�̎擾
	enemy_y_paint = Enemy_Y_Return();
	enemy_y_paint_masu = Enemy_Y_Return() / 30;
	/*
	//�L�����̈ʒu��\�����Ă���
	DrawFormatString(0, 90 + 120, BLACK, "�L�����̂����W�F%d", enemy_y_paint);
	DrawFormatString(0, 120 + 120, BLACK, "�L�����̂��R�}���W�F%d", enemy_y_paint_masu);
	*/
}


void Color_Count(){ //�R�}�𐔂���֐�
	color_count_chara = 0;
	color_count_enemy = 0;
	for (int i = 0; i < 30; i++){ //�����̃R�}�̐�
		for (int j = 0; j < 20; j++){
			if (field[i][j] == 2){
				color_count_chara += 1;
			}
		}
	}
	for (int i = 0; i < 30; i++){ //�G�̃R�}�̐�
		for (int j = 0; j < 20; j++){
			if (field[i][j] == 3){
				color_count_enemy += 1;
			}
		}
	}
	//DrawFormatString(0, 30, BLACK, "�����̖����F%d", color_count_chara);
	//DrawFormatString(0, 60, BLACK, "�G�̖����F%d", color_count_enemy);
}

int Get_Chara_Color_Count(){
	return color_count_chara;
}

int Get_Enemy_Color_Count(){
	return color_count_enemy;
}




//////////////////////////////////////�t�B�[���h�̃y�C���g/////////////////////////////////////////////////////////////////////////////////////////////////

//�n���h�K��
void Field_Front_Paint_Handgun(){ //�L�������U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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




void Field_Back_Paint_Handgun(){ //�L�������U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Handgun(){ //�L�������U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Handgun(){ //�L�������U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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

//�}�V���K��
void Field_Front_Paint_Machinegun(){ //�L�������U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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




void Field_Back_Paint_Machinegun(){ //�L�������U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Machinegun(){ //�L�������U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Machinegun(){ //�L�������U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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

//�X�i�C�p�[
void Field_Front_Paint_Sniperrifle(){ //�L�������U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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




void Field_Back_Paint_Sniperrifle(){ //�L�������U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Sniperrifle(){ //�L�������U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Sniperrifle(){ //�L�������U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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

//�V���b�g�K��
void Field_Front_Paint_Shotgun(){ //�L�������U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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




void Field_Back_Paint_Shotgun(){ //�L�������U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Shotgun(){ //�L�������U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Shotgun(){ //�L�������U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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























//////////////////////////////////////�G�̃t�B�[���h�̃y�C���g/////////////////////////////////////////////////////////////////////////////////////////////////
//�n���h�K��
void Field_Front_Paint_Enemy_Handgun(){ //�G���U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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


void Field_Back_Paint_Enemy_Handgun(){ //�G���U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Enemy_Handgun(){ //�G���U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Enemy_Handgun(){ //�G���U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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
//�}�V���K��
void Field_Front_Paint_Enemy_Machinegun(){ //�G���U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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


void Field_Back_Paint_Enemy_Machinegun(){ //�G���U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Enemy_Machinegun(){ //�G���U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Enemy_Machinegun(){ //�G���U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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
//�X�i�C�p�[
void Field_Front_Paint_Enemy_Sniperrifle(){ //�G���U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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


void Field_Back_Paint_Enemy_Sniperrifle(){ //�G���U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Enemy_Sniperrifle(){ //�G���U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Enemy_Sniperrifle(){ //�G���U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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
//�V���b�g�K��
void Field_Front_Paint_Enemy_Shotgun(){ //�G���U�������Ƃ��ɑO�̃t�B�[���h���y�C���g����
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


void Field_Back_Paint_Enemy_Shotgun(){ //�G���U�������Ƃ��Ɍ��̃t�B�[���h���y�C���g����
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

void Field_Right_Paint_Enemy_Shotgun(){ //�G���U�������Ƃ��ɉE�̃t�B�[���h���y�C���g����
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

void Field_Left_Paint_Enemy_Shotgun(){ //�G���U�������Ƃ��ɍ��̃t�B�[���h���y�C���g����
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






////////////////////////�}�X�̈ʒu��Ԃ�/////////////////////////////////////////////////////////////////
int Field_Front_Color_Return(){ //�O�̃}�X�̈ʒu��Ԃ��֐�
	return field[chara_y_paint_masu - 1][chara_x_paint_masu];
}

int Field_Back_Color_Return(){ //���X�̈ʒu��Ԃ��֐�
	return field[chara_y_paint_masu + 1][chara_x_paint_masu];
}

int Field_Right_Color_Return(){ //�E�̃}�X�̈ʒu��Ԃ��֐�
	return field[chara_y_paint_masu][chara_x_paint_masu + 1];
}

int Field_Left_Color_Return(){ //���̃}�X�̈ʒu��Ԃ��֐�
	return field[chara_y_paint_masu][chara_x_paint_masu - 1];
}


////////////////////////�G�̃}�X�̈ʒu��Ԃ�/////////////////////////////////////////////////////////////////
int Field_Front_Color_Return_Enemy(){ //�G�̑O�̃}�X�̈ʒu��Ԃ��֐�
	return field[enemy_y_paint_masu - 1][enemy_x_paint_masu];
}

int Field_Back_Color_Return_Enemy(){ //�G�̌��X�̈ʒu��Ԃ��֐�
	return field[enemy_y_paint_masu + 1][enemy_x_paint_masu];
}

int Field_Right_Color_Return_Enemy(){ //�G�̉E�̃}�X�̈ʒu��Ԃ��֐�
	return field[enemy_y_paint_masu][enemy_x_paint_masu + 1];
}

int Field_Left_Color_Return_Enemy(){ //�G�̍��̃}�X�̈ʒu��Ԃ��֐�
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