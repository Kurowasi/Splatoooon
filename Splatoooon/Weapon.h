#pragma once

void Weapon_Init();
void Weapon();
void Weapon_Draw();
void Weapon_Select();
bool Get_Weapon_Flag();
int Get_Weapon_Select_Chara();
int Get_Weapon_Select_Enemy();
void Check_Select_Count();

#define HAND_GUN 1
#define MACHINE_GUN 2
#define SNIPER_RIFLE 3
#define SHOT_GUN 4