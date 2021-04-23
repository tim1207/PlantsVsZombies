#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Shovel.h"
namespace game_framework {
	//	��l����l��
	Shovel::Shovel() {
		xb = 100;
		yb = 0;
		x = 115;
		y = 10;
		Choosed = false;
	}
	//	Ū����l�һݪ�����
	void Shovel::LoadBitmap() {
		bmp.LoadBitmap(".\\BMP_RES\\image\\interface\\Shovel.bmp", RGB(0, 0, 255));
		back.LoadBitmap(".\\BMP_RES\\image\\interface\\ShovelBack.bmp", RGB(0, 0, 0));
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