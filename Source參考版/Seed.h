#pragma once
#include "card.h"
namespace game_framework {
	class Seed {
	public:
		Seed();							          // ��l��
		int GetMoney();					      // �^�ǥثe�֦����Ӷ�
		void OnMove();					      // �B�z�ʧ@
		void OnShow();					      // ���
		void Load(int, int[]);	  		// Ū���һݪ��귽(�]�t�d��)
		void LoadBitmap();		    		// Ū���һݪ�����
		void Buy(int);			      		// �ʶR�Ӫ�
		void GotSun();			      		// �W�[�Ӷ�
		int GetCardID(int);		    		// �^�ǯS�w�d���N���Ӫ�����
		void ResetCardCounter(int);		// ���]�S�w�d�����N�o�ɶ�
		bool isCardAvailible(int);		// �^�ǯS�w�d���O�_�i�Q���
		void Reset();				        	// ���]����l���A
		void ResetCD();			      		// ���]�Ҧ��d�����N�o�ɶ�(�K�ޥ�)
	private:
		unsigned int money;			    	// �ثe�֦����Ӷ�
		vector<Card> cards;			    	// �x�s�֦����d��
		CMovingBitmap bmp;			
		CMovingBitmap	sun[4][10];
	};
}