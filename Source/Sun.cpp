#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Sun.h"
#include <ctime>
#include <cstdlib>
bool LoadSunAlready = false;	              // �Ӷ����ɬO�_�w�gŪ��
namespace game_framework {
	CAnimation	anime;
	Sun::Sun() {
	}
	Sun::Sun(int a, int b, bool c) {             // a�OX�y��, b�OY�y�� ,c�N����Q���ͪ�
		x = a;
		y = (c ? b : -100);
		desy = b;
		picked = false;
		MoveCounter = 0;
		finished = false;
		CallFromSunFlower = c;
		if (c) {					                      //	�p�G�O�q�V�鸪���ͪ��h�H�ߪ��u���覡�X�{
			srand((unsigned)time(NULL));
			vy = -8;
			vx = (rand() % 5) - 2;
		}
		if (LoadSunAlready == false) {	        //	�p�G�w�gŪ���L���ɫh����Ū��
			LoadBitmap();
			LoadSunAlready = true;
		}
	}
	void Sun::LoadBitmap() {			            // Ū������
		for (int i = 0; i <= 21; i++) {
			char FILENAME[100];
			sprintf(FILENAME, "BMP_RES/image/interface/Sun.bmp");
			anime.AddBitmap(FILENAME, RGB(255, 255, 255));
		}
		anime.SetDelayCount(2);
	}
	int Sun::GetX() {					                // �^��X�y��
		return x;
	}
	int Sun::GetY() {					                // �^��Y�y��
		return y;
	}
	int Sun::GetHeight() {				            // �^�ǹϪ�����
		return anime.Height();
	}
	int Sun::GetWidth() {				              // �^�ǹϪ��e��
		return anime.Width();
	}

	void Sun::PickUp() {				              // �]�w�Ӷ��Q�߰_�᪺����
		picked = true;
		stepX = (x - 25) / 20;
		stepY = (y - 25) / 20;
	}
	bool Sun::isFinished() {			            // �ˬd���ʬO�_����
		return finished;
	}
	void Sun::drop() {					              // ���Ӷ��q�Ť����U
		if (y <= desy) {
			y += 2;
		}
	}
	void Sun::fly() {					                // ���Ӷ��H�ߪ��u���X��
		if (y <= desy) {
			y += vy;
			vy++;
			x += vx;
		}
	}
	void Sun::MoveAnime() {				            // �B�z�Ӷ����ʵe
		anime.OnMove();
	}
	void Sun::OnMove() {				              // �B�z�Ӷ�������
		if (picked == false && CallFromSunFlower == false) {
			drop();
		}
		else if (picked == false && CallFromSunFlower == true) {
			fly();
		}
		else if (picked == true) {
			x -= stepX;
			y -= stepY;
			MoveCounter++;
		}
		if (MoveCounter == 20) {
			finished = true;
		}
	}
	void Sun::OnShow() {				              //	���Ӷ���ܦb�e����
		anime.SetTopLeft(x, y);
		anime.OnShow();
	}
}