#include<DxLib.h>
#include"Chara.h"
#include"Config.h"
#include"Key.h"
#include"Field.h"
#include"Weapon.h"

//�L�����̕`��Ɏg���ϐ�
static int chara_x;
static int chara_y;
//�L�����̈ړ��Ɏg���ϐ�
static int chara_v;

//�L�����̗̑�
static int chara_hp;

//���X�|�[���܂ł̎��Ԃ�����ϐ�
static int chara_respawn_counter;

//������ċN����܂ł̎��Ԃ�����ϐ�
static int weapon_respawn;

//�L�����̃��X�|�[���Ɏg���t���O
bool chara_respawn_flag;

enum{ //�L�����N�^�[�̕���
	FRONT,
	RIGHT,
	BACK,
	LEFT
}angle;


void Chara_Init(){ //�L�����Ŏg���ϐ�������������֐�
	//�L�����N�^�[�̏����ʒu
	chara_x = 0;
	chara_y = 870;
	//�L�����N�^�[�̈ړ����x
	chara_v = 30;
	//�L�����N�^�[��HP
	chara_hp = 100;
	//�`�����N�^�[�̌����Ă����
	angle = FRONT;

	chara_respawn_counter = 1000;

	chara_respawn_flag = true;

	weapon_respawn = 1000;

}

void Chara_Draw(){ //�L�����̕`�������֐�
	if (chara_respawn_flag == true){
		//�L�����̕`��
		DrawBox(chara_x, chara_y, chara_x + 30, chara_y + 30, RED, true);

		//�ڂ̕`��
		if (angle == FRONT){ //�O�����̖ڂ̕`��
			DrawBox(chara_x + 5, chara_y + 10, chara_x + 10, chara_y + 15, BLACK, true);
			DrawBox(chara_x + 20, chara_y + 10, chara_x + 25, chara_y + 15, BLACK, true);
		}
		if (angle == BACK){ //�������̖ڂ̕`��
			DrawBox(chara_x + 5, chara_y + 20, chara_x + 10, chara_y + 25, BLACK, true);
			DrawBox(chara_x + 20, chara_y + 20, chara_x + 25, chara_y + 25, BLACK, true);
		}
		if (angle == RIGHT){ //�E�����̖ڂ̕`��
			DrawBox(chara_x + 20, chara_y + 10, chara_x + 25, chara_y + 15, BLACK, true);
		}
		if (angle == LEFT){ //�������̖ڂ̕`��
			DrawBox(chara_x + 5, chara_y + 10, chara_x + 10, chara_y + 15, BLACK, true);
		}

		//���̕`��
		DrawBox(chara_x, chara_y, chara_x + 30, chara_y + 30, BLACK, false);

		//DrawFormatString(0, 90, BLACK, "�����̗̑́F%d", chara_hp);
	}
	chara_respawn_counter++;
	//DrawFormatString(0, 0, BLACK, "%d", chara_respawn_counter);
}

void Chara_Move(){ //�L�����̈ړ�������֐�
	if (chara_respawn_flag == true){
		//��L�[�֌W
		if (Key_Get(KEY_INPUT_UP) == 1 && angle != FRONT){ //�O��������Ȃ��̂ɏ�L�[�������ꂽ��O�����ɂ���
			angle = FRONT;
		}
		if (Key_Get(KEY_INPUT_UP) == 1 && Field_Front_Color_Return() == 2 && angle == FRONT){ //��L�[�ŏ�Ɉړ�
			chara_y -= chara_v;
		}
		//���L�[�֌W
		if (Key_Get(KEY_INPUT_DOWN) == 1 && angle != BACK){ //����������Ȃ��̂ɉ��L�[�������ꂽ��O�����ɂ���
			angle = BACK;
		}
		if (Key_Get(KEY_INPUT_DOWN) == 1 && Field_Back_Color_Return() == 2 && angle == BACK){ //���L�[�ŉ��Ɉړ�
			chara_y += chara_v;
		}
		//�E�L�[�֌W
		if (Key_Get(KEY_INPUT_RIGHT) == 1 && angle != RIGHT){ //�E��������Ȃ��̂ɉE�L�[�������ꂽ��O�����ɂ���
			angle = RIGHT;
		}
		if (Key_Get(KEY_INPUT_RIGHT) == 1 && Field_Right_Color_Return() == 2 && angle == RIGHT){ //�E�L�[�ŉE�Ɉړ�
			chara_x += chara_v;
		}
		//���L�[�֌W
		if (Key_Get(KEY_INPUT_LEFT) == 1 && angle != LEFT){ //����������Ȃ��̂ɍ��L�[�������ꂽ��O�����ɂ���
			angle = LEFT;
		}
		if (Key_Get(KEY_INPUT_LEFT) == 1 && Field_Left_Color_Return() == 2 && angle == LEFT){ //���L�[�ō��Ɉړ�
			chara_x -= chara_v;
		}
	}
}

void Chara_Decision(){ //�L�����̓����蔻����s���֐�
	if (chara_x <= 0){ //��ʍ��̓����蔻��
		chara_x = 0;
	}
	if (chara_x >= 570){ //��ʉE�̓����蔻��
		chara_x = 570;
	}
	if (chara_y <= 0){ //��ʏ�̓����蔻��
		chara_y = 0;
	}
	if (chara_y >= 870){ //��ʉ��̓����蔻��
		chara_y = 870;
	}
}

void Chara_Paint(){ //�L�����̍U���i�y�C���g�j���s���֐�
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
	//DrawFormatString(0, 200, RED, "weapon_respawn:%d�b", weapon_respawn / 60);
}


void Chara_Damage_Handgun(){ //�L�����N�^�[�̃_���[�W���s���֐�
	chara_hp -= 30;
}
void Chara_Damage_Machinegun(){ //�L�����N�^�[�̃_���[�W���s���֐�
	chara_hp -= 50;
}
void Chara_Damage_Sniperrifle(){ //�L�����N�^�[�̃_���[�W���s���֐�
	chara_hp -= 100;
}
void Chara_Damage_Shotgun(){ //�L�����N�^�[�̃_���[�W���s���֐�
	chara_hp -= 100;
}


void Chara_Respawn(){ //�L�����N�^�[�̃��X�|�[������i�ŏ��̈ʒu�ɂ���j�֐�
	Chara_Init();
	chara_respawn_counter = 0;
}

void Chara_Respawn_Time(){ //�L�����N�^�[�̕��A����܂ł̎��Ԃ������֐�
	if (chara_respawn_counter > 150){
		chara_respawn_flag = true;
	}
}

void Chara_Hp_Check(){ //�L�����N�^�[��HP���`�F�b�N����֐�
	if (chara_hp <= 0){
		Chara_Respawn();
		chara_respawn_flag = false;
	}
}


int Chara_X_Return(){ //�L�����̂����W��n���֐�
	return chara_x;
}

int Chara_Y_Return(){ //�L�����̂����W��n���֐�
	return chara_y;
}