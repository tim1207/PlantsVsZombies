#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Shovel.h"
namespace game_framework {
	//	鏟子的初始化
	Shovel::Shovel() {
		xb = 447;
		yb = 0;
		x = 462;
		y = 10;
		Choosed = false;
	}
	//	讀取鏟子所需的圖檔
	void Shovel::LoadBitmap() {
		bmp.LoadBitmap(".\\RES\\interface\\Shovel.bmp", RGB(0, 0, 255));
		back.LoadBitmap(".\\RES\\interface\\ShovelBack.bmp", RGB(0, 0, 0));
	}
	void Shovel::OnShow() {
		back.SetTopLeft(xb, yb);
		back.ShowBitmap(1.5);
		if (isChoosed() == false) {
			bmp.SetTopLeft(x, y);
			bmp.ShowBitmap();
		}
	}
	bool Shovel::isChoosed() {
		return Choosed;
	}
	void Shovel::SetChoosed(bool a) {
		Choosed = a;
	}
}