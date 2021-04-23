#pragma once
//class CMovingBitmap;
namespace game_framework {
	class Cursor {
	public:
		Cursor();              //��l��
		void LoadBitmap();     //Ū���Ϥ�
		void OnMove();         //�B�z����
		void SetWhich(int);    //�]�w��ܪ��Ϥ�
		void OnShow();         //���
		void SetXY(int, int);  //�]�w�Ϥ�����m
	private:
		int x, y;
		int which;             //�ثe�n��ܭ��ӹϤ�
		CMovingBitmap	Sunflower;
		CMovingBitmap	peashooter;
		CMovingBitmap	Wallnut;
		//CMovingBitmap	squash;
		//CMovingBitmap	cherrybomb;
		//CMovingBitmap	snowpea;
		//CMovingBitmap	repeater;
		CMovingBitmap	shovel;
	};
}