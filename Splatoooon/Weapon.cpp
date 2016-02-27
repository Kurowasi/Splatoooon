#include<DxLib.h>
#include"Config.h"
#include"Key.h"
#include"Weapon.h"
#include<string.h>
#include<stdio.h>

//マウスの位置を入れておく変数
static int mouse_point_x;
static int mouse_point_y;

//銃の選択フラグ
static int weapon_select_chara;
static int weapon_select_enemy;

//ステージを変更させるフラグ
static bool weapon_flag;

//フォントデータを入れておく
static int font_handle;
static int font_handle2;

//クリックの回数をカウントする変数
static int select_count;

//選んだ武器を入れておく変数
static char *chara_select_weapon;
static char *enemy_select_weapon;

void Weapon_Init(){
	mouse_point_x = 0;
	mouse_point_y = 0;
	weapon_select_chara = 0;
	weapon_select_enemy = 0;
	weapon_flag = false;
	font_handle = CreateFontToHandle("ＭＳ 明朝", 20, 8);
	font_handle2 = CreateFontToHandle("MS ゴシック", 30, 8);
	select_count = 0;
	chara_select_weapon = "未定";
	enemy_select_weapon = "未定";

}

void Weapon(){
	Weapon_Draw();
	Weapon_Select();
	Check_Select_Count();
}

void Weapon_Draw(){
	//武器画像の表示
	LoadGraphScreen(0, 0, "hand.jpg", TRUE);
	LoadGraphScreen(300, 330, "machine2.jpg", TRUE);
	LoadGraphScreen(0, 450, "sniper.jpg", TRUE);
	LoadGraphScreen(300, 450, "shotgun.jpg", TRUE);
	//DrawFormatString(0, 120, BLACK, "%d", weapon_flag);
	//DrawFormatString(0, 120, BLACK, "%d", weapon_select);


	DrawStringToHandle(300, 5, "使いたい武器の番号を", RED, font_handle);
	DrawStringToHandle(300, 35, "キーボードで入力してください", RED, font_handle);
	DrawStringToHandle(260, 420, "①", BLACK, font_handle2);
	DrawStringToHandle(310, 420, "②", BLACK, font_handle2);
	DrawStringToHandle(260, 450, "③", BLACK, font_handle2);
	DrawStringToHandle(310, 450, "④", BLACK, font_handle2);

	DrawStringToHandle(300, 85, "Ａさんが選んだ武器は", RED, font_handle);
	DrawFormatStringToHandle(360, 115, RED, font_handle, "%sです", chara_select_weapon);
	DrawStringToHandle(300, 145, "Ｂさんが選んだ武器は", RED, font_handle);
	DrawFormatStringToHandle(360, 175, RED, font_handle, "%sです", enemy_select_weapon);
}

void Weapon_Select(){
	//DrawFormatString(0, 0, BLACK, "select_count:%d", select_count);
	if ((Key_Get(KEY_INPUT_1) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "ハンドガンが選ばれました");
		weapon_select_chara = HAND_GUN;
		chara_select_weapon = "ハンドガン";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_2) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "マシンガンが選ばれました");
		weapon_select_chara = MACHINE_GUN;
		chara_select_weapon = "マシンガン";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_3) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "スナイパーライフルが選ばれました");
		weapon_select_chara = SNIPER_RIFLE;
		chara_select_weapon = "スナイパーライフル";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_4) == 1) && (select_count == 0)){
		//DrawFormatString(0, 90, BLACK, "ショットガンが選ばれました");
		weapon_select_chara = SHOT_GUN;
		chara_select_weapon = "ショットガン";
		select_count = 1;
	}else if ((Key_Get(KEY_INPUT_1) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "ハンドガンが選ばれました");
		weapon_select_enemy = HAND_GUN;
		enemy_select_weapon = "ハンドガン";
		select_count = 2;
	}else if ((Key_Get(KEY_INPUT_2) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "マシンガンが選ばれました");
		weapon_select_enemy = MACHINE_GUN;
		enemy_select_weapon = "マシンガン";
		select_count = 2;
	}else if ((Key_Get(KEY_INPUT_3) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "スナイパーライフルが選ばれました");
		weapon_select_enemy = SNIPER_RIFLE;
		enemy_select_weapon = "スナイパーライフル";
		select_count = 2;
	}else if ((Key_Get(KEY_INPUT_4) == 1) && (select_count == 1)){
		//DrawFormatString(0, 90, BLACK, "ショットガンが選ばれました");
		weapon_select_enemy = SHOT_GUN;
		enemy_select_weapon = "ショットガン";
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