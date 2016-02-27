#include<DxLib.h>
#include"Result.h"
#include"Config.h"
#include"Field.h"

static int chara_color_count;
static int enemy_color_count;
static int font_handle;


void Result_Init(){
	chara_color_count = 0;
	enemy_color_count = 0;
	font_handle = CreateFontToHandle("MS ƒSƒVƒbƒN", 50, 8);
}

void Result(){
	Get_Color_Count();
	Game_Decision();
	Result_Draw();
}

void Game_Decision(){
	if (chara_color_count == enemy_color_count){
		LoadGraphScreen(0, 0, "draw.png", TRUE);
	}else if(chara_color_count > enemy_color_count){
		//DrawFormatString(0, 60, BLACK, "‚`‚³‚ñ‚ªŸ‚¿‚Ü‚µ‚½");
		LoadGraphScreen(0,0,"winA.png",TRUE);
	}else{
		//DrawFormatString(0, 90, BLACK, "‚a‚³‚ñ‚ªŸ‚¿‚Ü‚µ‚½");
		LoadGraphScreen(0, 0, "winB.png", TRUE);
	}
}

void Get_Color_Count(){
	chara_color_count = Get_Chara_Color_Count();
	enemy_color_count = Get_Enemy_Color_Count();
}

void Result_Draw(){
	//DrawFormatString(0, 0, BLACK, "‚`‚³‚ñ‚ª“h‚Á‚½–‡”F%d", chara_color_count);
	//DrawFormatString(0, 30, BLACK, "‚a‚³‚ñ‚ª“h‚Á‚½–‡”F%d", enemy_color_count);
	DrawFormatStringToHandle(0, 90, BLACK, font_handle, "‚`‚³‚ñ‚ª“h‚Á‚½–‡”F%d", chara_color_count);
	DrawFormatStringToHandle(0, 160, BLACK, font_handle, "‚a‚³‚ñ‚ª“h‚Á‚½–‡”F%d", enemy_color_count);
}