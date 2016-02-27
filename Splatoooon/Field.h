#pragma once


void Field_Init();
void Field_Draw();
void Chara_X_Get();
void Chara_Y_Get();
void Enemy_X_Get();
void Enemy_Y_Get();
//ハンドガン
void Field_Front_Paint_Handgun();
void Field_Back_Paint_Handgun();
void Field_Right_Paint_Handgun();
void Field_Left_Paint_Handgun();
//マシンガン
void Field_Front_Paint_Machinegun();
void Field_Back_Paint_Machinegun();
void Field_Right_Paint_Machinegun();
void Field_Left_Paint_Machinegun();
//スナイパー
void Field_Front_Paint_Sniperrifle();
void Field_Back_Paint_Sniperrifle();
void Field_Right_Paint_Sniperrifle();
void Field_Left_Paint_Sniperrifle();
//ショットガン
void Field_Front_Paint_Shotgun();
void Field_Back_Paint_Shotgun();
void Field_Right_Paint_Shotgun();
void Field_Left_Paint_Shotgun();
//ハンドガン
void Field_Front_Paint_Enemy_Handgun();
void Field_Back_Paint_Enemy_Handgun();
void Field_Right_Paint_Enemy_Handgun();
void Field_Left_Paint_Enemy_Handgun();
//マシンガン
void Field_Front_Paint_Enemy_Machinegun();
void Field_Back_Paint_Enemy_Machinegun();
void Field_Right_Paint_Enemy_Machinegun();
void Field_Left_Paint_Enemy_Machinegun();
//スナイパー
void Field_Front_Paint_Enemy_Sniperrifle();
void Field_Back_Paint_Enemy_Sniperrifle();
void Field_Right_Paint_Enemy_Sniperrifle();
void Field_Left_Paint_Enemy_Sniperrifle();
//ショットガン
void Field_Front_Paint_Enemy_Shotgun();
void Field_Back_Paint_Enemy_Shotgun();
void Field_Right_Paint_Enemy_Shotgun();
void Field_Left_Paint_Enemy_Shotgun();

int Field_Front_Color_Return();
int Field_Back_Color_Return();
int Field_Right_Color_Return();
int Field_Left_Color_Return();
int Field_Front_Color_Return_Enemy();
int Field_Back_Color_Return_Enemy();
int Field_Right_Color_Return_Enemy();
int Field_Left_Color_Return_Enemy();
void Color_Count();
void Game_End_Check();
bool Game_End_Flag_Return();
int Get_Chara_Color_Count();
int Get_Enemy_Color_Count();