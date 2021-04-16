#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Seed.h"
#include "card.h"
namespace game_framework {
	Seed::Seed() {
		//money = 50;
		money =1000;
	}
	void Seed::Reset() {		                        // ���]��l���A
		//money = 50;
		money = 1000;
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->Reset();
		}
	}
	void Seed::ResetCD() {		                      // �j��N�o�ɶ��k�s(�K�ޥ�)
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->Reset();
		}
	}
	int Seed::GetMoney() {		                      // �^�ǥثe�Ӷ��ƶq
		return money;
	}
	void Seed::Buy(int a) {		                      // �ʶR�Ӫ�
		money -= cards[a].GetPrice();
	}
	void Seed::GotSun() {		                        // �W�[�Ӷ�
		money += 25;
		if (money > 9999) {		                        // �W��9999
			money = 9999;
		}
	}
	void Seed::Load(int sum, int CardIDs[]) {	      //Ū���һݪ��귽(�]�t�d��)
		LoadBitmap();
		for (int i = 0; i < sum; i++) {
			//cards.push_back(Card(CardIDs[i]));
			cards.push_back(Card(i+1));
		}
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->LoadBitmap();
		}
	}
	void Seed::LoadBitmap() {					              //Ū���һݪ�����
		// sum money
		bmp.LoadBitmap("./BMP_RES/image/interface/SunBack.bmp", RGB(0, 0, 0));	
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 10; j++) {
				char FILENAME[100];
				sprintf(FILENAME,  ".\\BMP_RES\\image\\interface\\%d.bmp", j);
				sun[i][j].LoadBitmap(FILENAME, RGB(255, 255, 255));
			}
		}
	}
	int Seed::GetCardID(int a) {				            // �^�ǯS�w�d���ҥN���Ӫ�����
		return cards[a].GetID();
	}
	void Seed::ResetCardCounter(int a) {		        // ���]�S�w�d�����N�o�ɶ�
		cards[a].ResetCounter();
	}
	bool Seed::isCardAvailible(int a) {			        // �^�ǯS�w�d���O�_�i�Q���
		return cards[a].isAvailible();
	}
	void Seed::OnMove()							                // ����ө����ʧ@
	{
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->OnMove();
			if (it->GetPrice() > GetMoney()) {
				it->SetAvailible(false);
			}
			else
				it->SetAvailible(true);
		}
	}
	void Seed::OnShow()							                // ��ܰө�
	{
		bmp.SetTopLeft(0, 0);
		bmp.ShowBitmap();
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->SetXY(it-cards.begin());
			it->OnShow();
		}
		// ��ܤӶ��ƶq
		if (GetMoney() == 0) {
			sun[0][0].SetTopLeft(100, 10);
			sun[0][0].ShowBitmap();
		}
		else if (GetMoney() > 0 && GetMoney() < 100) {
			for (int i = 0, num = GetMoney(); i < 2; i++, num /= 10) {
				sun[i][num % 10].SetTopLeft(100 - 13 * i,8);
				sun[i][num % 10].ShowBitmap();
			}
		}
		else if (GetMoney() >= 100 && GetMoney() < 1000) {
			for (int i = 0, num = GetMoney(); i < 3; i++, num /= 10) {
				sun[i][num % 10].SetTopLeft(100 - 13 * i,8);
				sun[i][num % 10].ShowBitmap();
			}
		}
		else {
			for (int i = 0, num = GetMoney(); i < 4; i++, num /= 10) {
				sun[i][num % 10].SetTopLeft(100 - 13 * i,8);
				sun[i][num % 10].ShowBitmap();
			}
		}
	}
}