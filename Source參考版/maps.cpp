#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "maps.h"
namespace game_framework {
	Maps::Maps() {
		x = -150;
		y = 0;
	}
	//讀取地圖
	void Maps::LoadBitmap() {
		bmp.LoadBitmap("RES/interface/background1.bmp");
	}
	//顯示地圖
	void Maps::OnShow() {
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
}