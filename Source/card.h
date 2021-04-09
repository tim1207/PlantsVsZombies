#pragma once
namespace game_framework {
	class Card {
	public:
		Card();
		Card(int);
		void OnMove();            //�B�z�d�����ʧ@
		void OnShow();            //��ܥd��
		void LoadBitmap();        //Ū���һݪ�����
		void LoadPlant();         //Ū���Ӫ����Ϥ�
		void LoadPrice();         //Ū���������Ϥ�
		void SetXY(int);          //�]�w�d������m
		int GetPrice();
		int GetWidth();
		int GetHeight();
		int GetX();
		int GetY();
		int GetID();
		void SetAvailible(bool);  //�]�w�d���O�_�i�Q���
		bool isAvailible();       //�^�ǥd���O�_�i�Q���
		void DelayCounter(); 
		void ResetCounter();
		bool CounterFinished();
		bool counting;
		void Reset();             //���]�d������l���A
	private:
		int x, y;
		double y2;                //�d�����ݮɶ��¹�����m
		int ID;                   //�d���N���Ӫ�����
		int price;                //����
		int delay;                //���ݩһݮɶ�
		int counter;              //�p�ɾ�
		bool availible;
		CMovingBitmap	bmp;
		CMovingBitmap	bmp2;
		CMovingBitmap	plant;
		CMovingBitmap	number[3][10];
	};
}