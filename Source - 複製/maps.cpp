#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "maps.h"
namespace game_framework {
	Maps::Maps() {
		x = 0;
		y = 0;
	}
	//Ū���a��
	void Maps::LoadBitmap(string path = "../BMP_RES/image/interface/background1.bmp") {
		bmp.LoadBitmap(path);
	}
	//��ܦa��
	void Maps::OnShow(int x = 0, int y = 0) {
		bmp.SetTopLeft(x, y);
		bmp.ShowBitmap();
	}
}