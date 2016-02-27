#include<DxLib.h>
#include"Config.h"
#include"Description.h"
#include"Key.h"


static bool description_flag;
static int font_handle;
static int font_handle2;

void Description_Init(){
	font_handle = CreateFontToHandle("ＭＳ 明朝", 50 , 3);
	font_handle2 = CreateFontToHandle("ＭＳ 明朝", 30, 3);
	description_flag = false;
}

void Description(){
	Description_Draw();
	Description_Decision();
}

void Description_Draw(){
	DrawStringToHandle(160, 0, "ルール説明", WHITE, font_handle);
	DrawStringToHandle(0, 100, "このゲームは２人で対戦するゲームです。", WHITE, font_handle2);
	DrawStringToHandle(0, 150, "Ａさんは赤。Ｂさんは青です。", WHITE, font_handle2);
	DrawStringToHandle(0, 200, "Ａさんのキー操作は", RED, font_handle2);
	DrawStringToHandle(0, 250, "「↑(上に移動)」「→(右に移動)」", WHITE, font_handle2);
	DrawStringToHandle(0, 300, "「↓(下に移動)」「←(左に移動)」", WHITE, font_handle2);
	DrawStringToHandle(0, 350, "Enter(色を塗る。相手を攻撃する)です。", WHITE, font_handle2);
	DrawStringToHandle(0, 400, "Ｂさんのキー操作は", BLUE, font_handle2);
	DrawStringToHandle(0, 450, "「Ｗ(上に移動)」「Ｄ(右に移動)」", WHITE, font_handle2);
	DrawStringToHandle(0, 500, "「Ｓ(下に移動)」「Ａ(左に移動)」", WHITE, font_handle2);
	DrawStringToHandle(0, 550, "SPACE(色を塗る。相手を攻撃する)です。", WHITE, font_handle2);
	DrawStringToHandle(0, 650, "武器によって塗れる範囲や威力が違います", WHITE, font_handle2);
	DrawStringToHandle(0, 700, "制限時間は１分で多く塗った人の勝利です。", WHITE, font_handle2);
	DrawStringToHandle(0, 750, "Enterを押すと武器選択画面に移行します", WHITE, font_handle2);

}

void Description_Decision(){
	if(Key_Get(KEY_INPUT_RETURN) == 1){
		description_flag = true;
	}
}

bool Get_Description_Flag(){
	return description_flag;
}