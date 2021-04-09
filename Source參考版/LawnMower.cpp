#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "LawnMower.h"
namespace game_framework {
	LawnMower::LawnMower() {
		x = -20;
		move = false;
	}
	//重設除草機的位置
	void LawnMower::Reset() {
		x = -20;
		move = false;
	}
	//設定除草機的位置
	void LawnMower::SetY(int a) {
		y = a * 75 + 70;
	}
	//取得除草機的位置
	int LawnMower::GetX() {
		return x;
	}
	//讀取除草機的圖片
	void LawnMower::LoadBitmap() {
		bmp.LoadBitmap(".\\RES\\interface\\LawnMower.bmp",RGB(0, 0, 0));
	}
	//移動除草機
	void LawnMower::OnMove() {
		if (move == true) {
			x += 10;
		}
	}
	//顯示除草機
	void LawnMower::OnShow(){
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
	//讓除草機動起來
	void LawnMower::StartMove() {
		move = true;
	}
}