#include<DxLib.h>
#include"Modeselect.h"
#include"Config.h"
#include"Field.h"


static int font_handle;
static int font_handle2;
static int mouse_x;
static int mouse_y;
static int mode;

void Mode_Select_Init(){
	font_handle = CreateFontToHandle("‚l‚r –¾’©", 70, 20);
	font_handle2 = CreateFontToHandle("‚l‚r –¾’©", 30, 10);
	mouse_x = 0;
	mouse_y = 0;
	mode = 0;
}

void Mode_Select(){
	Mode_Select_Draw();
	Mode_Select_Click();
}

void Mode_Select_Draw(){
	DrawBox(0, 0, 600, 450, YELLOW, true);
	DrawBox(0, 450, 600, 900, GREEN, true);
	DrawStringToHandle(120, 160, "‚`‚hƒ‚[ƒh", BLACK, font_handle);
	DrawStringToHandle(120,610,"‘Îíƒ‚[ƒh",BLACK,font_handle);
	DrawStringToHandle(100, 435, "ƒ‚[ƒh‚ðƒNƒŠƒbƒN‚µ‚Ä‚­‚¾‚³‚¢", BLACK, font_handle2);
}

void Mode_Select_Click(){
	if( (GetMouseInput() && MOUSE_INPUT_LEFT) != 0 ){
		GetMousePoint(&mouse_x, &mouse_y);
		if(mouse_y > 0 && mouse_y < 450){
			mode = MODE_AI;
		}else if(mouse_y > 450 && mouse_y < 900){
			mode = MODE_BATTLE;
		}
	}
}

int Get_Select_Mode(){
	return mode;
}
