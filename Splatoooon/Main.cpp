#include<DxLib.h>
#include"Main.h"
#include"Key.h"
#include"Config.h"
#include"Chara.h"
#include"Field.h"
#include"Enemy.h"
#include"Result.h"
#include"Weapon.h"
#include"Description.h"
#include"Modeselect.h"
#include"Ai.h"


bool Process_Loop(char key[256]){
	if (ScreenFlip() != 0) return false;
	if (ProcessMessage() != 0) return false;
	if (ClearDrawScreen() != 0) return false;
	if (GetHitKeyStateAll(key)) return false;

	return true;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(true);
	DxLib_Init();
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 16);
	//PlaySoundFile("Kalimba.mp3", DX_PLAYTYPE_LOOP);

	char key[256];

	typedef enum State{
		TITLE,
		MODESELECT,
		WEAPON,
		DESCRIPTION,
		GAME,
		AI,
		RESULT
	}State;
	State state = TITLE;

	Main_Init();

	while (Process_Loop(key)){
		Key_Update();
		switch (state){
		case TITLE:
			//DrawString(0, 0, "タイトル画面", WHITE);
			if (Key_Get(KEY_INPUT_RETURN) == 1){
				state = DESCRIPTION;
			}
			LoadGraphScreen(0, 0,"title.png", TRUE);
			break;
		case MODESELECT:
			if(Get_Select_Mode() == 1){
				state = AI;
			}else if(Get_Select_Mode() == 2){
				state = DESCRIPTION;
			}
			Mode_Select();
			break;
		case WEAPON:
			if (Get_Weapon_Flag() == true){
				state = GAME;
			}
			Weapon();
			break;
		case DESCRIPTION :
			if (Get_Description_Flag() == true){
				state = WEAPON;
			}
			Description();
			break;
		case GAME:
			DrawString(0, 0, "ゲーム画面", WHITE);
			Field_Draw();
			Chara_Draw();
			Chara_Move();
			Chara_Decision();
			Chara_Paint();
			Chara_X_Get();
			Chara_Y_Get();
			Chara_Hp_Check();
			Chara_Respawn_Time();
			Enemy_Draw();
			Enemy_Move();
			Enemy_Decision();
			Enemy_Paint();
			Enemy_X_Get();
			Enemy_Y_Get();
			Enemy_Hp_Check();
			Enemy_Respawn_Time();
			Color_Count();
			Game_End_Check();
			/*
			if (Key_Get(KEY_INPUT_RETURN) == 1){
				state = RESULT;
			}
			*/
			if (Game_End_Flag_Return() == true){
				state = RESULT;
			}
			break;
		case AI:
			DrawString(0, 0, "AIモード", WHITE);
			Ai();
			break;
		case RESULT:
			//DrawString(0, 0, "結果画面", WHITE);
			Result();
			if(Key_Get(KEY_INPUT_RETURN) == 1){
				DxLib_End();
			}
			break;
		}
	}

	WaitKey();
	DxLib_End();
	return 0;
}


void Main_Init(){
	Chara_Init();
	Enemy_Init();
	Field_Init();
	Result_Init();
	Weapon_Init();
	Description_Init();
	Mode_Select_Init();
	Ai_init();
}