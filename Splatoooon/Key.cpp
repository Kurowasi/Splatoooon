#include<DxLib.h>
#include"Key.h"

static int m_key[256];

void Key_Update(){
	char tmp_key[256];
	GetHitKeyStateAll(tmp_key);
	for (int i = 0; i < 256; i++){
		if (tmp_key[i] != 0){
			m_key[i]++;
		}
		else{
			m_key[i] = 0;
		}
	}
}

int Key_Get(int key_code){
	return m_key[key_code];
}